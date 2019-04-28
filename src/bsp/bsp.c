/**
 * @file bsp.c
 * @author Marcucci Ricardo Martín
 * @brief Board Support Package,
 * @version 0.1
 * @date 2019-04-22
 *
 * @copyright Copyright (c) 2019
 *
 */
/*=====[Inclusion de su propia cabecera]=====================================*/
#include "bsp.h"

/*=====[Inclusiones de dependencias de funciones privadas]===================*/
#include "stm32f1xx.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_utils.h"
#include <stdint.h>

/*=====[Macros de definicion de constantes privadas]=========================*/

#define corrienteIn_Pin LL_GPIO_PIN_0
#define corrienteIn_GPIO_Port GPIOA
#define tensionIn_Pin LL_GPIO_PIN_1
#define tensionIn_GPIO_Port GPIOA
#define tensionOut_Pin LL_GPIO_PIN_2
#define tensionOut_GPIO_Port GPIOA
#define corrienteOut_Pin LL_GPIO_PIN_3
#define corrienteOut_GPIO_Port GPIOA
#define PWMn_Pin LL_GPIO_PIN_7
#define PWMn_GPIO_Port GPIOA
#define PWM_Pin LL_GPIO_PIN_8
#define PWM_GPIO_Port GPIOA
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0                                                   \
    ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,               \
                                4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1                                                   \
    ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,               \
                                3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2                                                   \
    ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,               \
                                2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3                                                   \
    ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,               \
                                1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4                                                   \
    ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,               \
                                0 bit  for subpriority */
#endif

/*=====[Macros estilo funcion privadas]======================================*/

/*=====[Definiciones de tipos de datos privados]=============================*/

/*=====[Definiciones de Variables globales publicas externas]================*/

/*=====[Definiciones de Variables globales publicas]=========================*/

/*=====[Definiciones de Variables globales privadas]=========================*/

uint64_t tick_01ms = 0;

/*=====[Prototipos de funciones privadas]====================================*/

void SystemClock_Config(void);

void gpio_init(void);
void adc1_init(void);
void adc2_init(void);
void uart_init(void);
void timer1_init(void);

void Error_Handler(void);
/*=====[Implementaciones de funciones publicas]==============================*/

/**
 * @brief Modificar el ciclo de trabajo de la onda.
 *
 * @param duty valor entre 0 -> 0% y 1000 -> 100%
 */
void setPWM(uint16_t duty) {
    LL_TIM_OC_SetCompareCH1(TIM1,
                            ((LL_TIM_GetAutoReload(TIM1) + 1) * duty / 1000));
}

/**
 * @brief
 *
 * @param c
 */
inline void uartSend(char c) {
    LL_USART_TransmitData8(USART1, c);
}
/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
inline bool uartSendReady(char c) {
    return 1 == LL_USART_IsActiveFlag_TXE(USART1);
}
/**
 * @brief
 *
 * @param c
 */
inline void uartRecibe(char c) {
    LL_USART_ReceiveData8(USART1);
}
/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
inline bool uartRecibeHasData(char c) {
    return 1 == LL_USART_IsActiveFlag_RXNE(USART1);
}

/**
 * @brief retorna el contador de 0.1ms
 * 
 */
uint64_t get_01msTick(){
    return tick_01ms;
}




/**
 * @brief Inicializa todos los perifeficos del uC e inicializa los otros
 *  dispositivos conectados a la placa.
 *
 */
void bsp_init() {

    // Habilito los clocks de los buses
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    // configuro el NVIC para las interrupciones
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    LL_GPIO_AF_Remap_SWJ_NOJTAG();

    // Inicializo los perifericos
    SystemClock_Config();
    gpio_init();
    adc1_init();
    adc2_init();
    timer1_init();
    uart_init();

    // Habilito el PWM
    LL_TIM_CC_EnableChannel(TIM1,
                            LL_TIM_CHANNEL_CH1N); /* Enable output on channel */
    LL_TIM_CC_EnableChannel(TIM1,
                            LL_TIM_CHANNEL_CH1); /* Enable output on channel */

    LL_TIM_EnableCounter(TIM1);

    LL_TIM_EnableAllOutputs(TIM1);

    // Habilito el ADC1
    LL_ADC_Enable(ADC1);
    LL_ADC_Enable(ADC2);

    LL_SYSTICK_EnableIT();
}

/**
 * @brief
 *
 */
void led_toggle() {
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
}

/**
 * @brief
 *
 */
void led_on() {
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
}
/**
 * @brief
 *
 */
void led_off() {
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
}

/**
 * @brief
 *
 * @param d
 */
void bsp_delay(uint32_t d) {
    LL_mDelay(d);
}


/**
 * @brief
 *
 */
void adc_ConvertionStart() {
    LL_ADC_REG_StartConversionSWStart(ADC1);
}

/**
 * @brief
 *
 */
bool adc_ConvertionStop() {
    return 1 == LL_ADC_IsActiveFlag_EOS(ADC1);
}

/**
 * @brief
 *
 * @return uint16_t
 */
uint16_t adc_getData() {
    return LL_ADC_REG_ReadConversionData12(ADC1);
}












/**
 * @brief Configuración de System Clock
 * @retval None
 */
void SystemClock_Config(void) {
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

    if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {
        Error_Handler();
    }
    LL_RCC_HSE_Enable();

    /* Esperar que el cristal esté estable */
    while (LL_RCC_HSE_IsReady() != 1) {
    }
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_2);
    LL_RCC_PLL_Enable();

    /* Esperar que el PLL esté estable */
    while (LL_RCC_PLL_IsReady() != 1) {
    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Esperar a que el system clock este estable */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }

    LL_InitTick(16000000, 10000U);
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SetSystemCoreClock(16000000);
    LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_2);
}

/**
 * @brief
 *
 */
void gpio_init(void) {
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void adc1_init(void) {
    LL_ADC_InitTypeDef ADC_InitStruct = {0};
    LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    /**ADC1 GPIO Configuration
    PA0-WKUP   ------> ADC1_IN0
    PA1   ------> ADC1_IN1
    PA2   ------> ADC1_IN2
    PA3   ------> ADC1_IN3
    */
    GPIO_InitStruct.Pin =
        corrienteIn_Pin | tensionIn_Pin | tensionOut_Pin | corrienteOut_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /** Common config
     */
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
    LL_ADC_Init(ADC1, &ADC_InitStruct);
    ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_DUAL_REG_SIMULT;
    LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
    ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
    ADC_REG_InitStruct.SequencerLength = 1;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
    ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
    ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
    LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
    /** Configure Regular Channel
     */
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1,
                                  LL_ADC_SAMPLINGTIME_1CYCLE_5);
}
/* ADC2 init function */
void adc2_init(void) {
    LL_ADC_InitTypeDef ADC_InitStruct = {0};
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    /**ADC2 GPIO Configuration
    PA0-WKUP   ------> ADC2_IN0
    PA1   ------> ADC2_IN1
    PA2   ------> ADC2_IN2
    PA3   ------> ADC2_IN3
    */
    GPIO_InitStruct.Pin =
        corrienteIn_Pin | tensionIn_Pin | tensionOut_Pin | corrienteOut_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /** Common config
     */
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
    LL_ADC_Init(ADC2, &ADC_InitStruct);
    ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
    ADC_REG_InitStruct.SequencerLength = 1;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
    ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
    ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
    LL_ADC_REG_Init(ADC2, &ADC_REG_InitStruct);
    /** Configure Regular Channel
     */
    LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
    LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_1,
                                  LL_ADC_SAMPLINGTIME_1CYCLE_5);
}

void uart_init(void) {
    LL_USART_InitTypeDef USART_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    LL_GPIO_AF_EnableRemap_USART1();

    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    LL_USART_Init(USART1, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_Enable(USART1);
}

void timer1_init(void) {
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    uint32_t TimOutClock = SystemCoreClock / 1;
    TIM_InitStruct.Prescaler = __LL_TIM_CALC_PSC(SystemCoreClock, 500000);
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload =
        __LL_TIM_CALC_ARR(TimOutClock, TIM_InitStruct.Prescaler, 30000);
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = (uint8_t)0x00;
    LL_TIM_Init(TIM1, &TIM_InitStruct);
    LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = ((LL_TIM_GetAutoReload(TIM1) + 1) / 2);
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH1);
    LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM1);
    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
    LL_TIM_BDTR_Init(TIM1, &TIM_BDTRInitStruct);

    /**TIM1 GPIO Configuration
    PA7     ------> TIM1_CH1N
    PA8     ------> TIM1_CH1
    */
    GPIO_InitStruct.Pin = PWMn_Pin | PWM_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LL_GPIO_AF_RemapPartial_TIM1();
}

/*=====[Implementaciones de funciones de interrupcion publicas]==============*/
void NMI_Handler(void) {}

/**
 * @brief Versión devil del servicio para la aplicación
 *
 */
void __attribute__((weak)) app_1ms();

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
    tick_01ms++;

    // cada 10 ticks 1ms
    if(tick_01ms%10 == 0) {
        app_1ms();
    }
}

/**
 * @brief Trap para fallas de hardware
 */
void HardFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief Trap para fallas de manejo de memoria
 */
void MemManage_Handler(void) {
    while (1) {
    }
}

/**
 * @brief Trap para fallas de buses y prefetch
 */
void BusFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {}

/**
 * @brief  Función para errores de las funciones HAL
 * @retval None
 */
void Error_Handler(void) {}
