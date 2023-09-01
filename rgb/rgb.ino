/*
  RGB

  Acende o LED RGB em difentes cores. Cada botão define uma cor.

Autor: Fabio Souza
Data: 01/09/2023
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

const int buttonPins[] = {BOTAO_1, BOTAO_2, BOTAO_3, BOTAO_4, BOTAO_5, BOTAO_6}; // Pinos dos Botões 1 a 6
const int redPin = LED_VERMELHO;    // Pino do LED Vermelho
const int greenPin = LED_VERDE;  // Pino do LED Verde
const int bluePin = LED_AZUL;   // Pino do LED Azul

int buttonColors[][3] = {
  {255, 0, 0},   // Vermelho (R, G, B)
  {0, 255, 0},   // Verde (R, G, B)
  {0, 0, 255},   // Azul (R, G, B)
  {255, 255, 0}, // Amarelo (R, G, B)
  {0, 255, 255}, // Ciano (R, G, B)
  {255, 0, 255}  // Magenta (R, G, B)
};

void setup() {
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Configura os pinos dos botões como entrada com pull-up
  }

  pinMode(redPin, OUTPUT);   // Configura o pino do LED Vermelho como saída
  pinMode(greenPin, OUTPUT); // Configura o pino do LED Verde como saída
  pinMode(bluePin, OUTPUT);  // Configura o pino do LED Azul como saída
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);     // Define a intensidade do LED Vermelho
  analogWrite(greenPin, green); // Define a intensidade do LED Verde
  analogWrite(bluePin, blue);   // Define a intensidade do LED Azul
}

void loop() {
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      // Define a cor com base no botão pressionado
      setColor(buttonColors[i][0], buttonColors[i][1], buttonColors[i][2]);
      delay(500); // Pequeno atraso para evitar leituras múltiplas do botão
    }
  }
}
