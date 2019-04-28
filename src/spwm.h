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

/*
    Frecuencia PWM=10kHz = 100uS = period
    media onda a 50Hz = 20ms/2 =1 0mS
    10mS/100uS= 100 periodos cada medio ciclo
*/

void spwm_init(spwm_t *onda);

void spwm_process(spwm_t *onda);


/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/
#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/
#endif /* __SPWM_H */