# Arduinos Uno
Repositório destinado ao trabalho de comunicação entre arduínos Unos para a disciplina de Redes de Computadores SSC0142 2022/01

## Integrantes:
- 10734522 &nbsp; Amanda de Moura Peres
- 11796531 &nbsp; Israel Felipe da Silva
- 11795526 &nbsp; Tulio Santana Ramos

### Confecção
O trabalho foi realizado na linguagem C para programar o arduíno. Além do [Temporizador.h](https://github.com/Tulio-Santana-Ramos/Arduinos/blob/main/Temporizador.h) disponibilizado pela professora, utilizamos bibliotecas padrões da linguagem e o [Arduino IDE](https://www.arduino.cc/en/software) para o desenvolvimento e testagem do programa.
Nosso grupo configurou o programa de forma a ser um Emissor que utiliza Paridade Par, ou seja, nossa transmissão deve conter um número par de 1's, sendo esta a característica que determina o bit de paridade ao final da mensagem. Por sua vez, a mensagem consiste no envio de um caractere.
No [Serial.ino](https://github.com/Tulio-Santana-Ramos/Arduinos/blob/main/Serial.ino) configuramos o arduíno para variar entre 4 possíveis estados, sendo eles: **WaitingForData**, **WaitingForCTS**, **WaitingEndTrasmission** e **Transmitting**. Consistem, respectivamente, na espera por um byte pela *Serial* (*CTRL + SHIFT + M* na [Arduino IDE](https://www.arduino.cc/en/software)), na espera da ativação do **CTS** (por parte do receptor), no reconhecimento de final de transmissão (Ao receptor setar o **CTS** para **LOW**) e no efetivo envio de bits.

### Vídeo
Infelizmente, uma de nossas integrantes não pode participar das gravações pois contraiu a COVID-19.
Um vídeo para demonstrar a comunicação entre dois sistemas Arduino Uno (nosso grupo e um grupo receptor de paridade par) está disponível [aqui](https://drive.google.com/file/d/1t9GzMp9Ia9Z0nsYJRc2zZJay21RB70KG/view?usp=sharing)
