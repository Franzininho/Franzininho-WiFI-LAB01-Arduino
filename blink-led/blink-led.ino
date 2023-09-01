/*
  Blink LED - Sem delay

 LED vermelho piscará em intervalos de 1 segundo sem bloquear a execução de outras partes do código.
 Utilizamos a função millis() para obter o tempo atual em milissegundos. 
 Comparamos esse tempo com o previousMillis e, se o intervalo definido tiver passado, 
 atualizamos previousMillis para o tempo atual e invertemos o estado do LED usando a variável ledState.

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

#define TEMPO 1000    // Intervalo de piscagem (em milissegundos)

const int ledPin = LED_VERMELHO; // Pino do LED Vermelho
unsigned long previousMillis = 0; // Armazena o tempo da última mudança de estado do LED

int ledState = LOW; // Estado atual do LED

void setup() {
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void loop() {
  unsigned long currentMillis = millis(); // Obtém o tempo atual

  if (currentMillis - previousMillis >= TEMPO) {  // Verifica se o intervalo de tempo definido passou desde a última mudança de estado
    previousMillis = currentMillis;               // Atualiza o tempo da última mudança

    // Inverte o estado do LED
    if (ledState == LOW) {
      ledState = HIGH;                           // Se o LED está apagado, acende
    } else {
      ledState = LOW;                           // Se o LED está aceso, apaga
    }
    digitalWrite(ledPin, ledState); // Aplica o novo estado ao LED
  }
}
