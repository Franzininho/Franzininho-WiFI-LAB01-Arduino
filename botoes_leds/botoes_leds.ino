/*
  Botões e LEDs

Esse exemplo controla três LEDs usando três botões.
Cada Botão (1, 2 e 3) controlará o seu respectivo LED (Vermelho, Verde e Azul), invertendo o estado do LED a cada pressionamento do botão.

Autor: Fabio Souza
Data: 30/08/2023
*/

//mapeamento de pinos
#define LED_VERMELHO 14   // Pino do LED Vermelho
#define LED_VERDE 13      // Pino do LED Verde
#define LED_AZUL 12       // Pino do LED Azul
#define BOTAO_1 7         // Pino do Botão 1
#define BOTAO_2 6         // Pino do Botão 2
#define BOTAO_3 5         // Pino do Botão 3
#define BOTAO_4 4         // Pino do Botão 4
#define BOTAO_5 3         // Pino do Botão 5
#define BOTAO_6 2         // Pino do Botão 6
#define BUZZER 17         // Pino do Buzzer
#define DHT11 15          // Pino do DHT11
#define LDR 1             // Pino do LDR
#define OLED_SDA 8        // Pino SDA do OLED
#define OLED_SCL 9        // Pino SCL do OLED

//mapeamento de botões
#define BT_UP BOTAO_1     // Botão UP - botão 1
#define BT_DOWN BOTAO_4   // Botão DOWN - botão 4
#define BT_LEFT BOTAO_2   // Botão LEFT - botão 2
#define BT_RIGHT BOTAO_3  // Botão RIGHT - botão 3
#define BT_A BOTAO_6      // Botão A - botão 6
#define BT_B BOTAO_5      // Botão B - botão 5

const int buttonPin[] = {BOTAO_1, BOTAO_2, BOTAO_3};  // Pinos dos Botões 1, 2 e 3
const int ledPin[] = {LED_VERMELHO, LED_VERDE, LED_AZUL};  // Pinos dos LEDs Vermelho, Verde e Azul

unsigned long debounceDelay = 50; // Atraso para evitar o efeito de debounce
unsigned long lastDebounceTime[] = {0, 0, 0}; // Último tempo de debounce para cada botão

int buttonState[] = {HIGH, HIGH, HIGH};   // Estado atual de cada botão
int lastButtonState[] = {HIGH, HIGH, HIGH}; // Último estado de cada botão
int ledState[] = {LOW, LOW, LOW};       // Estado atual de cada LED

// Configuração inicial
void setup() {
  for (int i = 0; i < sizeof(buttonPin) / sizeof(buttonPin[0]); i++) {
    pinMode(buttonPin[i], INPUT_PULLUP); // Configura os pinos dos botões como entrada
    pinMode(ledPin[i], OUTPUT);   // Configura os pinos dos LEDs como saída
  }
}

// Loop principal
void loop() {
  for (int i = 0; i < sizeof(buttonPin) / sizeof(buttonPin[0]); i++) {  // Para cada botão
    int reading = digitalRead(buttonPin[i]);                            // Lê o estado do botão

    if (reading != lastButtonState[i]) {                                // Se o estado do botão mudou
      lastDebounceTime[i] = millis();                                   // Atualiza o tempo de debounce
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {             // Se o tempo de debounce passou
      if (reading != buttonState[i]) {                                  // Se o estado do botão mudou
        buttonState[i] = reading;                                       // Atualiza o estado do botão

        if (buttonState[i] == LOW) {                                    // Se o botão foi pressionado
          ledState[i] = !ledState[i];                                   // Inverte o estado do LED
          digitalWrite(ledPin[i], ledState[i]);                         // Atualiza o estado do LED
        }
      }
    }
    lastButtonState[i] = reading;                                       // Atualiza o último estado do botão
  }
}
