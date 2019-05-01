/**
 * @file spwm.c
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar el PWM
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup wave Modulo generador de SPWM
 * @ingroup TPF
 * @{
 */


/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */
#include "spwm.h"
#include "ondas.h"
#include "bsp/bsp.h"

/* ----------------------------------------------------------------------------------------------------------------
 * definiciones Privadas
 * ---------------------------------------------------------------------------------------------------------------- */

/// \brief Estructura con los datos de la onda
typedef struct {
    uint16_t frecuencia; ///< frecuencia de la señal en Mhz
    uint64_t last_start; ///< Ultimo tick en el que comenzó la señal
} spwm_t;

/* ----------------------------------------------------------------------------------------------------------------
 * Variables Privadas
 * ---------------------------------------------------------------------------------------------------------------- */

/// \brief Datos de la onda
static spwm_t onda;


/**
 * @brief Inicializa los datos para generación de SPWM
 */
void spwm_init() {
    onda.frecuencia = 60000;
    onda.last_start = get_01msTick();
}

/**
 * @brief Procesa y actualiza el estado de la onda.
 */
void spwm_process() {
    uint64_t current = get_01msTick() - onda.last_start;
    uint32_t ticks_ciclo = 10000000 / onda.frecuencia;
    uint8_t idx;
    uint16_t value;

    // Terminó un ciclo?
    if (current > ticks_ciclo) {
        onda.last_start += ticks_ciclo;
        current -= ticks_ciclo;
    }

    // Calculo posición de la muestra entre 0 y 199 según el tick actual
    // Lo realizo en 128 mas arriba para no utilizar floats
    idx = ((TAMANIO_ONDA * 4 * 128) / ticks_ciclo * current) / 128;

    if (current >= ticks_ciclo * 3 / 4) { // 4to Cuarto
        idx = TAMANIO_ONDA * 4 - idx - 1;
        value = 512 - onda_data[idx];

    } else if (current >= ticks_ciclo / 2) { // 3er Cuarto
        idx = idx - TAMANIO_ONDA * 2;
        value = 512 - onda_data[idx];

    } else if (current >= ticks_ciclo / 4) { // 2do Cuarto
        idx = TAMANIO_ONDA * 2 - idx - 1;
        value = 511 + onda_data[idx];

    } else { // 1er Cuarto
        idx = idx;
        value = 511 + onda_data[idx];
    }
    setPWM(value);
}

/**
 * @brief Permite cambiar la frecuencia de la onda senoidal
 * @param freq Nueva frecuencia senoidal
 */
void spwm_changeFrecuency(uint16_t freq) {
    // TODO: Realizar el calculo para que la nueva frecuencia continuel desde
    // la muestra actual
    onda.frecuencia = freq;
}


/** @} Doxygen module end*/