/**
 * @file delay.h
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar delays
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup delay Biblioteca de Delay
 * @ingroup TPF
 * @{
 */

#ifndef __DELAY_H
#define __DELAY_H

/* ----------------------------------------------------------------------------------------------------------------
* Inclusion de cabeceras
* ---------------------------------------------------------------------------------------------------------------- */
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ----------------------------------------------------------------------------------------------------------------
 * Definiciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */
/// @brief Tipo de dato que alberga el numero de ticks
typedef uint64_t tick_t;

/// @brief Estructura para delays
typedef struct {
    tick_t endTime;   ///< Tick en el que el delay debe terminar
    tick_t duration;  ///< Cantidad de ticks que dura el delay
} delay_t;


/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

void delayConfig(delay_t *delay, tick_t duracion);

void delayNext(delay_t *delay, tick_t duracion);

bool delayEnded(delay_t *delay);

tick_t getTick();

void delay_1ms();


#ifdef __cplusplus
}
#endif
#endif /* __DELAY_H */

/** @} Doxygen module end */