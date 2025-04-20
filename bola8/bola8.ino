#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define PINO_BOTAO 2 // Pino do botão
#define PINO_RX 9  // RX do módulo MP3-TF-16P V3.0
#define PINO_TX 8  // TX do módulo MP3-TF-16P V3.0

SoftwareSerial mySoftwareSerial(PINO_RX, PINO_TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
    pinMode(PINO_BOTAO, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up
    
    Serial.begin(9600); // Inicia a comunicação serial
    mySoftwareSerial.begin(9600); // Inicia a comunicação serial com o módulo MP3
    
    if (!myDFPlayer.begin(mySoftwareSerial)) { // Inicializa o módulo MP3
        Serial.println("Erro ao iniciar o módulo MP3!"); 
        return;
    }
    
    Serial.println("Módulo MP3 iniciado com sucesso!");
    myDFPlayer.volume(30); // Ajusta o volume (0-30)
}

void loop() {
    if (digitalRead(PINO_BOTAO) == LOW) {
        delay(200); // Debounce do botão
        int numeroAleatorio = random(1, 4); // Gera um número aleatório entre 1 e 3
        myDFPlayer.playMp3Folder(numeroAleatorio); // Reproduz o arquivo de áudio correspondente
    }
}