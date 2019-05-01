/**
 * @file app.c
 * @author Ricardo Martín Marcucci
 * @brief

Archivo principal de la aplicación

1. Plataforma embebida: BluePill (STM32f103)

2. Aplicación:
    - Se realizará una aplicación utilice el módulo de PWM del microcontrolador para generar una señal senoidal (SPWM).
    - El software deberá también tomar muestras de dos canales de ADC y enviarlos al puerto serie.
    - El software podrá recibir por puerto serie un comando de configuración que cambie la frecuencia de la señal sinusoidal Generada (MEF).
    - El software utilizará la HAL provista por el fabricante, implementará una capa BSP para abstraerse de los periféricos y una capa de aplicación donde se implemente la lógica.

3. Periféricos:
    - ADC
    - PWM
    - UART
    - GPIO

 * @version 0.1
 * @date 2019-04-24
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup TPF Programación de Microcontroladores
 * @brief Trabajo Final de materia
 * @{ */


/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include "app.h"

#include "bsp/bsp.h"
#include "delay.h"
#include "spwm.h"
#include "mef.h"
#include "terminal.h"

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Aplicación pricipal con SuperLoop
 *
 * @return int Nunca retornaría
 */
int main(void) {
    delay_t led;

    // Inicializo la placa.
    bsp_init();

    //Inicializo los modulos de applicación
    delayConfig(&led, 500);
    spwm_init();
    mef_init();
    terminal_configurar();

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
 * @brief llamada Callback del servicio prestado por BSP, se llama cada 1ms
 */
void app_1ms() {
    delay_1ms();
}

/** @} Doxygen module end*/
