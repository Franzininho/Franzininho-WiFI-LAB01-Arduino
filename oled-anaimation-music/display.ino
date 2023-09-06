#include "display.h"

void display_init()
{
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
    display.clearDisplay();
}


void display_logo()
{
    // Mostra o logo da Franzininho como splash screen
  display.clearDisplay();                                                           // Limpa a tela
  display.drawBitmap(0, 0, franzininho_logo_128x64, imageWidth, imageWidth, WHITE); // Desenha o logo da Franzininho
  display.display();                                                                // Atualiza o display
  delay(2000);      
}

void display_clear()
{
    display.clearDisplay();
    display.display();
}

void display_animation(){
  display.clearDisplay();
  display.drawBitmap(40, 8, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}