#include "mp3tf16p.h"
#include "DFRobotDFPlayerMini.h"
#include "stdlib.h"

MP3Player mp3(10, 11); // RX e TX para comunicação com o DFPlayer Mini

const int pin_botao = 2; // Pino onde o botão está conectado
bool ultimo_estado = HIGH; // Estado anterior do botão (HIGH porque usamos INPUT_PULLUP)
int n_aleatorio = 0;

void setup() {
  // Configuração do monitor serial
  Serial.begin(9600);

  // Configuração do botão
  pinMode(pin_botao, INPUT_PULLUP); // Configura o botão como entrada com pull-up interno

  // Configuração do MP3Player
  mp3.initialize(); // Inicializa o MP3Player

  Serial.println("Pressione o botão para reproduzir um som aleatório.");
}

void loop() {
  // Lê o estado atual do botão
  bool estado_atual = digitalRead(pin_botao);

  // Detecta a transição de "não pressionado" (HIGH) para "pressionado" (LOW)
  if (ultimo_estado == HIGH && estado_atual == LOW) {
    Serial.println("Botão pressionado!");

    // Gera um número aleatório entre 1 a 29 (ajuste conforme o número de faixas no SD)
    n_aleatorio = 1 + rand()% 5;

    Serial.print("Reproduzindo faixa: ");
    Serial.println(n_aleatorio);

    // Reproduz a faixa aleatória com volume 30
    mp3.playTrackNumber(n_aleatorio, 30);

    delay(500); // Pequeno atraso para evitar múltiplas leituras
  }

  // Atualiza o estado anterior do botão
  ultimo_estado = estado_atual;
}
