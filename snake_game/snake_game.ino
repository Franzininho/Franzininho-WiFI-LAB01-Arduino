/*
  Snake Game
  
  Jogo da cobrinha com contador de pontos

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

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH        128 // Largura da tela OLED, em pixels
#define SCREEN_HEIGHT        64 // altura da tela OLED, em pixels

#define OLED_RESET            -1 // Pino de reset do display, -1 se não houver
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Inicia Display OLED

const byte buttonPins[] = {BT_LEFT, BT_UP, BT_RIGHT, BT_DOWN}; // LEFT, UP, RIGHT, DOWN

typedef enum {      // Estados do jogo
  START,            // Início
  RUNNING,          // Rodando
  GAMEOVER          // Game Over
} State;            // Tipo de dado State

typedef enum {      // Direções
    LEFT,           // Esquerda
    UP,             // Cima
    RIGHT,          // Direita
    DOWN            // Baixo
} Direction;        // Tipo de dado Direction

#define SNAKE_PIECE_SIZE     3
#define MAX_SANKE_LENGTH   165
#define MAP_SIZE_X          35
#define MAP_SIZE_Y          20
#define STARTING_SNAKE_SIZE  5
#define SNAKE_MOVE_DELAY    30

State gameState;                  // Variável que guarda o estado atual do jogo

int8_t snake[MAX_SANKE_LENGTH][2];  // Vetor que guarda as posições da cobra
uint8_t snake_length;               // Tamanho da cobra
Direction dir;                      // Direção atual da cobra
Direction newDir;                   // Direção que a cobra irá seguir no próximo movimento

int8_t fruit[2];                    // Posição da fruta

int moveTime = 0;   // Variável para contar o tempo de movimento da cobra


void setup() {
  Serial.begin(9600);                                 // Inicia a comunicação serial

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {    // Inicia o display OLED
    Serial.println(F("SSD1306 allocation failed"));   // Se falhar, mostra mensagem de erro
    for(;;);                                          // Trava o programa
  }

  for (byte i = 0; i < sizeof(buttonPins)/sizeof(buttonPins[0]); i++) { // Configura os pinos dos botões
    pinMode(buttonPins[i], INPUT_PULLUP);                               // Habilita o resistor de pull-up interno
  }

  pinMode(BUZZER, OUTPUT);                                              // Configura o pino do buzzer como saída
  randomSeed(analogRead(A0));                                           // Inicia o gerador de números aleatórios
  setupGame();                                                          // Inicia o jogo
}

/*
Função para configurar o jogo
*/
void setupGame() {
  gameState = START;        // Inicia o jogo no estado START
  dir = RIGHT;              // Inicia a direção da cobra para a direita
  newDir = RIGHT;           // Inicia a direção que a cobra irá seguir no próximo movimento para a direita
  resetSnake();             // Reseta a cobra
  generateFruit();          // Gera a fruta
  display.clearDisplay();   // Limpa o display
  drawMap();                // Desenha o mapa
  drawScore();              // Desenha a pontuação
  drawPressToStart();       // Desenha a mensagem de pressione para iniciar
  display.display();        // Mostra o que foi desenhado no display
}

/*
Função para resetar a cobra
*/
void resetSnake() {
  snake_length = STARTING_SNAKE_SIZE;         // Inicia o tamanho da cobra
  for(int i = 0; i < snake_length; i++) {     // Para cada pedaço da cobra
    snake[i][0] = MAP_SIZE_X / 2 - i;         // Inicia a posição X
    snake[i][1] = MAP_SIZE_Y / 2;             // Inicia a posição Y
  }
}


void loop() {

  switch(gameState) {                           // Verifica o estado atual do jogo
    case START:                                 // Se for START
      if(buttonPress()) gameState = RUNNING;    // Se algum botão for pressionado, muda o estado para RUNNING
      break;
    
    case RUNNING:                               // Se for RUNNING
      moveTime++;                               // Incrementa o tempo de movimento
      readDirection();                          // Lê a direção
      if(moveTime >= SNAKE_MOVE_DELAY) {        // Se o tempo de movimento for maior que o tempo de movimento da cobra
        dir = newDir;                           // Muda a direção da cobra
        display.clearDisplay();                 // Limpa o display
        if(moveSnake()) {                       // Move a cobra, se houver colisão
          gameState = GAMEOVER;                 // Muda o estado para GAMEOVER
          drawGameover();                       // Desenha a mensagem de GAMEOVER
          delay(1000);                          // Espera 1 segundo
        }
        drawMap();                              // Desenha o mapa
        drawScore();                            // Desenha a pontuação
        display.display();                      // Mostra o que foi desenhado no display
        checkFruit();                           // Verifica se a cobra comeu a fruta
        moveTime = 0;                           // Reseta o tempo de movimento
      }
      break;
    
    case GAMEOVER:                              // Se for GAMEOVER
      if(buttonPress()) {                       // Se algum botão for pressionado
        delay(500);                             // Espera 500ms
        setupGame();                            // Inicia o jogo
      }
      break;
  }
  delay(10);                                    // Espera 10ms
}

/*
Função para verificar se algum botão foi pressionado
argumentos: nenhum
retorno: true se algum botão foi pressionado, false caso contrário
*/
bool buttonPress() {                        // Verifica se algum botão foi pressionado
  for (byte i = 0; i < 4; i++) {            // Para cada botão
    byte buttonPin = buttonPins[i];         // Pega o pino do botão
    if (digitalRead(buttonPin) == LOW) {    // Se o botão estiver pressionado
      return true;                          // Retorna true
    }
  }
  return false;                             // Retorna false
}
/*
Função para ler a direção
argumentos: nenhum
retorno: nenhum
*/
void readDirection() {                                              // Lê a direção
  for (byte i = 0; i < 4; i++) {                                    // Para cada botão
    byte buttonPin = buttonPins[i];                                 // Pega o pino do botão
    if (digitalRead(buttonPin) == LOW && i != ((int)dir + 2) % 4) {  // Se o botão estiver pressionado e não for o oposto da direção atual
      newDir = (Direction)i;                                          // Muda a direção
      return;                                                         // Retorna
    }
  }
}
/*
Função para mover a cobra
argumentos: nenhum
retorno: true se houver colisão, false caso contrário
*/
bool moveSnake() {
  int8_t x = snake[0][0];     // Pega a posição X da cabeça da cobra
  int8_t y = snake[0][1];     // Pega a posição Y da cabeça da cobra

  switch(dir) {               // Verifica a direção
    case LEFT:                // Se for LEFT
      x -= 1;                 // Decrementa a posição X
      break;                  // Sai do switch
    case UP:                  // Se for UP
      y -= 1;                 // Decrementa a posição Y
      break;                  // Sai do switch
    case RIGHT:               // Se for RIGHT
      x += 1;                 // Incrementa a posição X
      break;                  // Sai do switch
    case DOWN:                // Se for DOWN
      y += 1;                 // Incrementa a posição Y
      break;                  // Sai do switch
  }

  if(collisionCheck(x, y))    // Verifica se houve colisão
    return true;              // Retorna true - houve colisão

  for(int i = snake_length - 1; i > 0; i--) {   // Para cada pedaço da cobra
    snake[i][0] = snake[i - 1][0];              // Move o pedaço da cobra
    snake[i][1] = snake[i - 1][1];              // Move o pedaço da cobra
  }

  snake[0][0] = x;                    // Move a cabeça da cobra
  snake[0][1] = y;                    // Move a cabeça da cobra
  return false;                       // Retorna false - não houve colisão
}

/*
Função para verificar se a cobra comeu a fruta
argumentos: nenhum
retorno: nenhum
*/
void checkFruit() {
  if(fruit[0] == snake[0][0] && fruit[1] == snake[0][1])    // Se a cobra comeu a fruta
  {
    if(snake_length + 1 <= MAX_SANKE_LENGTH){               // Se o tamanho da cobra for menor que o tamanho máximo
      snake_length++;                                       // Incrementa o tamanho da cobra
      beep();                                               // Beep
    }
    generateFruit();                                        // Gera uma nova fruta
  }
}

/*
Função para gerar uma nova fruta
*/
void generateFruit() {
  bool b = false;                                             // Variável para verificar se a fruta está em cima da cobra
  do {                                                        // Repete enquanto a fruta estiver em cima da cobra
    b = false;                                                // Reseta a variável
    fruit[0] = random(0, MAP_SIZE_X);                         // Gera uma posição X aleatória
    fruit[1] = random(0, MAP_SIZE_Y);                         // Gera uma posição Y aleatória
    for(int i = 0; i < snake_length; i++) {                       // Para cada pedaço da cobra
      if(fruit[0] == snake[i][0] && fruit[1] == snake[i][1]) {    // Se a fruta estiver em cima da cobra
        b = true;                                                 // Muda a variável para true
        continue;                                                 // Continua o loop
      }
    }
  } while(b);                                                     // Repete enquanto a fruta estiver em cima da cobra
}
/*
Função para verificar se houve colisão
argumentos: posição X e Y
retorno: true se houve colisão, false caso contrário
*/
bool collisionCheck(int8_t x, int8_t y) {
  for(int i = 1; i < snake_length; i++) {                               // Para cada pedaço da cobra
    if(x == snake[i][0] && y == snake[i][1]) return true;               // Se houver colisão com a posição, retorna true
  }
  if(x < 0 || y < 0 || x >= MAP_SIZE_X || y >= MAP_SIZE_Y) return true; // Se posicionar fora do mapa, retorna true
  return false;                                                         // Se não houver colisão, retorna false    
}
/*
Função para desenhar o mapa
*/
void drawMap() {
  int offsetMapX = SCREEN_WIDTH - SNAKE_PIECE_SIZE * MAP_SIZE_X - 2;
  int offsetMapY = 2;

  display.drawRect(fruit[0] * SNAKE_PIECE_SIZE + offsetMapX, fruit[1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_INVERSE);
  display.drawRect(offsetMapX - 2, 0, SNAKE_PIECE_SIZE * MAP_SIZE_X + 4, SNAKE_PIECE_SIZE * MAP_SIZE_Y + 4, SSD1306_WHITE);
  for(int i = 0; i < snake_length; i++) {
    display.fillRect(snake[i][0] * SNAKE_PIECE_SIZE + offsetMapX, snake[i][1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_WHITE);
  }
}

/*
Função para desenhar a pontuação
*/
void drawScore() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2,2);
  display.println(snake_length - STARTING_SNAKE_SIZE);
}

void drawPressToStart() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2,20);
  //display.print(F("Press a\n button to\n start the\n game!"));
}

/*
Função para desenhar a mensagem de GAMEOVER
*/
void drawGameover() {
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16,20);
  display.println(F("GAME OVER"));
}


/*
Função para gerar um beep no buzzer
*/
void beep(){
  digitalWrite(BUZZER, HIGH);       // Liga o buzzer
  delay(50);                        // Espera 50ms
  digitalWrite(BUZZER, LOW);        // Desliga o buzzer 
}