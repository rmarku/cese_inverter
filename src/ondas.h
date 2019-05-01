/**
 * @file onda.h
 * @author Ricardo Martín Marcucci
 * @brief Datos de una onda senoidal
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup wave Modulo generador de SPWM
 * @ingroup TPF
 * @{
 */

#ifndef __ONDA_H
#define __ONDA_H

#ifdef __cplusplus
extern "C" {
#endif
/* ----------------------------------------------------------------------------------------------------------------
 * Definicion de constantes
 * ---------------------------------------------------------------------------------------------------------------- */

/// @brief Cantidad de muestras de la onda
#define TAMANIO_ONDA 50

/// \brief Muestras de un cuarto de ciclo de una onda senoidal
const uint16_t onda_data[TAMANIO_ONDA] = {
    0,    16,  32,  48,  64,  80,  96, 112, 127, 143,
    158, 173, 188, 203, 218, 232, 246, 260, 274, 288,
    301, 314, 326, 338, 350, 362, 373, 384, 394, 404,
    414, 423, 432, 440, 448, 456, 463, 469, 476, 481,
    486, 491, 495, 499, 502, 505, 507, 509, 510, 511
};


#ifdef __cplusplus
}
#endif
#endif /* __ONDA_H */

/** @} Doxygen module end*/