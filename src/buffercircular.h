/**
 * @file buffercircular.h
 * @author Ricardo Martín Marcucci
 * @brief Implementación de un buffer circular (circular queue)
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup bc Buffer Circular
 * @ingroup TPF
 * @{
 */

#ifndef __BUFFERCIRCULAR_H
#define __BUFFERCIRCULAR_H

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ----------------------------------------------------------------------------------------------------------------
 * Definiciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */
/** @brief Tamaño de los buffers circulares */
#define MAX_ITEMS 100

/* ----------------------------------------------------------------------------------------------------------------
 * Estructuras Publicas
 * ---------------------------------------------------------------------------------------------------------------- */
/**
 * @brief Estructura del buffer circular
 */
typedef struct {
    int inicio;             ///< posición de inicio del buffer
    int fin;                ///< posición de fin del buffer
    int cantidad;           ///< cantidad de items en el buffer
    char data[MAX_ITEMS];   ///< arreglo de datos
} bufferc_t;

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

void bc_init(bufferc_t *bc);

bool bc_isEmpty(bufferc_t *bc);

bool bc_isFull(bufferc_t *bc);

int bc_put(bufferc_t *bc, char dato);

int bc_get(bufferc_t *bc, char *dato);

int bc_peekLast(bufferc_t *bc, char *dato);

int bc_peekFirst(bufferc_t *bc, char *dato);

#ifdef __cplusplus
}
#endif
#endif /* __BUFFERCIRCULAR_H */

/** @} Doxygen module end*/