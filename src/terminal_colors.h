/**
 * @file terminal_color.h
 * @author Ricardo Martín Marcucci
 * @brief Definiciones de constantes para colores y formatos de la terminal
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup term Terminal por puerto serie
 * @ingroup TPF
 * @{
 */
#ifndef __TERMINAL_COLORS_H
#define __TERMINAL_COLORS_H


/** @brief Codigo de nueva linea */
#define NEW_LINE                            "\r\n"

/** @brief Codigo de color rojo */
#define TERMINAL_TEXTO_ROJO                 "\x1B[31m"

// Colores
/** @brief Codigo de color verde */
#define TERMINAL_TEXTO_VERDE                "\x1B[32m"
/** @brief Codigo de color amarillo */
#define TERMINAL_TEXTO_AMARILLO             "\x1B[33m"
/** @brief Codigo de color blanco */
#define TERMINAL_TEXTO_BLANCO               "\x1B[37m"

// Colores Light
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_ROJO_L               "\x1B[91m"
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_VERDE_L              "\x1B[92m"
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_AMARILLO_L           "\x1B[93m"

// Formatos
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_NORMAL               "\x1B[0m"
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_BOLD                 "\x1B[1m"
/** @brief Codigo de color rojo claro */
#define TERMINAL_TEXTO_UNDERLINE            "\x1B[4m"

#endif //  __TERMINAL_COLORS_H

/** @} Doxygen module end*/
