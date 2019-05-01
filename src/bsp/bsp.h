/**
 * @file bsp.h
 * @author Ricardo Martín Marcucci
 * @brief Cabecera del BSP para ser incluida por la app como el BSP
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup bsp Boar Support Package
 * @ingroup TPF
 * @{
 */

#ifndef __BSP_H
#define __BSP_H

/* ----------------------------------------------------------------------------------------------------------------
 * Inclusion de cabeceras
 * ---------------------------------------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

/**
 * Servicios del BSP
 */
void bsp_init();

void bsp_delay(uint32_t d);


/**
 *  Servicios de Leds
 */

void led_toggle();

void led_on();

void led_off();


/**
 *  Servicios del PWM
 */

void setPWM(uint16_t duty);

uint64_t get_01msTick();


/**
 *  Servicios de la UART
 */
void uartSend(char c);

bool uartSendReady();

char uartRecibe();

bool uartRecibeHasData();


/**
 *  Servicios del ADC
 */
void adc_ConvertionStart(uint8_t adc);

bool adc_ConvertionStoped(uint8_t adc);

uint16_t adc_getData(uint8_t adc);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */

/** @} Doxygen module end*/