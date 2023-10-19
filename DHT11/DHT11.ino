/*
  DHT11 - Leitura de temperatura e umidade

  Faz a leitura da temperatura e umidade do sensor DHT11 e exibe os valores no monitor serial.

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
#define DHT11_PIN 15          // Pino do DHT11
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

#include <DHT.h>          // Biblioteca do sensor DHT11

const int dhtPin = DHT11_PIN;    // Pino de conexão com o sensor DHT11
DHT dht(dhtPin, DHT11);     // Cria o objeto dht

void setup() {
  Serial.begin(9600);       // Inicializa a comunicação serial
  dht.begin();              // Inicializa o sensor DHT11
}

void loop() {
  float temperature = dht.readTemperature(); // Lê a temperatura em graus Celsius
  float humidity = dht.readHumidity();       // Lê a umidade relativa do ar

  if (!isnan(temperature) && !isnan(humidity)) {  // Verifica se os valores são válidos
    Serial.print("Temperatura: ");                // Exibe os valores no monitor serial
    Serial.print(temperature);                    
    Serial.print(" °C\t");

    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {                                                        // Caso haja algum erro na leitura
    Serial.println("Falha ao ler dados do sensor DHT11.");        // Exibe uma mensagem de erro no monitor serial
  }
  delay(2000); // Aguarda 2 segundos antes de fazer a próxima leitura
}
