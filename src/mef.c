#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "bsp/bsp.h"
#include "delay.h"
#include "buffercircular.h"
#include "spwm.h"
#include "terminal.h"

typedef struct {
    void(*fun_estado)(void);
    bool primeraVez;
} estado_t;


void estado_INICIO();

void estado_MENU_ADC();

void estado_CAMBIAR_FREQ();

//Menues

const msg_t menu_principal = {
    .mensaje = {
        "MENU",
        "====",
        "1) Leer valores de ADC",
        "2) Cambiar salida de SPWM"
    },
    .cant_mensajes = 4
};

const msg_t menu_ADC = {
    .mensaje = {
        "MENU ADC",
        "========",
        "1) Leer valor ADC1",
        "2) Leer valor ADC2"
    },
    .cant_mensajes = 4
};

const msg_t menu_invalido = {
    .mensaje = {
        "El valor ingresado es invalido, intente nuevamente"
    },
    .cant_mensajes = 1
};

const msg_t menu_frecenciaCambiada = {
    .mensaje = {
        "La frecuencia se cambió con exitos"
    },
    .cant_mensajes = 1
};
const msg_t menu_preguntarFrecuencia = {
    .mensaje = {
        "Ingrese la nueva frecuencia de salida: "
    },
    .cant_mensajes = 1
};

void menu_show();
void menu_ADC_print(uint8_t adc);
uint16_t menu_readValue(bool *lei);

estado_t estado;

void mef_init(void) {
    estado.fun_estado = estado_INICIO;
    estado.primeraVez = true;
};

void mef_process() {
    estado.fun_estado();
}

void mef_cambiar(void(*fun)(void)) {
    estado.fun_estado = fun;
    estado.primeraVez = true;
}


void estado_INICIO() {
    int8_t opcion;
    bool lei;
    if(estado.primeraVez) {
        terminal_escribirMsg(&menu_principal);
        estado.primeraVez = false;
    }
    opcion = menu_readValue(&lei);
    if(lei && opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion)
        {
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


void estado_MENU_ADC() {
    int8_t opcion;
    bool lei;
    if(estado.primeraVez) {
        terminal_escribirMsg(&menu_ADC);
        estado.primeraVez = false;
    }
    opcion = menu_readValue(&lei);
    if(lei && opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion) {
        case 1:
        case 2:
            menu_ADC_print(opcion);
            mef_cambiar(estado_INICIO);
            break;

        default:
            terminal_escribirMsg(&menu_invalido);
            mef_cambiar(estado_MENU_ADC);
            break;
        }
    }
}



void estado_CAMBIAR_FREQ() {
    uint16_t new_freq;
    bool lei;
    if(estado.primeraVez) {
        terminal_escribirMsg(&menu_preguntarFrecuencia);
        estado.primeraVez = false;
    }
    new_freq = menu_readValue(&lei);

    if(lei) {
        if(new_freq >= 10000 && new_freq < 65000) {  // verifico si es valida la frecuencia
            spwm_changeFrecuency(new_freq);
            terminal_escribirMsg(&menu_frecenciaCambiada);
            mef_cambiar(estado_INICIO);

        } else {
            terminal_escribirMsg(&menu_invalido);
            mef_cambiar(estado_CAMBIAR_FREQ);
        }
    }
}



void menu_ADC_print(uint8_t adc) {
    char buffer[50];
    uint16_t adcRead;
        terminal_escribir("Valor del ADC");
    if(adc == 1) {
        terminal_escribir("1: ");

    } else {
        terminal_escribir("2: ");
    }
    adc_ConvertionStart(adc);
    while(!adc_ConvertionStoped(adc));
    adcRead =  adc_getData(adc);
    itoa (adcRead,buffer,10);
    terminal_escribir(buffer);
    terminal_escribir("\r\n");
}

uint16_t menu_readValue(bool *lei) {
    *lei = false;
    char dato[50];
    uint8_t cant;

    cant = terminal_getCommand(dato);
    if(cant > 0) { // leí datos
        *lei = true;
        return atoi(dato);
    }
    return 0;
}
