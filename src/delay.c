/**
 * @file delay.c
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar delays
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup delay Biblioteca de Delay
 * @ingroup TPF
 * @{
 */

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */
#include "delay.h"

/* ----------------------------------------------------------------------------------------------------------------
 * variables privadas
 * ---------------------------------------------------------------------------------------------------------------- */

static tick_t tick_counter = 0;

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Leer el valor actual del tick
 * @return valor del tick
 */
tick_t getTick() {
    return tick_counter;
}

/**
 * @brief Configurar una estructura delay por primera vez
 * @param delay Estructura del delay
 * @param duracion Cantidad de ticks a esperar
 */
void delayConfig(delay_t *delay, tick_t duracion) {
    delay->endTime = getTick() + duracion;
}

/**
 * @brief Actualiza un delay para que suceda en un tiempo futuro
 * @param delay Estructura del delay
 * @param duracion Cantidad de ticks a esperar a partir del ultimo
 */
void delayNext(delay_t *delay, tick_t duracion) {
    delay->endTime += duracion;
}

/**
 * @brief Verificar si el delay terminó
 * @param delay Estructura del delay
 * @retval true: El delay terminó
 * @retval false: El delay no terminó
 */
bool delayEnded(delay_t *delay) {
    bool res = false;
    if (delay->endTime < getTick()) {
        res = true;
    }
    return res;
}

/**
 * @brief Servicio a ser llamado cada 1ms para que el delay funcione
 */
void delay_1ms() {
    tick_counter++;
}
/** @} Doxygen module end */
