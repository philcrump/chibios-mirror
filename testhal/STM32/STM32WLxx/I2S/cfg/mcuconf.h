/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * STM32WLxx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

#ifndef MCUCONF_H
#define MCUCONF_H

#define STM32WLxx_MCUCONF

/*
 * HAL driver system settings.
 */
#define STM32_NO_INIT                       FALSE
#define STM32_CLOCK_DYNAMIC                 TRUE
#define STM32_TARGET_CORE                   1

#define STM32_VOS                           STM32_VOS_RANGE1
#define STM32_PWR_CR2                       (PWR_CR2_PLS_LVL0)
#define STM32_PWR_PUCRA                     (0UL)
#define STM32_PWR_PDCRA                     (0UL)
#define STM32_PWR_PUCRB                     (0UL)
#define STM32_PWR_PDCRB                     (0UL)
#define STM32_PWR_PUCRC                     (0UL)
#define STM32_PWR_PDCRC                     (0UL)
#define STM32_PWR_PUCRH                     (0UL)
#define STM32_PWR_PDCRH                     (0UL)
#define STM32_HSI16_ENABLED                 FALSE
#define STM32_LSI_ENABLED                   TRUE
#define STM32_LSIPRE                        STM32_LSIPRE_NODIV
#define STM32_HSE32_ENABLED                 FALSE
#define STM32_HSE32SRC                      STM32_HSE32_XTAL
#define STM32_LSE_ENABLED                   TRUE
#define STM32_MSIPLL_ENABLED                FALSE
#define STM32_MSIRANGE                      STM32_MSIRANGE_16M
#define STM32_MSISRANGE                     STM32_MSISRANGE_4M
#define STM32_SW                            STM32_SW_PLL
#define STM32_PLLSRC                        STM32_PLLSRC_MSI
#define STM32_PLLM_VALUE                    1
#define STM32_PLLN_VALUE                    6
#define STM32_PLLR_VALUE                    2
#define STM32_PLLP_VALUE                    2
#define STM32_PLLQ_VALUE                    2
#define STM32_HPRE                          STM32_HPRE_DIV1
#define STM32_C2HPRE                        STM32_C2HPRE_DIV1
#define STM32_SHDHPRE                       STM32_SHDHPRE_DIV1
#define STM32_PPRE1                         STM32_PPRE1_DIV1
#define STM32_PPRE2                         STM32_PPRE2_DIV1
#define STM32_STOPWUCK                      STM32_STOPWUCK_MSI
#define STM32_MCOSEL                        STM32_MCOSEL_NOCLOCK
#define STM32_MCOPRE                        STM32_MCOPRE_DIV1
#define STM32_LSCOSEL                       STM32_LSCOSEL_NOCLOCK

/*
 * Peripherals clock sources.
 */
#define STM32_ADCSEL                        STM32_ADCSEL_SYSCLK
#define STM32_USART1SEL                     STM32_USART1SEL_SYSCLK
#define STM32_USART2SEL                     STM32_USART2SEL_SYSCLK
#define STM32_LPUART1SEL                    STM32_LPUART1SEL_SYSCLK
#define STM32_I2C1SEL                       STM32_I2C1SEL_SYSCLK
#define STM32_I2C3SEL                       STM32_I2C3SEL_SYSCLK
#define STM32_LPTIM1SEL                     STM32_LPTIM1SEL_PCLK1
#define STM32_LPTIM2SEL                     STM32_LPTIM2SEL_PCLK1
#define STM32_LPTIM3SEL                     STM32_LPTIM3SEL_PCLK1
#define STM32_SPI2S2SEL                     STM32_SPI2S2SEL_PLLQCLK
#define STM32_RNGSEL                        STM32_RNGSEL_PLLQCLK
#define STM32_RTCSEL                        STM32_RTCSEL_LSE

/*
 * IRQ system settings.
 */
#define STM32_IRQ_EXTI0_PRIORITY            6
#define STM32_IRQ_EXTI1_PRIORITY            6
#define STM32_IRQ_EXTI2_PRIORITY            6
#define STM32_IRQ_EXTI3_PRIORITY            6
#define STM32_IRQ_EXTI4_PRIORITY            6
#define STM32_IRQ_EXTI5_9_PRIORITY          6
#define STM32_IRQ_EXTI10_15_PRIORITY        6
#define STM32_IRQ_EXTI17_PRIORITY           6
#define STM32_IRQ_EXTI18_PRIORITY           6
#define STM32_IRQ_EXTI19_PRIORITY           6
#define STM32_IRQ_EXTI20_PRIORITY           6
#define STM32_IRQ_EXTI16_34_PRIORITY        6
#define STM32_IRQ_EXTI45_PRIORITY           6

#define STM32_IRQ_TIM1_BRK_PRIORITY         7
#define STM32_IRQ_TIM1_UP_PRIORITY          7
#define STM32_IRQ_TIM1_TRGCO_PRIORITY       7
#define STM32_IRQ_TIM1_CC_PRIORITY          7
#define STM32_IRQ_TIM2_PRIORITY             7
#define STM32_IRQ_TIM16_PRIORITY            7
#define STM32_IRQ_TIM17_PRIORITY            7
#define STM32_IRQ_LPTIM1_PRIORITY           7
#define STM32_IRQ_LPTIM2_PRIORITY           7
#define STM32_IRQ_LPTIM3_PRIORITY           7

#define STM32_IRQ_USART1_PRIORITY           12
#define STM32_IRQ_USART2_PRIORITY           12
#define STM32_IRQ_LPUART1_PRIORITY          12

/*
 * ADC driver system settings.
 */
#define STM32_ADC_COMPACT_SAMPLES           FALSE
#define STM32_ADC_USE_ADC1                  FALSE
#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
#define STM32_ADC_ADC1_DMA_PRIORITY         2
#define STM32_ADC_ADC1_IRQ_PRIORITY         5
#define STM32_ADC_ADC1_DMA_IRQ_PRIORITY     5

/*
 * DAC driver system settings.
 */
#define STM32_DAC_DUAL_MODE                 FALSE
#define STM32_DAC_USE_DAC1_CH1              FALSE
#define STM32_DAC_USE_DAC1_CH2              FALSE
#define STM32_DAC_DAC1_CH1_IRQ_PRIORITY     10
#define STM32_DAC_DAC1_CH2_IRQ_PRIORITY     10
#define STM32_DAC_DAC1_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH2_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH1_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC1_CH2_DMA_STREAM       STM32_DMA_STREAM_ID_ANY

/*
 * GPT driver system settings.
 */
#define STM32_GPT_USE_TIM1                  FALSE
#define STM32_GPT_USE_TIM2                  FALSE
#define STM32_GPT_USE_TIM16                 FALSE
#define STM32_GPT_USE_TIM17                 FALSE

/*
 * I2C driver system settings.
 */
#define STM32_I2C_USE_I2C1                  FALSE
#define STM32_I2C_USE_I2C3                  FALSE
#define STM32_I2C_BUSY_TIMEOUT              50
#define STM32_I2C_I2C1_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C1_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C3_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C3_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C1_IRQ_PRIORITY         5
#define STM32_I2C_I2C3_IRQ_PRIORITY         5
#define STM32_I2C_I2C1_DMA_PRIORITY         3
#define STM32_I2C_I2C3_DMA_PRIORITY         3
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define STM32_ICU_USE_TIM1                  FALSE
#define STM32_ICU_USE_TIM2                  FALSE
#define STM32_ICU_USE_TIM16                 FALSE
#define STM32_ICU_USE_TIM17                 FALSE

/*
 * PWM driver system settings.
 */
#define STM32_PWM_USE_ADVANCED              FALSE
#define STM32_PWM_USE_TIM1                  FALSE
#define STM32_PWM_USE_TIM2                  FALSE
#define STM32_PWM_USE_TIM16                 FALSE
#define STM32_PWM_USE_TIM17                 FALSE

/*
 * RTC driver system settings.
 */
#define STM32_RTC_PRESA_VALUE               128
#define STM32_RTC_PRESS_VALUE               256
#define STM32_RTC_CR_INIT                   0
#define STM32_RTC_TAMPCR_INIT               0

/*
 * SERIAL driver system settings.
 */
#define STM32_SERIAL_USE_USART1             FALSE
#define STM32_SERIAL_USE_USART2             FALSE
#define STM32_SERIAL_USE_LPUART1            FALSE
#define STM32_SERIAL_USART1_PRIORITY        12
#define STM32_SERIAL_USART2_PRIORITY        12
#define STM32_SERIAL_LPUART1_PRIORITY       12

/*
 * SPI driver system settings.
 */
#define STM32_SPI_USE_SPI1                  FALSE
#define STM32_SPI_USE_SPI2                  FALSE
#define STM32_SPI_USE_SPI3                  FALSE
#define STM32_SPI_SPI1_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI1_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI2_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI2_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI3_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI3_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI1_DMA_PRIORITY         1
#define STM32_SPI_SPI2_DMA_PRIORITY         1
#define STM32_SPI_SPI1_IRQ_PRIORITY         10
#define STM32_SPI_SPI2_IRQ_PRIORITY         10
#define STM32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * I2S driver system settings.
 */
#define STM32_I2S_USE_SPI2                  TRUE
#define STM32_I2S_SPI2_IRQ_PRIORITY         10
#define STM32_I2S_SPI2_DMA_PRIORITY         1
#define STM32_I2S_SPI2_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2S_SPI2_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2S_DMA_ERROR_HOOK(i2sp)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define STM32_ST_IRQ_PRIORITY               8
#define STM32_ST_USE_TIMER                  2

/*
 * TRNG driver system settings.
 */
#define STM32_TRNG_USE_RNG1                 FALSE

/*
 * UART driver system settings.
 */
#define STM32_UART_USE_USART1               FALSE
#define STM32_UART_USE_USART2               FALSE
#define STM32_UART_USE_LPUART1              FALSE
#define STM32_UART_USART1_RX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART1_TX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART2_RX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART2_TX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_LPUART1_RX_DMA_STREAM    STM32_DMA_STREAM_ID_ANY
#define STM32_UART_LPUART1_TX_DMA_STREAM    STM32_DMA_STREAM_ID_ANY
#define STM32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * WDG driver system settings.
 */
#define STM32_WDG_USE_IWDG                  FALSE


/* STM32FLASH driver settings */
#define STM32FLASH_SECTORS_COUNT            128
#define STM32FLASH_SECTOR_SIZE              (2 * 1024)
#define STM32FLASH_PAGE_SIZE                8

#endif /* MCUCONF_H */
