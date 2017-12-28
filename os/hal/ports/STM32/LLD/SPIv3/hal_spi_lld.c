/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

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

/**
 * @file    SPIv2/hal_spi_lld.c
 * @brief   STM32 SPI subsystem low level driver source.
 *
 * @addtogroup SPI
 * @{
 */

#include "hal.h"

#if HAL_USE_SPI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief SPI1 driver identifier.*/
#if STM32_SPI_USE_SPI1 || defined(__DOXYGEN__)
SPIDriver SPID1;
#endif

/** @brief SPI2 driver identifier.*/
#if STM32_SPI_USE_SPI2 || defined(__DOXYGEN__)
SPIDriver SPID2;
#endif

/** @brief SPI3 driver identifier.*/
#if STM32_SPI_USE_SPI3 || defined(__DOXYGEN__)
SPIDriver SPID3;
#endif

/** @brief SPI4 driver identifier.*/
#if STM32_SPI_USE_SPI4 || defined(__DOXYGEN__)
SPIDriver SPID4;
#endif

/** @brief SPI5 driver identifier.*/
#if STM32_SPI_USE_SPI5 || defined(__DOXYGEN__)
SPIDriver SPID5;
#endif

/** @brief SPI6 driver identifier.*/
#if STM32_SPI_USE_SPI6 || defined(__DOXYGEN__)
SPIDriver SPID6;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

static const uint32_t dummytx = STM32_SPI_FILLER_PATTERN;
static uint32_t dummyrx;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Shared DMA service routine.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void spi_serve_dma_interrupt(SPIDriver *spip, uint32_t flags) {

  /* DMA errors handling.*/
#if defined(STM32_SPI_DMA_ERROR_HOOK)
  (void)spip;
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    STM32_SPI_DMA_ERROR_HOOK(spip);
  }
#else
  (void)spip;
  (void)flags;
#endif
}

/**
 * @brief   Shared SPI service routine.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 */
static void spi_lld_serve_interrupt(SPIDriver *spip) {
  uint32_t sr;

  sr = spip->spi->SR & spip->spi->IER;
  spip->spi->IFCR = sr;

  if ((sr & SPI_SR_EOT) != 0U) {
    /* Stop everything.*/
    dmaStreamDisable(spip->dmatx);
    dmaStreamDisable(spip->dmarx);

    /* Portable SPI ISR code defined in the high level driver, note, it is
       a macro.*/
    _spi_isr_code(spip);
  }
  else if ((sr & SPI_SR_OVR) != 0U) {
    /* TODO: faut notification.*/
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_SPI_USE_SPI1 || defined(__DOXYGEN__)
#if !defined(STM32_SPI1_SUPPRESS_ISR)
#if !defined(STM32_SPI1_HANDLER)
#error "STM32_SPI1_HANDLER not defined"
#endif
/**
 * @brief   SPI1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI1_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID1);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI1_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI1 */

#if STM32_SPI_USE_SPI2 || defined(__DOXYGEN__)
#if !defined(STM32_SPI2_SUPPRESS_ISR)
#if !defined(STM32_SPI2_HANDLER)
#error "STM32_SPI2_HANDLER not defined"
#endif
/**
 * @brief   SPI2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI2_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID2);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI2_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI2 */

#if STM32_SPI_USE_SPI3 || defined(__DOXYGEN__)
#if !defined(STM32_SPI3_SUPPRESS_ISR)
#if !defined(STM32_SPI3_HANDLER)
#error "STM32_SPI3_HANDLER not defined"
#endif
/**
 * @brief   SPI3 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI3_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID3);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI3_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI3 */

#if STM32_SPI_USE_SPI4 || defined(__DOXYGEN__)
#if !defined(STM32_SPI4_SUPPRESS_ISR)
#if !defined(STM32_SPI4_HANDLER)
#error "STM32_SPI4_HANDLER not defined"
#endif
/**
 * @brief   SPI4 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI4_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID4);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI4_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI4 */

#if STM32_SPI_USE_SPI5 || defined(__DOXYGEN__)
#if !defined(STM32_SPI5_SUPPRESS_ISR)
#if !defined(STM32_SPI5_HANDLER)
#error "STM32_SPI5_HANDLER not defined"
#endif
/**
 * @brief   SPI5 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI5_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID5);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI5_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI5 */

#if STM32_SPI_USE_SPI6 || defined(__DOXYGEN__)
#if !defined(STM32_SPI6_SUPPRESS_ISR)
#if !defined(STM32_SPI6_HANDLER)
#error "STM32_SPI6_HANDLER not defined"
#endif
/**
 * @brief   SPI6 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_SPI6_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  spi_lld_serve_interrupt(&SPID6);

  OSAL_IRQ_EPILOGUE();
}
#endif /* !defined(STM32_SPI6_SUPPRESS_ISR) */
#endif /* STM32_SPI_USE_SPI6 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level SPI driver initialization.
 *
 * @notapi
 */
void spi_lld_init(void) {

#if STM32_SPI_USE_SPI1
  spiObjectInit(&SPID1);
  SPID1.spi       = SPI1;
  SPID1.dmarx     = STM32_DMA_STREAM(STM32_SPI_SPI1_RX_DMA_CHANNEL);
  SPID1.dmatx     = STM32_DMA_STREAM(STM32_SPI_SPI1_TX_DMA_CHANNEL);
  SPID1.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI1_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID1.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI1_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI1_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI1_NUMBER, STM32_SPI_SPI1_IRQ_PRIORITY);
#endif
#endif

#if STM32_SPI_USE_SPI2
  spiObjectInit(&SPID2);
  SPID2.spi       = SPI2;
  SPID2.dmarx     = STM32_DMA_STREAM(STM32_SPI_SPI2_RX_DMA_CHANNEL);
  SPID2.dmatx     = STM32_DMA_STREAM(STM32_SPI_SPI2_TX_DMA_CHANNEL);
  SPID2.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID2.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI2_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI2_NUMBER, STM32_SPI_SPI2_IRQ_PRIORITY);
#endif
#endif

#if STM32_SPI_USE_SPI3
  spiObjectInit(&SPID3);
  SPID3.spi       = SPI3;
  SPID3.dmarx     = STM32_DMA_STREAM(STM32_SPI_SPI3_RX_DMA_CHANNEL);
  SPID3.dmatx     = STM32_DMA_STREAM(STM32_SPI_SPI3_TX_DMA_CHANNEL);
  SPID3.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI3_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID3.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI3_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI3_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI3_NUMBER, STM32_SPI_SPI3_IRQ_PRIORITY);
#endif
#endif

#if STM32_SPI_USE_SPI4
  spiObjectInit(&SPID4);
  SPID4.spi       = SPI4;
  SPID4.dmarx     = STM32_DMA_STREAM(STM32_SPI_SPI4_RX_DMA_CHANNEL);
  SPID4.dmatx     = STM32_DMA_STREAM(STM32_SPI_SPI4_TX_DMA_CHANNEL);
  SPID4.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI4_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID4.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI4_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI4_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI4_NUMBER, STM32_SPI_SPI4_IRQ_PRIORITY);
#endif
#endif

#if STM32_SPI_USE_SPI5
  spiObjectInit(&SPID5);
  SPID5.spi       = SPI5;
  SPID5.dmarx     = STM32_DMA_STREAM(STM32_SPI_SPI5_RX_DMA_CHANNEL);
  SPID5.dmatx     = STM32_DMA_STREAM(STM32_SPI_SPI5_TX_DMA_CHANNEL);
  SPID5.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI5_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID5.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI5_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI5_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI5_NUMBER, STM32_SPI_SPI5_IRQ_PRIORITY);
#endif
#endif

#if STM32_SPI_USE_SPI6
  spiObjectInit(&SPID6);
  SPID6.spi       = SPI6;
  SPID6.dmarx     = STM32_BDMA_STREAM(STM32_SPI_SPI6_RX_BDMA_CHANNEL);
  SPID6.dmatx     = STM32_BDMA_STREAM(STM32_SPI_SPI6_TX_BDMA_CHANNEL);
  SPID6.rxdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI6_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_P2M |
                    STM32_DMA_CR_TCIE |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
  SPID6.txdmamode = STM32_DMA_CR_PL(STM32_SPI_SPI6_DMA_PRIORITY) |
                    STM32_DMA_CR_DIR_M2P |
                    STM32_DMA_CR_DMEIE |
                    STM32_DMA_CR_TEIE;
#if !defined(STM32_SPI6_SUPPRESS_ISR)
  nvicEnableVector(STM32_SPI6_NUMBER, STM32_SPI_SPI6_IRQ_PRIORITY);
#endif
#endif
}

/**
 * @brief   Configures and activates the SPI peripheral.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 *
 * @notapi
 */
void spi_lld_start(SPIDriver *spip) {
  uint32_t dsize, cfg1;

  /* If in stopped state then enables the SPI and DMA clocks.*/
  if (spip->state == SPI_STOP) {
#if STM32_SPI_USE_SPI1
    if (&SPID1 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI1_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI1_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI1(false);
    }
#endif
#if STM32_SPI_USE_SPI2
    if (&SPID2 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI2_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI2_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI2(false);
    }
#endif
#if STM32_SPI_USE_SPI3
    if (&SPID3 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI3_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI3_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI3(false);
    }
#endif
#if STM32_SPI_USE_SPI4
    if (&SPID4 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI4_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI4_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI4(false);
    }
#endif
#if STM32_SPI_USE_SPI5
    if (&SPID5 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI5_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI5_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI5(false);
    }
#endif
#if STM32_SPI_USE_SPI6
    if (&SPID6 == spip) {
      bool b;
      b = dmaStreamAllocate(spip->dmarx,
                            STM32_SPI_SPI6_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      b = dmaStreamAllocate(spip->dmatx,
                            STM32_SPI_SPI6_IRQ_PRIORITY,
                            (stm32_dmaisr_t)spi_serve_dma_interrupt,
                            (void *)spip);
      osalDbgAssert(!b, "stream already allocated");
      rccEnableSPI6(false);
    }
#endif

    /* DMA setup.*/
    dmaStreamSetPeripheral(spip->dmarx, &spip->spi->RXDR);
    dmaStreamSetPeripheral(spip->dmatx, &spip->spi->TXDR);
    dmaStreamSetTransactionSize(spip->dmarx, 0U);
    dmaStreamSetTransactionSize(spip->dmatx, 0U);
 }

  /* Configuration-specific DMA setup.*/
  dsize = (spip->config->cfg2 & SPI_CFG1_DSIZE_Msk) + 1U;
  cfg1  = spip->config->cfg1 | SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN;
  if (dsize <= 8U) {
    /* Frame width is between 4 and 8 bits.*/
    spip->rxdmamode = (spip->rxdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE |
                      STM32_DMA_CR_PFCTRL;
    spip->txdmamode = (spip->txdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE |
                      STM32_DMA_CR_PFCTRL;
    cfg1 |= SPI_CFG1_FTHLV_2;   /* FTHLV = 4.*/
  }
  else if (dsize <= 16U) {
    /* Frame width is between 9 and 16 bits.*/
    spip->rxdmamode = (spip->rxdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD |
                      STM32_DMA_CR_PFCTRL;
    spip->txdmamode = (spip->txdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD |
                      STM32_DMA_CR_PFCTRL;
    cfg1 |= SPI_CFG1_FTHLV_1;   /* FTHLV = 2.*/
  }
  else {
    /* Frame width is between 16 and 32 bits.*/
    spip->rxdmamode = (spip->rxdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
                      STM32_DMA_CR_PFCTRL;
    spip->txdmamode = (spip->txdmamode & ~STM32_DMA_CR_SIZE_MASK) |
                      STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
                      STM32_DMA_CR_PFCTRL;
    cfg1 |= SPI_CFG1_FTHLV_0;   /* FTHLV = 1.*/
  }

  /* SPI setup and enable.*/
  spip->spi->CR1 &= ~SPI_CR1_SPE;
  spip->spi->CR1  = SPI_CR1_MASRX;
  spip->spi->CR2  = 0U;
  spip->spi->CFG1 = cfg1;
  spip->spi->CFG2 = spip->config->cfg2 | SPI_CFG2_MASTER;
  spip->spi->IER  = SPI_IER_OVRIE | SPI_IER_EOTIE;
  spip->spi->IFCR = 0xFFFFFFFFU;
  spip->spi->CR1 |= SPI_CR1_SPE;
}

/**
 * @brief   Deactivates the SPI peripheral.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 *
 * @notapi
 */
void spi_lld_stop(SPIDriver *spip) {

  /* If in ready state then disables the SPI clock.*/
  if (spip->state == SPI_READY) {

    /* SPI disable.*/
    spip->spi->CR1 &= ~SPI_CR1_SPE;
    spip->spi->CR1  = 0U;
    spip->spi->CR2  = 0U;
    spip->spi->CFG1 = 0U;
    spip->spi->CFG2 = 0U;
    spip->spi->IER  = 0U;
    dmaStreamRelease(spip->dmarx);
    dmaStreamRelease(spip->dmatx);

#if STM32_SPI_USE_SPI1
    if (&SPID1 == spip)
      rccDisableSPI1();
#endif
#if STM32_SPI_USE_SPI2
    if (&SPID2 == spip)
      rccDisableSPI2();
#endif
#if STM32_SPI_USE_SPI3
    if (&SPID3 == spip)
      rccDisableSPI3();
#endif
#if STM32_SPI_USE_SPI4
    if (&SPID4 == spip)
      rccDisableSPI4();
#endif
#if STM32_SPI_USE_SPI5
    if (&SPID5 == spip)
      rccDisableSPI5();
#endif
#if STM32_SPI_USE_SPI6
    if (&SPID6 == spip)
      rccDisableSPI6();
#endif
  }
}

#if (SPI_SELECT_MODE == SPI_SELECT_MODE_LLD) || defined(__DOXYGEN__)
/**
 * @brief   Asserts the slave select signal and prepares for transfers.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 *
 * @notapi
 */
void spi_lld_select(SPIDriver *spip) {

  /* No implementation on STM32.*/
}

/**
 * @brief   Deasserts the slave select signal.
 * @details The previously selected peripheral is unselected.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 *
 * @notapi
 */
void spi_lld_unselect(SPIDriver *spip) {

  /* No implementation on STM32.*/
}
#endif

/**
 * @brief   Ignores data on the SPI bus.
 * @details This asynchronous function starts the transmission of a series of
 *          idle words on the SPI bus and ignores the received data.
 * @post    At the end of the operation the configured callback is invoked.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] n         number of words to be ignored
 *
 * @notapi
 */
void spi_lld_ignore(SPIDriver *spip, size_t n) {

  osalDbgAssert(n < 65536, "unsupported DMA transfer size");

  dmaStreamSetMemory0(spip->dmarx, &dummyrx);
  dmaStreamSetMode(spip->dmarx, spip->rxdmamode);

  dmaStreamSetMemory0(spip->dmatx, &dummytx);
  dmaStreamSetMode(spip->dmatx, spip->txdmamode);

  dmaStreamEnable(spip->dmarx);
  dmaStreamEnable(spip->dmatx);

  spip->spi->CR2 = (uint32_t)n;
  spip->spi->CR1 |= SPI_CR1_CSTART;
}

/**
 * @brief   Exchanges data on the SPI bus.
 * @details This asynchronous function starts a simultaneous transmit/receive
 *          operation.
 * @post    At the end of the operation the configured callback is invoked.
 * @note    The buffers are organized as uint8_t arrays for data sizes below or
 *          equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] n         number of words to be exchanged
 * @param[in] txbuf     the pointer to the transmit buffer
 * @param[out] rxbuf    the pointer to the receive buffer
 *
 * @notapi
 */
void spi_lld_exchange(SPIDriver *spip, size_t n,
                      const void *txbuf, void *rxbuf) {

  osalDbgAssert(n < 65536, "unsupported DMA transfer size");

  dmaStreamSetMemory0(spip->dmarx, rxbuf);
  dmaStreamSetMode(spip->dmarx, spip->rxdmamode | STM32_DMA_CR_MINC);

  dmaStreamSetMemory0(spip->dmatx, txbuf);
  dmaStreamSetMode(spip->dmatx, spip->txdmamode | STM32_DMA_CR_MINC);

  dmaStreamEnable(spip->dmarx);
  dmaStreamEnable(spip->dmatx);

  spip->spi->CR2 = (uint32_t)n;
  spip->spi->CR1 |= SPI_CR1_CSTART;
}

/**
 * @brief   Sends data over the SPI bus.
 * @details This asynchronous function starts a transmit operation.
 * @post    At the end of the operation the configured callback is invoked.
 * @note    The buffers are organized as uint8_t arrays for data sizes below or
 *          equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] n         number of words to send
 * @param[in] txbuf     the pointer to the transmit buffer
 *
 * @notapi
 */
void spi_lld_send(SPIDriver *spip, size_t n, const void *txbuf) {

  osalDbgAssert(n < 65536, "unsupported DMA transfer size");

  dmaStreamSetMemory0(spip->dmarx, &dummyrx);
  dmaStreamSetMode(spip->dmarx, spip->rxdmamode);

  dmaStreamSetMemory0(spip->dmatx, txbuf);
  dmaStreamSetMode(spip->dmatx, spip->txdmamode | STM32_DMA_CR_MINC);

  dmaStreamEnable(spip->dmarx);
  dmaStreamEnable(spip->dmatx);

  spip->spi->CR2 = (uint32_t)n;
  spip->spi->CR1 |= SPI_CR1_CSTART;
}

/**
 * @brief   Receives data from the SPI bus.
 * @details This asynchronous function starts a receive operation.
 * @post    At the end of the operation the configured callback is invoked.
 * @note    The buffers are organized as uint8_t arrays for data sizes below or
 *          equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] n         number of words to receive
 * @param[out] rxbuf    the pointer to the receive buffer
 *
 * @notapi
 */
void spi_lld_receive(SPIDriver *spip, size_t n, void *rxbuf) {

  osalDbgAssert(n < 65536, "unsupported DMA transfer size");

  dmaStreamSetMemory0(spip->dmarx, rxbuf);
  dmaStreamSetMode(spip->dmarx, spip->rxdmamode | STM32_DMA_CR_MINC);

  dmaStreamSetMemory0(spip->dmatx, &dummytx);
  dmaStreamSetMode(spip->dmatx, spip->txdmamode);

  dmaStreamEnable(spip->dmarx);
  dmaStreamEnable(spip->dmatx);

  spip->spi->CR2 = (uint32_t)n;
  spip->spi->CR1 |= SPI_CR1_CSTART;
}

/**
 * @brief   Exchanges one frame using a polled wait.
 * @details This synchronous function exchanges one frame using a polled
 *          synchronization method. This function is useful when exchanging
 *          small amount of data on high speed channels, usually in this
 *          situation is much more efficient just wait for completion using
 *          polling than suspending the thread waiting for an interrupt.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] frame     the data frame to send over the SPI bus
 * @return              The received data frame from the SPI bus.
 */
uint16_t spi_lld_polled_exchange(SPIDriver *spip, uint16_t frame) {
#if 0
  /*
   * Data register must be accessed with the appropriate data size.
   * Byte size access (uint8_t *) for transactions that are <= 8-bit.
   * Halfword size access (uint16_t) for transactions that are <= 8-bit.
   */
  if ((spip->config->cr2 & SPI_CR2_DS) <= (SPI_CR2_DS_2 |
                                           SPI_CR2_DS_1 |
                                           SPI_CR2_DS_0)) {
    volatile uint8_t *spidr = (volatile uint8_t *)&spip->spi->RXDR;
    *spidr = (uint8_t)frame;
    while ((spip->spi->SR & SPI_SR_RXNE) == 0)
      ;
    return (uint16_t)*spidr;
  }
  else {
    spip->spi->TXDR = frame;
    while ((spip->spi->SR & SPI_SR_RXNE) == 0)
      ;
    return spip->spi->DR;
  }
#else
  (void)spip;
  (void)frame;
  return 0;
#endif
}

#endif /* HAL_USE_SPI */

/** @} */
