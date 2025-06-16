/*
  T-Rex Gamne para Franzininho WiFi LAB01

  Este é um jogo simples inspirado no famoso jogo do T-Rex do Google Chrome.
  O objetivo é pular os obstáculos (árvores) que aparecem na tela.  
  O jogo termina quando o T-Rex colide com uma árvore.
  O jogo é controlado por um botão, que quando pressionado faz o T-Rex pular.
  O jogo exibe a pontuação atual na tela OLED e toca um som quando o botão é pressionado.

  Baseado no exemplo: https://www.harshmittal.com/tutorials/Chrome-Dino-Game/

  Adaptador por Fábio Souza
  https://franzininho.com.br
  Data: 23/06/2024
*/


// Mapa de pinos do Franzininho WiFi LAB01
#define LED_VERMELHO 14   // Pino do LED Vermelho
#define LED_VERDE 13      // Pino do LED Verde
#define LED_AZUL 12       // Pino do LED Azul
#define BOTAO_1 7         // Pino do Botão 1
#define BOTAO_2 6         // Pino do Botão 2
#define BOTAO_3 5         // Pino do Botão 3
#define BOTAO_4 4         // Pino do Botão 4
#define BOTAO_5 3         // Pino do Botão 5
#define BOTAO_6 2         // Pino do Botão 6


// Bibliotecas necessárias
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definições do display OLED
#define SCREEN_WIDTH 128      // largura do display OLED, em pixels
#define SCREEN_HEIGHT 64      // altura do display OLED, em pixels
#define OLED_RESET     -1     // Reset do display OLED, -1 se não for usado
#define SCREEN_ADDRESS 0x3C   // Endereço I2C do display OLED

// Definições do jogo
#define DINO_WIDTH 25   // Largura do T-Rex
#define DINO_HEIGHT 26  // Altura do T-Rex
#define DINO_INIT_X 10  // Posição inicial do T-Rex no eixo X
#define DINO_INIT_Y 29  // Posição inicial do T-Rex no eixo Y

#define BASE_LINE_X 0     // Posição inicial da linha base no eixo X
#define BASE_LINE_Y 54    // Posição inicial da linha base no eixo Y
#define BASE_LINE_X1 127  // Posição final da linha base no eixo X
#define BASE_LINE_Y1 54   // Posição final da linha base no eixo Y

#define TREE1_WIDTH 11    // Largura da árvore 1
#define TREE1_HEIGHT 23   // Altura da árvore 1

#define TREE2_WIDTH 22    // Largura da árvore 2
#define TREE2_HEIGHT 23   // Altura da árvore 2

#define TREE_Y 35   // Posição Y das árvores

#define JUMP_PIXEL 22 // Quantidade de pixels que o T-Rex sobe ao pular

// Inicialização do display OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bitmap do T-Rex
static const unsigned char PROGMEM dino1[]={
  // 'dino', 25x26px
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00, 
0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00, 
0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00, 
0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00, 
0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 
0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 
0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00
};

// Bitmap das árvores
static const unsigned char PROGMEM tree1[]={
  // 'tree1', 11x23px
0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 
0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00, 
0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00
};

// Bitmap da segunda árvore
static const unsigned char PROGMEM tree2[]={
  // 'tree2', 22x23px
0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf, 
0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 
0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0, 
0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 
0x03, 0xe0, 0x1f, 0x03, 0xe0
};


const int buttonPin = BOTAO_6;      // Pino do Botão 6 (usado para iniciar o jogo)
int previousButtonState = HIGH;     // Estado anterior do botão (inicialmente HIGH)
const int buzzerPin = 17;           // Pino do Buzzer

void beep() {
  //digitalWrite(buzzerPin, HIGH); // Liga o buzzer
  tone(buzzerPin, 440); // Toca um som de 440 Hz (Lá)
  delay(100);           // Mantém o buzzer ligado por 100 ms
  //digitalWrite(buzzerPin, LOW); // Desliga o buzzer
  noTone(buzzerPin);
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  pinMode(buzzerPin, OUTPUT);       // Configura o pino do buzzer como saída
  beep();

  // Inicializa o display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); 
    for(;;); // Não continua se o display não for inicializado
  }

  // Configura o display 
  display.clearDisplay();

  introMessage(); // Exibe a mensagem de introdução

}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if ((buttonState != previousButtonState) && (buttonState == LOW)) 
  {
    beep();
    while(digitalRead(buttonPin) == LOW);
    play();

  }
    previousButtonState = buttonState;
}

// Função para exibir a mensagem de introdução
void introMessage(){
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,5);
  display.println("T-Rex Game");
  display.drawBitmap(50, 22, dino1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
  display.setTextSize(1);  
  display.setCursor(0,52);
  display.println("    Press To Play");
  display.display();
}

// Função para mover o T-Rex
void moveDino(int16_t *y, int type=0){
  display.drawBitmap(DINO_INIT_X, *y, dino1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
}

// Função para mover as árvores
void moveTree(int16_t *x, int type=0){
  if(type==0){
    display.drawBitmap(*x, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, SSD1306_WHITE);
  }
  else if(type==1){
    display.drawBitmap(*x, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, SSD1306_WHITE);
  }
  
}

// Função para exibir a tela de Game Over
void gameOver(int score=0){
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,5);
  display.println("GAME OVER");
  display.setTextSize(1);
  display.setCursor(10,30);
  display.print("     Score: ");
  display.print(score);  
  display.setCursor(0,55);
  display.println("  franzininho.com.br");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  introMessage();
}

// Função para exibir a pontuação
void displayScore(int score){
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print(score);
}

// Função principal do jogo
void play(){

  int16_t tree_x=127;
  int16_t tree1_x=195;
  int tree_type = random(0,2);
  int tree_type1 = random(0,2);

  int16_t dino_y = DINO_INIT_Y;
  int input_command;
  int jump=0;

  int score=0;
  
  for(;;){
    display.clearDisplay();

    int buttonState = digitalRead(buttonPin);
    if ((buttonState != previousButtonState) && (buttonState == LOW)) {
      beep();
      Serial.println("Jump");
        if(jump==0) jump=1;
  }
    previousButtonState = buttonState;

    if(jump==1){
      dino_y--;
      if(dino_y== (DINO_INIT_Y-JUMP_PIXEL)){
        jump=2;
        //score++;
      }
    }
    else if(jump==2){
      dino_y++;
      if(dino_y== DINO_INIT_Y){
        jump=0; 
      }
    }

    if(tree_x<= (DINO_INIT_X+DINO_WIDTH) && tree_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
      if(dino_y>=(DINO_INIT_Y-3)){
        Serial.println("Collision Happend");  // Sinaliza uma colisão
        break;
      }    
    }

    if(tree1_x<= (DINO_INIT_X+DINO_WIDTH) && tree1_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
      if(dino_y>=(DINO_INIT_Y-3)){
        Serial.println("Collision Happend");  // Sinaliza uma colisão
        break;
      }    
    }

    displayScore(score);
    moveTree(&tree_x,tree_type);
    moveTree(&tree1_x,tree_type1);
    moveDino(&dino_y);
    display.drawLine(0, 54, 127, 54, SSD1306_WHITE);
    

    tree_x--;
    tree1_x--;
    if(tree_x==0) {
      tree_x = 127;
      tree_type = random(0,1);
      score++;
    }

    if(tree1_x==0) {
      tree1_x = 195;
      tree_type1 = random(0,1);
      score++;
    }
    display.display();
  }

  Serial.println("Game Over");
  gameOver(score);
}

// Função para renderizar a cena inicial
void renderScene(int16_t i=0){
  display.drawBitmap(10, 29, dino1, 25, 26, SSD1306_WHITE);
  display.drawBitmap(50, TREE_Y, tree1, 11, 23, SSD1306_WHITE);
  display.drawBitmap(100, TREE_Y, tree2, 22, 23, SSD1306_WHITE);
  display.drawLine(0, 54, 127, 54, SSD1306_WHITE);
  display.drawPixel(i, 60, SSD1306_WHITE);
}
