/**
 * @file terminal.h
 * @author Ricardo Martín Marcucci
 * @brief Implementación de una terminal simple
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup term Terminal por puerto serie
 * @ingroup TPF
 * @{
 */

#ifndef __TERMINAL_H
#define __TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------------------------------------------------------------------------
 * Definiciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/// \brief Estructura para crear mensajes
typedef struct {
    uint8_t cant_mensajes;
    char *mensaje[];
} msg_t;

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

void terminal_configurar();

void terminal_escribir(const char *cadena);

void terminal_escribirMsg(const msg_t *msg);

void terminal_process();

uint8_t terminal_getCommand(char *data);

#ifdef __cplusplus
}
#endif
#endif /* __TERMINAL_H */

/** @} Doxygen module end*/