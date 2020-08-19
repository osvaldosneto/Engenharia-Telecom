#include <Arduino_FreeRTOS.h>
#include <FreeRTOSVariant.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>

#define BIT_PERIODO pdMS_TO_TICKS(80)
#define HALF_BIT_PERIODO pdMS_TO_TICKS(35)
#define STOP_PERIODO 3*BIT_PERIODO
#define origem_mac 176
#define tamanho_frame 15
#define byte_recebido 13

const byte interruptPin = 2;
const byte outputSignalPIN = 3;

//tarefas
void TaskSender(void *pvParameters);
void TaskChatSender(void *pvParameters);
void TaskChatReceiver(void *pvParameters);

//Timer utilizado para controlar tempo de leitura
static TimerHandle_t xTimer;
//Timer utilizado para verifica start bit
static TimerHandle_t xTimerVerifica;

//Fila de armazenamento de informações
QueueHandle_t queueSender = NULL; //fila de recebimento
QueueHandle_t queueReceived = NULL; //fila recebida para processo em aplicação
QueueHandle_t filaSinalizacao = NULL; //fila de sinalização
QueueHandle_t queueSenderStruct = NULL; //fila de struct frame a enviar
QueueHandle_t queueSet = NULL; //conjunto de filas (fila SenderStruct e Sender)
 
//variável controle byte
bool processaByte = false;

//conatador para leitura dos bits
int contador = 0;

//contador para leitura de bytes
int contadorByte = 0;

//dado recebido pelo rx
byte dadoRecebido = 0;

//Semáforo utilizado para sinalizar a Tarefa de Interrupção
SemaphoreHandle_t semaforo = NULL;

//estados da máquina de leitura
volatile static enum t_estadoLeitura {START, lendo, STOP} estadoLeitura;

volatile byte state = HIGH;

//MAQUINA DE TRANSMISSÂO
#define STOP_BIT_PERIODO 4*BIT_PERIODO

byte frame[15];

byte sender[15];
byte received[13];

struct quadro{
  byte dado[10];
  byte portDest;
  byte portFonte;
  byte dest_mac;
}quadro;


class maquina_TX {
  private:
    volatile static enum t_estado {AGUARDA_STOP, TX, FIM_TX, FIM} estado;
    static byte dado;
    static byte cont;
    static TimerHandle_t xTimerSerial;
  public:
    maquina_TX(){}
    void setMTX() {
      digitalWrite(outputSignalPIN, HIGH);
      xTimerSerial = xTimerCreate("Signal", STOP_BIT_PERIODO, pdTRUE, 0, timerSerialHandler);
    }
    void waitFim(){
      int aux = 0;
      xQueueReceive(filaSinalizacao, &aux, portMAX_DELAY);
    }

    static void timerSerialHandler (TimerHandle_t meuTimer) {
      switch (estado) {
        case AGUARDA_STOP:
          estado = TX;
          cont = 0;
          digitalWrite(outputSignalPIN, LOW);
          if (digitalRead(outputSignalPIN) == LOW) {
          }
          xTimerChangePeriod(meuTimer, BIT_PERIODO, 0);
          break;
        case TX:
          if (dado & B00000001) {
            digitalWrite(outputSignalPIN, HIGH);
          } else {
            digitalWrite(outputSignalPIN, LOW);
          }
          cont++;
          if (cont != 8) {
            dado = dado >> 1;
          } else {
            estado = FIM_TX;
          }
          break;
        case FIM_TX:
          xTimerStop(meuTimer, 0);
          estado = FIM;
          digitalWrite(outputSignalPIN, HIGH);
          xSemaphoreGive(semaforo);
          int i = 1;
          xQueueOverwrite(filaSinalizacao, &i);
          break;
      }
    };

    //função da Máquina de tx para montar o quadro
    void montarQuadro(struct quadro *quadro){
       frame[0] = B00000010;
       frame[1] = B00001011 | quadro->dest_mac;
       frame[2] = B01000000;
       frame[3] = quadro->dado[0];
       frame[4] = quadro->dado[1];
       frame[5] = quadro->dado[2];
       frame[6] = quadro->dado[3];
       frame[7] = quadro->dado[4];
       frame[8] = quadro->dado[5];
       frame[9] = quadro->dado[6];
       frame[10] = quadro->dado[7];
       frame[11] = quadro->dado[8];
       frame[12] = quadro->dado[9];
       frame[13] = B00000000;
       frame[14] = B00000011;
    }
    
    void enviar_byte(byte dado) {
      estado = AGUARDA_STOP;
      this->dado = dado;
      digitalWrite(outputSignalPIN, HIGH);
      xTimerChangePeriod(xTimerSerial, STOP_BIT_PERIODO, 0);
      xTimerStart(xTimerSerial, 0);
      waitFim();
    };
} MTX;


volatile enum maquina_TX::t_estado maquina_TX::estado;
byte maquina_TX::dado;
byte maquina_TX::cont;
TimerHandle_t maquina_TX::xTimerSerial;


void setup() {

  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(outputSignalPIN, OUTPUT);
  MTX.setMTX();
  
  //Criando Semáforo Mutex
  semaforo = xSemaphoreCreateMutex();

  //Iniciando o estado da máquina de leitura
  estadoLeitura = STOP;

  //Criando fila de dados
  queueSender = xQueueCreate(50, sizeof(sender));
  queueReceived = xQueueCreate(50, sizeof(received));
  filaSinalizacao = xQueueCreate(1, sizeof(int));
  queueSenderStruct = xQueueCreate(50, sizeof(quadro));
  queueSet = xQueueCreateSet(50*2);

  //conjunto de filas
  xQueueAddToSet(queueSenderStruct, queueSet);
  xQueueAddToSet(queueSender, queueSet);

  //Timer com METADE do período, chamando função para verificação do start bit
  xTimerVerifica = xTimerCreate("Verifica", HALF_BIT_PERIODO, pdFALSE, 0, timerHandlerVerifica);
  //Timer que chama função de leitura
  xTimer = xTimerCreate("Timer_1", BIT_PERIODO, pdTRUE, 0, timerHandler);

  //Tarefa de envio de BYTES
  xTaskCreate(TaskSender, (const portCHAR*)"TaskSender", 128, NULL, 3, NULL);

  //Tarefa de chat - envio bytes
  xTaskCreate(TaskChatSender, (const portCHAR*)"TaskChatSender", 128, NULL, 1, NULL);

  //Tarefa de chat - recebimento bytes
  xTaskCreate(TaskChatReceiver, (const portCHAR*)"TaskChatReceiver", 128, NULL, 1, NULL);

}

//Tarefa responsável pela leitura das filas onde existe algum dado armazenado
void TaskSender(void *pvParameters) {
  
  (void) pvParameters;

  uint32_t receiveData;

  //criação do identificador onde receberá a identificação da fila ocupada por algum dado
  QueueHandle_t xQueueThatContainsData;
  byte envio[tamanho_frame];
   
  for(;;){
    //recebendo identificador da fila com algum dado
    xQueueThatContainsData = ( QueueHandle_t ) xQueueSelectFromSet(queueSet, portMAX_DELAY );
    if(xQueueThatContainsData == queueSender){
      //inicio de envio do byte
      xQueueReceive(queueSender, &envio, 0);
      for (int i=0; i<tamanho_frame; i++){      
        MTX.enviar_byte(envio[i]);
        Serial.print("\nEncaminhando enlace:");
        Serial.print((char)envio[i]);
        envio[i] = NULL;     
      }
    }else{
      struct quadro aux;
      xQueueReceive(queueSenderStruct, &aux, 0);
      MTX.montarQuadro(&aux);
      //inicio de envio do byte
      for (int i=0; i<tamanho_frame; i++){
        MTX.enviar_byte(frame[i]);
        Serial.print("\nEncaminhando Origem:");
        Serial.print((char)frame[i]);
        frame[i] = NULL; 
      }
      
    }
  }
}

//Tarefa de envio de mensagem a enviar, sendo lida da serial do arduino
void TaskChatSender(void *pvParameters) {
  struct quadro enviar;
  byte aux;
  int i=0;
  
  Serial.print("Mensagem:");
  
  for (;;) {
    while (Serial.available() == 0){} // espera ocupada lendo a serial
    aux = Serial.read(); // Lê mensagem da serial
    enviar.dado[i]=aux;  // Adiciona dados na struct
    Serial.print((char)aux);
    i++;  
    if (aux=='\n') {
      i=0;
      attachInterrupt(digitalPinToInterrupt(interruptPin), interrup, LOW);
      leitura_Destino(enviar);
      Serial.print("\nMensagem:");
    }
  }
}

//Tarefa de leitura do byte recebido, nos informa qual mensagem foi recebida
void TaskChatReceiver(void *pvParameters) {
  for(;;){
    byte recebido[byte_recebido];
    if(uxQueueMessagesWaiting(queueReceived)){     
      xQueueReceive(queueReceived, &recebido, 0);
      Serial.print("\nRecebida: ");
      for(int i=3; i<byte_recebido; i++){
        Serial.print((char)recebido[i]);
      }
    }
  }
}

//função de leitura do destino a enviar mensagem
void leitura_Destino(struct quadro &enviar){
  byte aux;
  Serial.print("\nDestino: "); 
  while (Serial.available() == 0){} // espera ocupada lendo a serial  
  aux = Serial.parseInt(); // Lê mensagem da serial
  while(Serial.read() != '\n'); 
  enviar.dest_mac = (byte) aux;
  Serial.print(enviar.dest_mac);
  xQueueSendToBack(queueSenderStruct, &enviar, 0);
}

//Função timer inicia leitura bits
void timerHandler(TimerHandle_t Timer) {

  bool recebendo = true;
  //Análise do estado da máquina
  switch (estadoLeitura) {
    case lendo:
    
      if (contador != 8) {
        dadoRecebido = dadoRecebido >> 1;
        if (digitalRead(interruptPin) == HIGH) {
          dadoRecebido = dadoRecebido | B10000000;
        }
        contador++;      
      } else {
        byte dest = 0;
        xTimerChangePeriod(xTimer, STOP_PERIODO, 0); //mudança do timer para garantir stop bit
        estadoLeitura = STOP; //mudança do estado da máquina
        contador = 0;

        if(dadoRecebido == 2){
          recebendo = true;
        }

        if(recebendo){
          if(contadorByte==1){
            dest = B11110000 & dadoRecebido;
            verificaDestino(dest);
            if(processaByte){        
            } else {
              byte a = B00000010;
              sender[0] = B00000010;
              sender[contadorByte] = dadoRecebido;
            }         
          }
          if(contadorByte>1){
              if(processaByte){
              received[contadorByte] = dadoRecebido;
            } else {
              sender[contadorByte] = dadoRecebido;
            }     
          }
        }
        contadorByte ++;
        if(contadorByte == tamanho_frame){
          if(processaByte){
            //adicionar na fila de processanento
            xQueueSendToBack(queueReceived, &received, portMAX_DELAY);
          } else {
             xQueueSendToBack(queueSender, &sender, portMAX_DELAY);
          }
          contadorByte = 0;
          processaByte = false;
        }
      }
      break;

    case STOP:
      estadoLeitura = START;
      attachInterrupt(digitalPinToInterrupt(interruptPin), interrup, LOW);
      break;
  }
}

//função que verifica o destino da mensagem a enviar
void verificaDestino(int aux){
  if(aux == origem_mac){
    processaByte = true;
  } else {
    processaByte = false;
  }
}

//Timer que verifica se o start bit está correto
void timerHandlerVerifica (TimerHandle_t timer) {

  if (digitalRead(interruptPin) == LOW) {
    
    xTimerChangePeriod(xTimer, BIT_PERIODO, 0); //Chama timer que fará a leitura, pois o start bit está correto!
    xTimerStart(xTimer, 0); //Start bit confirmado, alterando estado da máquina de leitura!
    estadoLeitura = lendo;
  } else {
    //ativa interrupção pois start bit está incorreto
    attachInterrupt(digitalPinToInterrupt(interruptPin), interrup, LOW);
  }
}

//interrupção em sinal baixo
void interrup(void) {

  BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR( semaforo, &xHigherPriorityTaskWoken );

  //timer iniciado com T/2 para verificar stop bit.
  xTimerStart(xTimerVerifica, 0);
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}

void loop() {
}
