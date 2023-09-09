/*
  Blink LED Sequencial

  Pisca os LEDs sequencialmente em intervalos de 1 segundo entre eles.
  
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


// Definindo os pinos dos LEDs
const int ledPins[] = {LED_VERMELHO, LED_VERDE,LED_AZUL}; // Pinos dos LEDs Vermelho, Verde e Azul

void setup() {
  // Configurando os pinos dos LEDs como saídas
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {    //loop para configurar os pinos dos LEDs
    pinMode(ledPins[i], OUTPUT);                                      //configura o pino como saída
  }
}

void loop() {
  // Fazendo cada LED piscar sequencialmente
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    digitalWrite(ledPins[i], HIGH);                                 // Ligando o LED
    delay(1000);                                                    // Aguardando 1 segundo
    digitalWrite(ledPins[i], LOW);                                  // Desligando o LED
    delay(1000);                                                    // Aguardando 1 segundo entre os LEDs
  }
}
