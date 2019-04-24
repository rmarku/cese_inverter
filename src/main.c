#include "bsp/bsp.h"


int main(void)
{
  bsp_init();
  while (1)
  {
    led_toggle();
    bsp_delay(500);
  }
}
