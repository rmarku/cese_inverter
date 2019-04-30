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

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include "buffercircular.h"

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Inicializa una estructura Buffer circular con los datos validos.
 * @param[out] bc  Estructura que se desea inicializar
 */
void bc_init(bufferc_t *bc) {
    int i;
    bc->cantidad = 0;
    bc->inicio = 0;
    bc->fin = 0;
    for (i = 0; i < MAX_ITEMS; i++) {
        bc->data[i] = 0;
    }
}

/**
 * @brief Informa si un buffer circular esta vacío
 * @param[in] bc  Buffer circular a analizar
 * @retval  true:  está vacio
 * @retval  false: no está vacio
 */
bool bc_isEmpty(bufferc_t *bc) {
    return (bool) (bc->cantidad == 0);
}

/**
 * @brief Informa si un buffer circular esta lleno
 * @param[in] bc  Buffer circular a analizar
 * @retval  true:  está lleno
 * @retval  false: no está lleno
 */
bool bc_isFull(bufferc_t *bc) {
    return (bool) (bc->cantidad == MAX_ITEMS);
}

/**
 * @brief Agrega un dato a la cola circular
 * @param[in] bc Buffer circular seleccionado
 * @param[in] dato Valor a agregar a la cola
 * @retval  0:  se agregó el dato
 * @retval  -1: el buffer está lleno
 */
int bc_put(bufferc_t *bc, char dato) {
    if (bc_isFull(bc))
        return -1;

    bc->cantidad++;
    bc->data[bc->fin] = dato;
    bc->fin = (bc->fin + 1) % MAX_ITEMS;
    return 0;
}

/**
 * @brief Leo un dato del buffer
 * @param[in] bc Buffer circular seleccionado
 * @param[out] dato Valor leido del buffer
 * @retval  0:  se pudo leer del buffer
 * @retval  -1: el buffer está vacío
 */
int bc_get(bufferc_t *bc, char *dato) {
    if (bc_isEmpty(bc))
        return -1;

    *dato = bc->data[bc->inicio];
    bc->inicio = (bc->inicio + 1) % MAX_ITEMS;
    bc->cantidad--;
    return 0;
}

/**
 * @brief Espío el ultimo valor que ingresó al buffer
 * @param[in] bc Buffer circular seleccionado
 * @param[out] dato Valor leido del buffer
 * @retval  0:  se pudo leer del buffer
 * @retval  -1: el buffer está vacío
 */
int bc_peekLast(bufferc_t *bc, char *dato) {
    if (bc_isEmpty(bc))
        return -1;

    *dato = bc->data[(bc->inicio + bc->cantidad - 1) % MAX_ITEMS];
    return 0;
}

/**
 * @brief Espío el primer valor que ingresó al buffer
 * @param[in] bc Buffer circular seleccionado
 * @param[out] dato Valor leido del buffer
 * @retval  0:  se pudo leer del buffer
 * @retval  -1: el buffer está vacío
 */
int bc_peekFirst(bufferc_t *bc, char *dato) {
    if (bc_isEmpty(bc))
        return -1;

    *dato = bc->data[bc->inicio];
    return 0;
}

/** @} Doxygen module end*/