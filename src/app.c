/**
 * @file app.c
 * @author Ricardo Martín Marcucci
 * @brief Archivo principal de la aplicación
 * @version 0.1
 * @date 2019-04-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */
/*=====[Inclusion de su propia cabecera]=====================================*/
#include "app.h"

/*=====[Inclusiones de dependencias de funciones privadas]===================*/
#include "bsp/bsp.h"
#include "delay.h"

/*=====[Macros de definicion de constantes privadas]=========================*/
/*=====[Macros estilo funcion privadas]======================================*/
/*=====[Definiciones de tipos de datos privados]=============================*/
/*=====[Definiciones de Variables globales publicas externas]================*/
/*=====[Definiciones de Variables globales publicas]=========================*/
/*=====[Definiciones de Variables globales privadas]=========================*/
/*=====[Prototipos de funciones privadas]====================================*/


/*=====[Implementaciones de funciones publicas]==============================*/
/**
 * @brief Aplicación pricipal
 * 
 * @return int 
 */
int main(void) {

  // Inicializo la placa.
  bsp_init();


  // Loop infinito
  while (1) {
    led_toggle();
    bsp_delay(500);
  }
  return 0; // nunca llegaría
}

/**
 * @brief Función llamada por el BSP cada 1ms
 * 
 */
void app_1ms() {
   delay_1ms(); 
}


/*=====[Implementaciones de funciones privadas]==============================*/
