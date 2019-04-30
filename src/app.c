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
#include "spwm.h"
#include "mef.h"
#include "terminal.h"

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
    spwm_init();
    mef_init();

    // Muestro el menú por primera vez

    // Loop infinito (Super Loop)
    while (1) {
        // Blinky
        if (delayEnded(&led)) {
            led_toggle();
            delayNext(&led, 100);
        }

        // Procesado de UART mediante terminal
        terminal_process();

        // Proceso generador de onda
        spwm_process();

        // Proceso la maquina de estados
        mef_process();
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
