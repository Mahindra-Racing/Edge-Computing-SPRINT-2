#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

const int startButtonPin = 5; // Botão para iniciar e calcular a média dos pit stops
const int resetButtonPin = 4; // Botão para resetar

unsigned long startTime = 0; // Tempo de início
bool timerActive = false; // Estado do timer
int pitStopCount = 0; // Contador de pit stops
unsigned long pitStops[5][2]; // Array para armazenar tempos de pit stops

void setup() {
  Serial.begin(115200);
  LCD.init();
  LCD.backlight();
  
  pinMode(startButtonPin, INPUT_PULLUP); // Configura o pino do botão de iniciar
  pinMode(resetButtonPin, INPUT_PULLUP); // Configura o pino do botão de resetar

  LCD.setCursor(0, 0);
  LCD.print("Aguardando inicio");
}

void loop() {
  checkButtons();

  if (timerActive) {
    unsigned long elapsedTime = millis() - startTime; // Calcula o tempo decorrido
    LCD.setCursor(0, 1);
    LCD.print("Tempo: ");
    LCD.print(elapsedTime / 1000); // Segundos
    LCD.print(" s ");
    LCD.print(elapsedTime % 1000); // Milissegundos
    LCD.print(" ms");
  }
}

void checkButtons() {
  // Verifica o botão de iniciar
  if (digitalRead(startButtonPin) == LOW) {
    delay(50); // Debounce
    if (digitalRead(startButtonPin) == LOW) {
      if (timerActive) {
        if (pitStopCount < 5) {
          pitStops[pitStopCount][0] = (millis() - startTime) / 1000; // Segundos
          pitStops[pitStopCount][1] = (millis() - startTime) % 1000; // Milissegundos
          pitStopCount++;
        }
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Pitstop #");
        LCD.print(pitStopCount);
        LCD.print(": ");
        LCD.print(pitStops[pitStopCount - 1][0]);
        LCD.print("s ");
        LCD.print(pitStops[pitStopCount - 1][1]);
        LCD.print("ms");
        timerActive = false; // Para o timer
      } else {
        timerActive = true; // Inicia o timer
        startTime = millis(); // Reseta o tempo de início
      }
      delay(250); // Espera para evitar múltiplos acionamentos
    }
  }

  // Verifica o botão de resetar
  if (digitalRead(resetButtonPin) == LOW && !timerActive) {
    delay(50); // Debounce
    if (digitalRead(resetButtonPin) == LOW) {
      if (pitStopCount > 0) {
        unsigned long totalSeconds = 0, totalMilliseconds = 0;
        
        for (int i = 0; i < pitStopCount; i++) {
          totalSeconds += pitStops[i][0];
          totalMilliseconds += pitStops[i][1];
        }

        // Calcula a média dos pit stops
        unsigned long averageSeconds = totalSeconds / pitStopCount;
        unsigned long averageMilliseconds = totalMilliseconds / pitStopCount;

        // Exibe a média no LCD
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Media: ");
        LCD.print(averageSeconds); // Média dos segundos
        LCD.print("s ");
        LCD.print(averageMilliseconds); // Média dos milissegundos
        LCD.print("ms");

        // Reseta os pit stops
        pitStopCount = 0; 
      }
      delay(250); // Espera para evitar múltiplos acionamentos
    }
  }
}
