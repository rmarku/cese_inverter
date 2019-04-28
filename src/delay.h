/**
 * @file delay.h
 * @author Ricardo Martín Marcucci
 * @brief Librería en capa de aplicación para gestionar delays
 * @version 0.1
 * @date 2019-04-22
 *
 * @copyright Copyright (c) 2019
 *
 */

/*=====[Evitar inclusion multiple comienzo]==================================*/
#ifndef __DELAY_H
#define __DELAY_H

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

typedef uint64_t tick_t;

typedef struct {
  tick_t endTime;
  tick_t duration;
} delay_t;

/*=====[Prototipos de funciones publicas]====================================*/

void delayConfig(delay_t *delay, tick_t duracion);
void delayNext(delay_t *delay, tick_t duracion);
bool delayEnded(delay_t *delay);
tick_t getTick();
void delay_1ms();

/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/
#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/
#endif /* __DELAY_H */