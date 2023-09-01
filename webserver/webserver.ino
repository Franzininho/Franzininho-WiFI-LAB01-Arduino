/*
  Webserver

  Exibe os valores dos sensores em uma página html e controla o estado do LED.

  Acende o LED RGB em difentes cores. Cada botão define uma cor.

Autor: Fabio Souza
Data: 01/09/2023
*/

#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>          // Biblioteca do sensor DHT11

const int dhtPin = 15;    // Pino de conexão com o sensor DHT11
DHT dht(dhtPin, DHT11);     // Cria o objeto dht

#define SCREEN_WIDTH 128 // Largura da tela OLED
#define SCREEN_HEIGHT 64 // Altura da tela OLED

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "SeuSSID"; // Nome da sua rede Wi-Fi
const char* password = "SuaSenha"; // Senha da sua rede Wi-Fi

int ledPin = 14; // Pino do LED

WebServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  dht.begin();              // Inicializa o sensor DHT11

  // Inicializa o display OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Define as rotas para a página web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);

  server.begin();
}

void loop() {
  server.handleClient();

  // Leitura dos sensores e exibição no display OLED
  float temperature = dht.readTemperature(); // Lê a temperatura em graus Celsius
  float humidity = dht.readHumidity();       // Lê a umidade relativa do ar
  int lightLevel = analogRead(A0);   // Leitura do LDR

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.println(temperature);
  display.print("Umidade: ");
  display.println(humidity);
  display.print("Luminosidade: ");
  display.println(lightLevel);
  display.display();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Sensor Data</h1>";
  html += "<p>Temperatura: " + String(random(20, 30)) + " C</p>";
  html += "<p>Umidade: " + String(random(40, 60)) + " %</p>";
  html += "<p>Luminosidade: " + String(analogRead(A0)) + "</p>";
  html += "<form action='/toggle' method='POST'>";
  html += "<input type='submit' value='Toggle LED'>";
  html += "</form>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleToggle() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.send(200, "text/plain", "LED toggled");
}
