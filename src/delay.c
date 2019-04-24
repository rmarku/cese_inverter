/**
 * @file delay.c
 * @author Ricardo Martín Marcucci
 * @brief Librería para implementar delays no bloqueantes
 * @version 0.1
 * @date 2019-04-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */
/*=====[Inclusion de su propia cabecera]=====================================*/
#include "delay.h"


static tick_t tick_counter = 0;

tick_t getTick() { return tick_counter; }

void delayConfig(delay_t *delay, tick_t duracion) {
  delay->endTime = getTick() + duracion;
}

bool delayEnded(delay_t *delay) {
  bool res = false;
  if (delay->endTime < getTick()) {
    res = true;
  }
  return res;
}

void delay_1ms() { tick_counter++; }
