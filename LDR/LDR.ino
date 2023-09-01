/*
  LDR 
  Controla os LEDs com base na luminosidade do ambiente. Foi utilizado um filtro de média para evitar oscilações no limiar de luminosidade.
  Alem disso foi adicionada uma histerese para evitar repetidas trocas de estado dos LEDs quando a luminosidade está próxima do limiar.

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

const int ldrPin = LDR;       // Pino do LDR
const int ledPins[] = {LED_VERMELHO, LED_VERDE, LED_AZUL}; // Pinos dos LEDs Vermelho, Verde e Azul

const int numReadings = 10; // Número de leituras para a média
int readings[numReadings];  // Armazena as leituras do LDR
int indice = 0;              // Índice atual das leituras
long total = 0;             // Soma das leituras para cálculo da média

int ledThreshold = 500;     // Limiar de luminosidade para acender os LEDs
int hysteresis = 50;        // Histerese para evitar oscilações

void setup() {
  pinMode(ldrPin, INPUT); // Configura o pino do LDR como entrada

  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT);                                      // Configura os pinos dos LEDs como saída
  }

  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  // Leitura do LDR e filtro de média
  total = total - readings[indice];         // Subtrai o valor mais antigo
  readings[indice] = analogRead(ldrPin)>>3; //desloca 3 bits para deixar valor em 10 bits 
  total = total + readings[indice];         // Adiciona o valor mais recente
  indice = (indice + 1) % numReadings;      // Avança para o próximo índice
  int average = total / numReadings;        // Calcula a média

  // Controle dos LEDs baseado na luminosidade
  if (average < ledThreshold + hysteresis) {                          // Se a luminosidade for menor que o limiar + histerese
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {  // Percorre todos os LEDs
      digitalWrite(ledPins[i], HIGH); // Acende os LEDs               // Acende os LEDs RGB - cor branca  
    }
  } else if (average > ledThreshold - hysteresis) {                   // Se a luminosidade for maior que o limiar - histerese
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {  // Percorre todos os LEDs
      digitalWrite(ledPins[i], LOW);                                  // Apaga os LEDs
    }
  }

  // Imprime o valor da luminosidade no monitor serial
  Serial.print("Luminosidade: ");
  Serial.println(average);

  delay(100); // Pequeno atraso para evitar atualizações muito rápidas
}
