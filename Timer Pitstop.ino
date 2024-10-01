#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int igomb = 2; // Botão para iniciar e calcular a média dos pit stops
const int tgomb = 4; // Botão para resetar

unsigned long iido = 0; // Tempo de início
unsigned long tido = 0; // Tempo decorrido
bool idozito = false; // Estado do timer (ativo/inativo)

const int maxPitStops = 5; // Número máximo de pit stops a serem armazenados
unsigned long pitStops[maxPitStops][2]; // Array para armazenar tempos de pit stops (segundos, milissegundos)
int pitStopCount = 0; // Contador de pit stops

void setup() {
  pinMode(igomb, INPUT_PULLUP); // Configura o pino do botão de iniciar
  pinMode(tgomb, INPUT_PULLUP); // Configura o pino do botão de resetar
  lcd.begin(16, 2); // Inicializa o LCD
}

void loop() {
  gomb(); // Verifica os botões
  if (idozito) {
    tido = millis() - iido; // Calcula o tempo decorrido em milissegundos

    // Converte milissegundos em segundos e milissegundos
    unsigned long segundos = tido / 1000; // Calcula os segundos
    unsigned long milissegundos = tido % 1000; // Calcula os milissegundos restantes

    lcd.setCursor(0, 0);
    lcd.print("Tempo: ");
    lcd.print(segundos); // Mostra os segundos
    lcd.print(" s "); // Adiciona a unidade de segundos
    lcd.print(milissegundos); // Mostra os milissegundos
    lcd.print(" ms"); // Adiciona a unidade de milissegundos
  }
}

void gomb() {
  // Verifica o botão de iniciar/cálculo da média
  if (digitalRead(igomb) == LOW) {
    delay(50); // Debounce
    if (digitalRead(igomb) == LOW) {
      if (idozito) {
        // Armazena o tempo do pit stop
        unsigned long pitStopTime = millis() - iido; // Calcula o tempo atual desde o início
        if (pitStopCount < maxPitStops) {
          pitStops[pitStopCount][0] = pitStopTime / 1000; // Armazena os segundos
          pitStops[pitStopCount][1] = pitStopTime % 1000; // Armazena os milissegundos
          pitStopCount++; // Incrementa o contador de pit stops
        }
        
        // Mostra o último pit stop no LCD
        lcd.clear(); // Limpa o display
        lcd.setCursor(0, 0);
        lcd.print("#");
        lcd.print(pitStopCount); // Mostra o número do pit stop
        lcd.print(" Pitstop: ");
        lcd.print(pitStops[pitStopCount - 1][0]); // Segundos do último pit stop
        lcd.print("s ");
        lcd.print(pitStops[pitStopCount - 1][1]); // Milissegundos do último pit stop
        lcd.print("ms");

        idozito = false; // Para o timer
      } else {
        idozito = true; // Inicia o timer
        iido = millis(); // Reseta o tempo de início para agora
      }
      delay(250); // Espera para evitar múltiplos acionamentos
    }
  }

  // Verifica o botão de resetar
  if (digitalRead(tgomb) == LOW && !idozito) {
    delay(50); // Debounce
    if (digitalRead(tgomb) == LOW) {
      // Calcula e exibe a média dos pit stops
      if (pitStopCount > 0) {
        unsigned long totalSegundos = 0;
        unsigned long totalMilissegundos = 0;
        
        for (int i = 0; i < pitStopCount; i++) {
          totalSegundos += pitStops[i][0];
          totalMilissegundos += pitStops[i][1];
        }

        // Converte total para média
        unsigned long mediaSegundos = totalSegundos / pitStopCount;
        unsigned long mediaMilissegundos = totalMilissegundos / pitStopCount;

        // Exibe a média no LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Media: ");
        lcd.print(mediaSegundos); // Mostra a média dos segundos
        lcd.print("s ");
        lcd.print(mediaMilissegundos); // Mostra a média dos milissegundos
        lcd.print("ms");

        // Reseta os pit stops
        pitStopCount = 0;
      }
      delay(250); // Espera para evitar múltiplos acionamentos
    }
  }
}
