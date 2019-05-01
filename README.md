# Trabajo Practico Final

Código para el Trabajo Practico final de la materia Programación de Microcontroladores.

## Enunciado

1. Plataforma embebida: BluePill (STM32f103)

2. Aplicación:
    - Se realizará una aplicación utilice el módulo de PWM del microcontrolador para generar una señal senoidal (SPWM).
    - El software deberá también tomar muestras de dos canales de ADC y enviarlos al puerto serie.
    - El software podrá recibir por puerto serie un comando de configuración que cambie la frecuencia de la señal sinusoidal Generada (MEF).
    - El software utilizará la HAL provista por el fabricante, implementará una capa BSP para abstraerse de los periféricos y una capa de aplicación donde se implemente la lógica.

3. Periféricos:
    - ADC
    - PWM
    - UART
    - GPIO