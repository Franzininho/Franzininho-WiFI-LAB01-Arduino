/*
  Botão

  Faz a leitura do estado de um botão e inverta o estado do LED vermelho quando o botão é pressionado.
  
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


const int buttonPin = BOTAO_1;  // Pino do Botão 1
const int ledPin = LED_VERMELHO;    // Pino do LED Vermelho

unsigned long debounceDelay = 50; // Atraso para evitar o efeito de bounce
unsigned long lastDebounceTime = 0; // Último tempo de debounce

int buttonState = HIGH;   // Estado atual do botão
int lastButtonState = HIGH; // Último estado do botão
int ledState = LOW;       // Estado atual do LED

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada
  pinMode(ledPin, OUTPUT);   // Configura o pino do LED como saída
}

void loop() {

  int reading = digitalRead(buttonPin);                           // Lê o estado do botão

  if (reading != lastButtonState) {                               // Verifica se o estado do botão mudou
    lastDebounceTime = millis();                                  // Atualiza o tempo de debounce
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {            // Verifica se o tempo de debounce expirou
    if (reading != buttonState) {                                 // Verifica se o estado atual da leitura é diferente do estado do botão
      buttonState = reading;                                      // Atualiza o estado do botão

      if (buttonState == LOW) {                                   // Verifica se o botão foi pressionado
        ledState = !ledState;                                     // Inverte o estado do LED
        digitalWrite(ledPin, ledState);                           // Atualiza o estado do LED
      }
    }
  }
  lastButtonState = reading;                                      // Atualiza o último estado do botão
}
