/**
 * @file spwm.h
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar el PWM
 * @version 0.1
 * @date 2019-04-22
 *
 * @copyright Copyright (c) 2019
 *
 */

/*=====[Evitar inclusion multiple comienzo]==================================*/
#ifndef __SPWM_H
#define __SPWM_H

/*=====[Inclusiones de dependencias de funciones publicas]===================*/
#include <stdbool.h>
#include <stdint.h>


/*=====[C++ comienzo]========================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*=====[Macros de definicion de constantes publicas]=========================*/

/*=====[Macros estilo funcion publicas]======================================*/

/*=====[Definiciones de tipos de datos publicos]=============================*/


typedef struct {
    uint16_t frecuencia; // en mhz
    uint64_t last_start;
} spwm_t;

/*=====[Prototipos de funciones publicas]====================================*/

void spwm_init();

void spwm_process();

void spwm_changeFrecuency(uint16_t freq);

/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/
#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/
#endif /* __SPWM_H */