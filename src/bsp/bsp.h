#ifndef __BSP_H
#define __BSP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void bsp_init();
void led_toggle();
void bsp_delay(uint32_t d);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */