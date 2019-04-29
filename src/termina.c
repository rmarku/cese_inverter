#include "bsp/bsp.h"
#include "buffercircular.h"

static bufferc_t buffer_rx, buffer_tx;

/** @brief Configura el terminal serial */
void terminal_configurar() {
    bc_init(&buffer_rx);
    bc_init(&buffer_tx);
}

/**
 * @brief Escribe en la terminal
 *
 * @param cadena Cadena de caracteres que se va a escribir
 */
void terminal_escribir(const char * cadena) {
    // Agrego la cadena al buffer circular
    while(*cadena != '\0' && ! bc_isFull(&buffer_tx)) {
        bc_putItem(&buffer_tx, *cadena);
        cadena++;
    }
}


void terminal_process() {
    char dato;
    // si tengo datos y puedo enviar, envío
    if(!bc_isEmpty(&buffer_tx) && uartSendReady()){
        bc_getItem(&buffer_tx, &dato);
        uartSend(dato);
    }

    // Si hay datos y no esta llena la cola de entrada recibo.
    if(!bc_isFull(&buffer_rx) && uartRecibeHasData()){
        bc_putItem(&buffer_rx, uartRecibe());
    }
}
