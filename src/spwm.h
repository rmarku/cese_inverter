/**
 * @file spwm.h
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar el PWM
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup wave Modulo generador de SPWM
 * @ingroup TPF
 * @{
 */

#ifndef __SPWM_H
#define __SPWM_H

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------------------------------------------------------------------------
 * Prototipos funciones publicas
 * ---------------------------------------------------------------------------------------------------------------- */

void spwm_init();

void spwm_process();

void spwm_changeFrecuency(uint16_t freq);


#ifdef __cplusplus
}
#endif
#endif /* __SPWM_H */

/** @} Doxygen module end*/