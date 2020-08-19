#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
#include <RTClib.h> 
#include <dht.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led1 8      //led de inicialização se estiver tudo ok!!!!
#define led2 7      //led de aguardo de inicialização!!!!
#define DHT11_PIN 5 //definindo pinos para leitura de dados (uidade e temperatura)
#define id 1        //definindo id do modulo transmissor

const uint64_t pipe1 = 0xE14BC8F482LL; //endereço de comunicação para abertura de pipe

dht DHT;            //objeto DHT sendo criado para extração das variáveis
RTC_DS1307 rtc;     //objeto rtc sendo criado para extração da hora
RF24 radio(9,10);   //definindo portas CE porta 9 e CSN porta 10     

String enviar = "";
char buf1 [32];

void setup() {
  Serial.begin(9600);
  Serial.println("Modulo Iniciando...");
  Wire.begin();
  pinMode(led1, OUTPUT);     //definindo portas para led de verificação
  pinMode(led2, OUTPUT);     //definindo portas para led de verificação

  digitalWrite(led2, HIGH);       //acendendo led para verificação visual de inicialização
  radio.begin();                  //iniciando comunicação radio
  radio.openWritingPipe(pipe1);   //configurando endereço para comunicação pipe
  radio.stopListening();          //bloqueando estado de leitura no módulo de rádio
  radio.setDataRate(RF24_250KBPS);//Define a taxa de transmissão

  if( !rtc.begin()){
    delay(3000);
    while(true);
  }
   
  setTimer();
  delay(3000);
  digitalWrite(led2, LOW);   //apagando led de verificação
  Serial.println("Modulo Iniciado com sucesso");
}
 
void loop() {
  DateTime now = rtc.now(); //iniciando módulo RTC para leitura
  int hora = now.hour();
  int minutos = now.minute();
  
   // if(verificaEnvioDado(hora, minutos)){
    Serial.println("Preparando dados para envio...");
    preparaStringEnvio();
    Serial.print("Dado preparado:");
    Serial.println(buf1);
    Serial.println("Enviando dados...");
    enviaDados();
  //  }
    piscaLed();
 // delay(10000);
}

//função que fica piscando o led de funcionamento ok
void piscaLed(){
  for(int i=0; i<2; i++){
    digitalWrite(led1, HIGH);  //acendendo led de funcionamento  
    delay(1000);
    digitalWrite(led1, LOW);   //apagando led de funcionamento
    delay(4000);
  }
}

//função que prepara a string a ser enviada
void preparaStringEnvio(){
  DateTime now = rtc.now();       //reiniciando módulo RTC para leitura
  DHT.read11(DHT11_PIN);          //iniciando módulo DHT para leitura de temperatura e umidade
  String temperatura, hr, minu, d, m, umidade;

  int ano = now.year();
  int um = DHT.humidity;          //atribuindo umidade a variável um
  int temp = DHT.temperature;     //atribuindo temperatura a variável temp
  
  if(now.hour()<10){
    hr = "0" + String(now.hour());
  } else {
    hr = String(now.hour());
  }
  if(now.minute()<10){
    minu = "0" + String(now.minute());
  } else {
    minu = String(now.minute());
  }
  if(now.day()<10){
    d = "0" + String(now.day());
  } else {
    d = String(now.day());
  }
  if(now.month()<10){
    m = "0" + String(now.month());
  } else {
    m = String(now.month());
  }
  if(temp<10){
    temperatura = "0" + String(temp);
  } else {
    temperatura = String(temp);
  }
  if(um<10){
    umidade = "0" + String(um);
  } else {
    umidade = String(um);
  }
  enviar = String(id)+","+d+","+m+","+String(ano)+","+hr+","+minu+","+temperatura+","+umidade;
  enviar.toCharArray(buf1, 40);  //convertendo string para char
  delay(10); //INTERVALO
}

void enviaDados(){
  if(radio.write(&buf1, sizeof(buf1))){ //escrita no pipe1 da mensagem
    memset(buf1, 0, sizeof buf1);       //limpando buffer
    digitalWrite(led2, LOW);            //apagando led para verificação
    Serial.println("Dado enviado com sucesso.");
    delay(10);
  }else{
    digitalWrite(led2, HIGH);           //acendendo led para verificação
    Serial.println("Ocorreu um erro, favor verificar.......");
    delay(1000);
  }  
}

//função que verifica se variável pode ser enviada
//retorna true se sim e false se não
boolean verificaEnvioDado(int hr, int minuts){
  if(((hr == 8) && (minuts == 0)) || ((hr == 16) && (minuts == 0)) || ((hr == 0) && (minuts == 0))) {
    return true;
  } else {
    return false;
  }
}

void setTimer(){
  //ajustando dia e hora (ano, mes, dia, hora, minutos, segundos);
 // rtc.adjust(DateTime(19, 01, 07, 01, 03, 0));
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
