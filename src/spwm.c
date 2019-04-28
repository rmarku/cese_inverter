#include "spwm.h"
#include "ondas.h"
#include "bsp/bsp.h"

void spwm_init(spwm_t *onda) {
    onda->frecuencia = 60000;
    onda->last_start = get_01msTick();
}


void spwm_process(spwm_t *onda) {
    uint64_t current = get_01msTick()-onda->last_start;
    uint32_t ticks_ciclo = 10000000 / onda->frecuencia;
    uint8_t idx;
    uint16_t value;

    // Analizo las etapas
    // Terminó un ciclo?
    if (current > ticks_ciclo) {
        onda->last_start += ticks_ciclo;
        current -= ticks_ciclo;
    }

    if(current >= ticks_ciclo * 3 / 4) { // 4to Cuarto
        idx = TAMANIO_ONDA * 4 - 2000000 /(ticks_ciclo * 100) * current/100 -1;
        value = 512 - onda_data[idx];
    } else if(current >= ticks_ciclo /2) { // 3er Cuarto
        idx = 2000000 /(ticks_ciclo * 100) * current/100 - TAMANIO_ONDA * 2;
        value = 512 - onda_data[idx];

    } else if(current >= ticks_ciclo  / 4) { // 2do Cuarto
        idx =  TAMANIO_ONDA * 2 - 2000000 /(ticks_ciclo * 100) * current /100- 1;
        value = 511 + onda_data[idx];

    } else { // 1er Cuarto
        idx = 2000000 /(ticks_ciclo * 100) * current /100;
        value = 511 + onda_data[idx];
    }
    setPWM( value );
}