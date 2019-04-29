#include "spwm.h"
#include "ondas.h"
#include "bsp/bsp.h"


spwm_t onda;




void spwm_init() {
    onda.frecuencia = 60000;
    onda.last_start = get_01msTick();
}


void spwm_process() {
    uint64_t current = get_01msTick()-onda.last_start;
    uint32_t ticks_ciclo = 10000000 / onda.frecuencia;
    uint8_t idx;
    uint16_t value;

    // Terminó un ciclo?
    if (current > ticks_ciclo) {
        onda.last_start += ticks_ciclo;
        current -= ticks_ciclo;
    }
    
    // Calculo posición de la muestra entre 0 y 199 según el tick actual
    // Lo realizo en 128 mas arriba para no utilizar floats
    idx = ((TAMANIO_ONDA * 4 * 128) / ticks_ciclo * current) / 128;

    if(current >= ticks_ciclo * 3 / 4) { // 4to Cuarto
        idx = TAMANIO_ONDA * 4 - idx - 1;
        value = 512 - onda_data[idx];

    } else if(current >= ticks_ciclo /2) { // 3er Cuarto
        idx = idx - TAMANIO_ONDA * 2;
        value = 512 - onda_data[idx];

    } else if(current >= ticks_ciclo  / 4) { // 2do Cuarto
        idx =  TAMANIO_ONDA * 2 - idx - 1;
        value = 511 + onda_data[idx];

    } else { // 1er Cuarto
        idx = idx;
        value = 511 + onda_data[idx];
    }
    setPWM( value );
}

void spwm_changeFrecuency( uint16_t freq){
    // TODO: Realizar el calculo para que la nueva frecuencia continuel desde
    // la muestra actual
    onda.frecuencia = freq;
}