#define PINO_RX 13
#define PINO_TX 13
#define PINO_RTS 12
#define PINO_CTS 11
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h" // include disponibilizado pela professora

enum TxState
{
  WaitingForData,  // Estado em aguardo de comunicação
  WaitingForCTS,  // Estado em aguardo do CTS por parte do receptor
  WaitingEndTransmission,  // Estado em aguardo para finalização da transmissão
  Transmitting,   // Estado em transmissão de dados
};

TxState txState = WaitingForData;

// O byte a ser transmitido
char byteToSend;
// O indice do bit a ser transmitido esse ciclo.
int bitIndex;
// Contador de bits 1 transmitidos. Usado para calcular o bit de paridade.
int bitOneCount;

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){
  // Contagem e verificação dos bits
  if (bitIndex < 8) {
        // Calculo do bit a partir do char
        char mask = 1 << bitIndex;
        bool bit = (byteToSend & mask) != 0;
    
        // Envio parcial de bits
        digitalWrite(PINO_TX, bit);
        bitIndex++;
    
        // Incremeta contador de bits 1, para paridade.
        if (bit) {
          bitOneCount++;
        }
  } else {
        // Verifica quantidade de 1's e envia o último bit de acordo com o resultado
        if(bitOneCount % 2 == 1)  digitalWrite(PINO_TX, 1);
        else  digitalWrite(PINO_TX, 0);
    
        // Para-se o temporizador e limpa-se o RTS
        
        digitalWrite(PINO_RTS, LOW);
        paraTemporizador();
        txState = WaitingEndTransmission;
  }
}

// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);
  // Inicializa TX ou RX
  pinMode(PINO_TX, OUTPUT);
  pinMode(PINO_RTS, OUTPUT);
  pinMode(PINO_CTS, INPUT);
  // Configura timer
  configuraTemporizador(BAUD_RATE);
  // habilita interrupcoes
  interrupts();
}

// O loop() eh executado continuamente (como um while(true))
void loop ( ) {
  
  switch(txState)
  {
    case WaitingForData:
      // Espera um byte chegar pela serial
      if (Serial.available() > 0) {
        
        // Le o byte da serial, e inicializa globais.
        byteToSend = (char) Serial.read();
        if(byteToSend != '\n'){
          bitIndex = 0;
          bitOneCount = 0;

          // Seta o RTS, e muda para o estado esperar por CTS.
          digitalWrite(PINO_RTS, HIGH);
          txState = WaitingForCTS;
        }
      }
      break;
    
    case WaitingForCTS:
      // Espera o receptor ativar o CTS
      if (digitalRead(PINO_CTS)) {
        // Ativa o temporizador, e muda para o estado transmitir.
        iniciaTemporizador();
        txState = Transmitting;
      }
      break;
    case WaitingEndTransmission:
      // Espera o receptor setar CTS para LOW, finalizando uma transmissão
      while(digitalRead(PINO_CTS) != LOW);
      txState = WaitingForData;
      break;
    case Transmitting:
      // Apenas espera enquanto a rotina de interrupção envia os dados.
      break;
  }
}