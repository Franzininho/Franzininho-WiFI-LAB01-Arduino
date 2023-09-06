#include "music.h"      // Biblioteca que contém a música
#include "display.h"    // Biblioteca que contém o display

/*Bibliotecas FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*protítipos das Tasks*/
void vTaskMusic(void *pvParameters);    //Task que toca a música
void vTaskLED(void *pvParameters);      //Task que pisca o LED

#define LED 14    //LED pino do LED

void setup() {

  display_init();   // Inicializa o display
  display_logo();   // Exibe o logo da Franzininho
  display_clear();  // Limpa o display
  
  xTaskCreate(vTaskMusic,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,NULL); // Cria a task que toca a música
  xTaskCreate(vTaskLED,"TASK2",configMINIMAL_STACK_SIZE,NULL,1,NULL);   // Cria a task que pisca o LED
}

/*
* Exibe a animação no display
*/
void loop() {  
  display_animation();    // Exibe a animação no display
}

/*
* Task que toca a música
*/
void vTaskMusic(void *pvParameters)
{
    music_init();   // Inicializa o buzzer  
    while (1)
    {
      music_play(); // Toca a música
    }
}

/*
* Task que pisca o LED
*/
void vTaskLED(void *pvParameters)
{
    pinMode(LED,OUTPUT);  // Define o pino do LED como saída

    while (1)
    {
      digitalWrite(LED,!digitalRead(LED));  // Inverte o estado do LED
      vTaskDelay(pdMS_TO_TICKS(200));       // Delay de 200ms
    }
}
