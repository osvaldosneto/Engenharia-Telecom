#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define senha "xx"
#define led1 D3      //led de inicialização se estiver tudo ok!!!!
#define led2 D2      //led de aguardo de inicialização!!!!

RF24 radio(D4,D8);                      //definindo portas CE e CSN
WiFiServer server(80); 

const char* ssid = "Osneto";            //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "osvaldo1983";   //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR
const char* url = "http://104.154.254.106/medicoes";

const uint64_t pipe1 = 0xE14BC8F482LL;  //endereço de comunicação para abertura de pipe
char recebidos[32];                     //variável que receberá a mensagem a enviar

String enviarServidor = "";
int i=0;

void setup()
{ 
  pinMode(led1, OUTPUT);     //definindo portas para led de verificação
  pinMode(led2, OUTPUT);     //definindo portas para led de verificação
  digitalWrite(led2, HIGH);       //acendendo led para verificação visual de inicialização
  Serial.begin(115200);
  Serial.println("Iniciando configuração WIFI...");
  Serial.println("Iniciando configuração radio...");
  radio.begin();                     //Inicializa a comunicaçao entre os módulos
  radio.openReadingPipe(1, pipe1);   //Entra em modo de recepcao
  radio.startListening();            //Entra em modo de recepcao
  radio.setDataRate(RF24_250KBPS);   //Define a taxa de transmissão
  Serial.println("Radio configurado");

  WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500); //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
    //acender led vermelho
  }
  server.begin();
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH);  
  //acender led verde
  Serial.print("Conectado a rede WIFI "); 
  Serial.println(ssid); 
  Serial.print("http://"); //ESCREVE O TEXTO NA SERIAL
  Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)
}
void loop(){
  if (radio.available()){     
    Serial.println("Sinal recebido....");              
    radio.read(&recebidos, sizeof(recebidos));  //lendo informações contidas no pipe1 e armazenando em recebidos
    Serial.print("Recebendo dado: ");
    Serial.println(recebidos);
    Serial.println("Iniciando formatação json da mensagem recebida ....");
    tratamentoRecebido();
    if(enviarServidor.length()>0){
      Serial.print("Formato Json:");
      Serial.println(enviarServidor);
      enviandoServidor();
    }
  }
  
  delay(1000);    //delay para estabilização do sistema
}

void tratamentoRecebido(){
  enviarServidor = "{ \"id\": \"" + String(recebidos[0]) + "\", \"s\": \"" + senha + "\", \"u\": " + String(recebidos[22])+String(recebidos[23])+
                    ", \"t\": " + String(recebidos[19])+String(recebidos[20]) + ", \"data\": \""+String(recebidos[2])+String(recebidos[3])+"/"+String(recebidos[5])+
                    String(recebidos[6])+"/"+String(recebidos[8])+String(recebidos[9])+String(recebidos[10])+String(recebidos[11])+" "+String(recebidos[13])+String(recebidos[14])+":"+
                    String(recebidos[16])+String(recebidos[17])+ "\" }";
}

void enviandoServidor(){
  String payload;
  int httpCode;
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(enviarServidor);
    payload = http.getString();
  }
  Serial.print("Payload:");
  Serial.println(payload);
  Serial.print("httpCode:");
  Serial.println(httpCode);
  if(httpCode==201){
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH);  
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH); 
  }
}
