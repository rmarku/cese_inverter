/**
 * @file mef.c
 * @author Ricardo Martín Marcucci
 * @brief Logica de la maquina de estados implementada con punteros a funciones
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup mef Maquina de estado del proyecto
 * @ingroup TPF
 * @{
 */

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "bsp/bsp.h"
#include "delay.h"
#include "buffercircular.h"
#include "spwm.h"
#include "terminal.h"
#include "terminal_colors.h"

/* ----------------------------------------------------------------------------------------------------------------
 * Estructuras privadas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Estructura de un estado
 */
typedef struct {
    void (*fun_estado)(void);    ///< Puntero a la función que ejecuta el estado
    bool primeraVez;            ///< Bandera indicando si se acaba es la primera vez que se entra al estado
} estado_t;

/* ----------------------------------------------------------------------------------------------------------------
 * Variables  privadas
 * ---------------------------------------------------------------------------------------------------------------- */

static estado_t estado;

/* ----------------------------------------------------------------------------------------------------------------
 * Constantes de Menú
 * ---------------------------------------------------------------------------------------------------------------- */

/// @brief Menú principal
const msg_t menu_principal = {
        .mensaje = {
                "MENU",
                "====",
                "1) Leer valores de ADC",
                "2) Cambiar salida de SPWM"
        },
        .cant_mensajes = 4
};

/// @brief Menú del ADC
const msg_t menu_ADC = {
        .mensaje = {
                "MENU ADC",
                "========",
                "1) Leer valor ADC1",
                "2) Leer valor ADC2"
        },
        .cant_mensajes = 4
};

/// @brief Mensaje de Invalido
const msg_t menu_invalido = {
        .mensaje = {
                "El valor ingresado es invalido, intente nuevamente"
        },
        .cant_mensajes = 1
};

/// @brief Mensaje de cambio de frecuencia
const msg_t menu_frecenciaCambiada = {
        .mensaje = {
                "La frecuencia se cambió con exitos"
        },
        .cant_mensajes = 1
};

/// @brief Mensaje de pregunta de frecuencia
const msg_t menu_preguntarFrecuencia = {
        .mensaje = {
                "Ingrese la nueva frecuencia de salida: "
        },
        .cant_mensajes = 1
};


/* ----------------------------------------------------------------------------------------------------------------
 * Cabeceras de funciones Privadas
 * ---------------------------------------------------------------------------------------------------------------- */

void estado_INICIO();

void estado_MENU_ADC();

void estado_CAMBIAR_FREQ();

uint16_t menu_readValue(bool *lei);


/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Inicialización de la maquina de estados
 */
void mef_init(void) {
    estado.fun_estado = estado_INICIO;
    estado.primeraVez = true;
}

/**
 * @brief Ejecución de la maquina de estados
 */
void mef_process() {
    estado.fun_estado();
}

/**
 * @brief Función que cambia de estado y resetea la vandera de primer inicio
 * @param fun
 */
void mef_cambiar(void(*fun)(void)) {
    estado.fun_estado = fun;
    estado.primeraVez = true;
}

/**
 * @brief Estado de inicio de la MEF
 */
void estado_INICIO() {
    int8_t opcion;
    bool lei;
    if (estado.primeraVez) {
        terminal_escribirMsg(&menu_principal);
        estado.primeraVez = false;
    }
    opcion = menu_readValue(&lei);
    if (lei && opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion) {
            case 1:
                mef_cambiar(estado_MENU_ADC);
                break;
            case 2:
                mef_cambiar(estado_CAMBIAR_FREQ);
                break;

            default:
                terminal_escribirMsg(&menu_invalido);
                mef_cambiar(estado_INICIO);
                break;
        }
    }
}


/**
 * @brief Estado del menú de ADC MEF
 */
void estado_MENU_ADC() {
    int8_t opcion;
    bool lei;

    // para uso de lectura
    char buffer[50];
    uint16_t adcRead;
    if (estado.primeraVez) {
        terminal_escribirMsg(&menu_ADC);
        estado.primeraVez = false;
    }
    opcion = menu_readValue(&lei);
    if (lei && opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion) {
            case 1:
            case 2:
                terminal_escribir("Valor del ADC");
                if (opcion == 1) {
                    terminal_escribir("1: ");

                } else {
                    terminal_escribir("2: ");
                }
                adc_ConvertionStart(opcion);
                while (!adc_ConvertionStoped(opcion));

                adcRead = adc_getData(opcion);
                itoa(adcRead, buffer, 10);
                terminal_escribir(buffer);
                terminal_escribir(NEW_LINE);

                mef_cambiar(estado_INICIO);
                break;

            default:
                terminal_escribirMsg(&menu_invalido);
                mef_cambiar(estado_MENU_ADC);
                break;
        }
    }
}

/**
 * @brief Estado para cambio de frecuencia
 */
void estado_CAMBIAR_FREQ() {
    uint16_t new_freq;
    bool lei;
    if (estado.primeraVez) {
        terminal_escribirMsg(&menu_preguntarFrecuencia);
        estado.primeraVez = false;
    }
    new_freq = menu_readValue(&lei);

    if (lei) {
        if (new_freq >= 10000 && new_freq < 65000) {  // verifico si es valida la frecuencia
            spwm_changeFrecuency(new_freq);
            terminal_escribirMsg(&menu_frecenciaCambiada);
            mef_cambiar(estado_INICIO);

        } else {
            terminal_escribirMsg(&menu_invalido);
            mef_cambiar(estado_CAMBIAR_FREQ);
        }
    }
}

/**
 * @brief Función helper para leer valores de la terminal
 */
uint16_t menu_readValue(bool *lei) {
    *lei = false;
    char dato[50];
    uint8_t cant;

    cant = terminal_getCommand(dato);
    if (cant > 0) { // leí datos
        *lei = true;
        return atoi(dato);
    }
    return 0;
}

/** @} Doxygen module end*/