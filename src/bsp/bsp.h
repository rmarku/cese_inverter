/**
 * @file bsp.h
 * @author Ricardo Martín Marcucci
 * @brief Cabecera del BSP para ser incluida por la app como el BSP
 * @version 0.1
 * @date 2019-04-22
 *
 * @copyright Copyright (c) 2019
 *
 */

/*=====[Evitar inclusion multiple comienzo]==================================*/
#ifndef __BSP_H
#define __BSP_H

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

/*=====[Prototipos de funciones publicas]====================================*/
void bsp_init();
void led_toggle();
void bsp_delay(uint32_t d);

/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/
#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/
#endif /* __MAIN_H */