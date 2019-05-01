/**
 * @file terminal.c
 * @author Ricardo Martín Marcucci
 * @brief Implementación de una terminal simple
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup term Terminal por puerto serie
 * @ingroup TPF
 * @{
 */

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include "bsp/bsp.h"
#include "terminal.h"
#include "buffercircular.h"
#include "terminal_colors.h"

/* ----------------------------------------------------------------------------------------------------------------
 * variables Privadas
 * ---------------------------------------------------------------------------------------------------------------- */

/// \brief Buffers de recepción y transmisión
static bufferc_t buffer_rx, buffer_tx;

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/** @brief Configura el terminal serial */
void terminal_configurar() {
    bc_init(&buffer_rx);
    bc_init(&buffer_tx);
}

/**
 * @brief Escribe en la terminal
 *
 * @param[in] cadena Cadena de caracteres que se va a escribir
 */
void terminal_escribir(const char *cadena) {
    // Agrego la cadena al buffer circular
    while (*cadena != '\0' && !bc_isFull(&buffer_tx)) {
        bc_put(&buffer_tx, *cadena);
        cadena++;
    }
}

/**
 * @brief Permite escribir un conjunto de mensajes en una estructura en pantalla
 * @param msg Conjunto de mensajes a escribir
 */
void terminal_escribirMsg(const msg_t *msg) {
    for (int i = 0; i < msg->cant_mensajes; i++) {
        terminal_escribir(msg->mensaje[i]);
        terminal_escribir(NEW_LINE);
    }
}

/**
 * @brief Metodo que procesa el envio y resepción asincrónico de la terminal
 */
void terminal_process() {
    char dato;
    // si tengo datos y puedo enviar, envío
    if (!bc_isEmpty(&buffer_tx) && uartSendReady()) {
        bc_get(&buffer_tx, &dato);
        uartSend(dato);
    }

    // Si hay datos y no esta llena la cola de entrada recibo.
    if (!bc_isFull(&buffer_rx) && uartRecibeHasData()) {
        char dato = uartRecibe();
        bc_put(&buffer_rx, dato);
        // Envío Eco
        uartSend(dato);
    }
}

/**
 * @brief Metodo que analiza si han introducido un comando (los comandos terminan con \r)
 *  Verifico si introdujeron un enter y devuelvo la cadena
 * @param[out] data Copia los datos que estaban en el buffer hasta el enter
 * @return
 */
uint8_t terminal_getCommand(char *data) {
    char d;
    int i = 0;
    if (0 == bc_peekLast(&buffer_rx, &d)) { // si hay un dato me fijo que sea el enter
        if (d == '\r') {
            // copio del buffer a los datos
            while (bc_get(&buffer_rx, &d) == 0) {
                data[i] = d;
                i++;
            }
            data[i - 1] = '\0';
        }
    }
    return i;
}

/** @} Doxygen module end*/