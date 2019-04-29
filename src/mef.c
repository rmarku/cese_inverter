#include <stdbool.h>
#include <stdint.h>

#include "delay.h"
#include "buffercircular.h"
#include "spwm.h"

typedef struct {
    void(*fun_estado)(void);
    bool primeraVez;

} estado_t;

void estado_INICIO();

void estado_MENU_ADC();

void estado_CAMBIAR_FREQ();

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
    if(estado.primeraVez) {
        menu_show();
        estado.primeraVez = false;
    }
    opcion = menu_read();
    if(opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion)
        {
        case 1:
            mef_cambiar(estado_MENU_ADC);
            break;
        case 2:
            mef_cambiar(estado_CAMBIAR_FREQ);
            break;

        default:
            menu_invalido();
            mef_cambiar(estado_INICIO);
            break;
        }
    }
}


void estado_MENU_ADC() {
    int8_t opcion;
    if(estado.primeraVez) {
        menu_ADC_show();
        estado.primeraVez = false;
    }
    opcion = menu_read();
    if(opcion >= 0) {  // Solo si hay un evento de menu
        switch (opcion)
        {
        case 1:
            menu_showADC1();
            mef_cambiar(estado_INICIO);
            break;
        case 2:
            menu_showADC2();
            mef_cambiar(estado_INICIO);
            break;

        default:
            menu_invalido();
            mef_cambiar(estado_MENU_ADC);
            break;
        }
    }
}



void estado_CAMBIAR_FREQ() {
    uint16_t new_freq;
    bool lei;
    if(estado.primeraVez) {
        menu_preguntarFrecuencia();
        estado.primeraVez = false;
    }
    new_freq = menu_readValue(&lei);

    if(lei) {
        if(new_freq >= 10000 && new_freq < 65000) {  // verifico si es valida la frecuencia
            spwm_changeFrecuency(new_freq);
            menu_frecenciaCambiada();
            mef_cambiar(estado_INICIO);

        } else {
            menu_invalido();
            mef_cambiar(estado_CAMBIAR_FREQ);
        }
    }
}