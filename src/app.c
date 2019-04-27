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
#include "buffercircular.h"

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

    delay_t led;
    delay_t uart;
    // Inicializo la placa.
    bsp_init();

    delayConfig(&led, 500);
    delayConfig(&uart, 2000);
    uint16_t i=0;
    // Loop infinito
    while (1) {
        if (delayEnded(&led)) {
            led_toggle();
            delayConfig(&led, 100);
            setPWM(i++%1000);
        }
        if (delayEnded(&uart)) {
            delayConfig(&uart, 2000);
            uartSend('A');
        }
    }
    return 0; // nunca llegaría
}

/**
 * @brief Función llamada por el BSP cada 1ms
 *
 */
void app_1ms() { delay_1ms(); }

/*=====[Implementaciones de funciones privadas]==============================*/
