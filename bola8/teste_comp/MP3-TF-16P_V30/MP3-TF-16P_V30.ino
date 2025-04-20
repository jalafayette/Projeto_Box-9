#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define PINO_CS 4  // Pino do chip select do cartão SD
#define PINO_RX 9  // RX do módulo MP3-TF-16P V3.0
#define PINO_TX 8  // TX do módulo MP3-TF-16P V3.0

SoftwareSerial mySerial(PINO_RX, PINO_TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDirectory(File dir, int numTabs) {
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            // No more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++) {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void setup() {
    // Inicializa a comunicação serial a 9600 bps
    Serial.begin(9600);
    // Aguarda a inicialização da porta serial
    while (!Serial) {
        ; // Aguarda até que a porta serial esteja pronta
    }
    Serial.println("Iniciando o teste de loopback...");
    pinMode(PINO_CS, OUTPUT);

    if (!SD.begin(PINO_CS)) {
        Serial.println("Erro ao iniciar o cartão SD!");
        return;
    }
    
    Serial.println("Cartão SD iniciado com sucesso!");

    // Listar arquivos no cartão SD
    File root = SD.open("/");
    printDirectory(root, 0);
    root.close();

    mySerial.begin(9600); // Inicia a comunicação serial com o módulo MP3
    
    Serial.println("Inicializando o módulo MP3...");
    
    if (!myDFPlayer.begin(mySerial)) { // Inicializa o módulo MP3
        Serial.println("Erro ao iniciar o módulo MP3!"); 
        while (true); // Para o programa
    }
    
    Serial.println("Módulo MP3 iniciado com sucesso!");
    myDFPlayer.volume(20); // Ajusta o volume (0-30)
}

void loop() {
    // Verifica se há dados disponíveis para leitura
    if (Serial.available() > 0) {
        // Lê o byte recebido
        char received = Serial.read();
        // Envia o byte de volta
        Serial.print("Recebido: ");
        Serial.println(received);
    }

    // Envia um byte de teste a cada segundo
    Serial.print("Enviando: ");
    Serial.println('A');
    Serial.write('A');
    delay(1000);

    // Teste simples para reproduzir o primeiro arquivo de áudio
    myDFPlayer.play(1); // Reproduz o arquivo "1.mp3"
    delay(10000); // Aguarda 10 segundos antes de repetir
}

