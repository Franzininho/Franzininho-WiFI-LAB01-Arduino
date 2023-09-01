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

const int ldrPin = LDR;     // Pino do LDR
const int buzzerPin = BUZZER;  // Pino do Buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT); // Configura o pino do Buzzer como saída
  Serial.begin(9600);        // Inicializa a comunicação serial
}

void loop() {
  int lightLevel = analogRead(ldrPin); // Lê o valor do LDR

  // Mapeia o valor da luminosidade para uma faixa de frequência
  int frequency = map(lightLevel, 0, 8191, 60 , 2000);

  // Gera um som no Buzzer com a frequência calculada
  tone(buzzerPin, frequency);

  // Exibe o valor da luminosidade no monitor serial
  Serial.print("Luminosidade: ");
  Serial.println(lightLevel);

  delay(10); // Pequeno atraso
}
