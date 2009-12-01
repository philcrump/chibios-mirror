/*
    ChibiOS/RT - Copyright (C) 2006-2007 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file STM32/can_lld.h
 * @brief STM32 CAN subsystem low level driver header
 * @addtogroup STM32_CAN
 * @{
 */

#ifndef _CAN_LLD_H_
#define _CAN_LLD_H_

#if CH_HAL_USE_CAN || defined(__DOXYGEN__)

/**
 * @brief This switch defines whether the driver implementation supports
 *        a low power switch mode with automatic an wakeup feature.
 */
#define CAN_SUPPORTS_SLEEP  TRUE

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief CAN1 driver enable switch.
 * @details If set to @p TRUE the support for ADC1 is included.
 * @note The default is @p TRUE.
 */
#if !defined(USE_STM32_CAN1) || defined(__DOXYGEN__)
#define USE_STM32_CAN1              TRUE
#endif

/**
 * @brief CAN1 interrupt priority level setting.
 * @note @p BASEPRI_KERNEL >= @p STM32_SPI1_IRQ_PRIORITY > @p PRIORITY_PENDSV.
 */
#if !defined(STM32_CAN1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_CAN1_IRQ_PRIORITY     0xB0
#endif

/**
 * @brief Sleep mode related APIs inclusion switch.
 * @note This switch is enforced to @p FALSE if the driver implementation
 *       does not support the sleep mode.
 */
#if CAN_SUPPORTS_SLEEP || defined(__DOXYGEN__)
#if !defined(CAN_USE_SLEEP_MODE) || defined(__DOXYGEN__)
#define CAN_USE_SLEEP_MODE  TRUE
#endif
#else /* !CAN_SUPPORTS_SLEEP */
#define CAN_USE_SLEEP_MODE  FALSE
#endif /* !CAN_SUPPORTS_SLEEP */

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief CAN status flags.
 */
typedef uint32_t canstatus_t;

/**
 * @brief CAN frame.
 * @note Accessing the frame data as word16 or word32 is not portable because
 *       machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {
  uint8_t                   cf_DLC:4;       /**< @brief Data length.        */
  uint8_t                   cf_IDE:1;       /**< @brief Identifier type.    */
  uint8_t                   cf_RTR:1;       /**< @brief Frame type.         */
  uint32_t                  cf_id;          /**< @brief Frame identifier.   */
  union {
    uint8_t                 cf_data8[8];    /**< @brief Frame data.         */
    uint16_t                cf_data16[4];   /**< @brief Frame data.         */
    uint32_t                cf_data32[2];   /**< @brief Frame data.         */
  };
} CANFrame;

/**
 * @brief Driver configuration structure.
 */
typedef struct {
  /**
   * @brief CAN MCR register initialization data.
   * @note Some bits in this register are enforced by the driver regardless
   *       their status in this field.
   */
  uint32_t                  cc_mcr;
  /**
   * @brief CAN BTR register initialization data.
   * @note Some bits in this register are enforced by the driver regardless
   *       their status in this field.
   */
  uint32_t                  cc_btr;
} CANConfig;

/**
 * @brief Structure representing an CAN driver.
 */
typedef struct {
  /**
   * @brief Driver state.
   */
  canstate_t                cd_state;
  /**
   * @brief Current configuration data.
   */
  const CANConfig           *cd_config;
  /**
   * @brief Transmission queue semaphore.
   */
  Semaphore                 cd_txsem;
  /**
   * @brief Receive queue semaphore.
   */
  Semaphore                 cd_rxsem;
  /**
   * @brief One or more frames become available.
   */
  EventSource               cd_rxfull_event;
  /**
   * @brief One or more transmission slots become available.
   */
  EventSource               cd_txempty_event;
  /**
   * @brief A CAN bus error happened.
   */
  EventSource               cd_error_event;
  /**
   * @brief Error flags set when an error event is broadcasted.
   */
  canstatus_t               cd_status;
#if CAN_USE_SLEEP_MODE || defined (__DOXYGEN__)
  /**
   * @brief Entering sleep state event.
   */
  EventSource               cd_sleep_event;
  /**
   * @brief Exiting sleep state event.
   */
  EventSource               cd_wakeup_event;
#endif /* CAN_USE_SLEEP_MODE */
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the CAN registers.
   */
  CAN_TypeDef               *cd_can;
} CANDriver;

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/** @cond never*/
#if USE_STM32_CAN1
extern CANDriver CAND1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void can_lld_init(void);
  void can_lld_start(CANDriver *canp);
  void can_lld_stop(CANDriver *canp);
  bool_t can_lld_can_transmit(CANDriver *canp);
  msg_t can_lld_transmit(CANDriver *canp, const CANFrame *cfp);
  bool_t can_lld_can_receive(CANDriver *canp);
  msg_t can_lld_receive(CANDriver *canp, CANFrame *cfp);
#if CAN_USE_SLEEP_MODE
  void can_lld_sleep(CANDriver *canp);
  void can_lld_wakeup(CANDriver *canp);
#endif /* CAN_USE_SLEEP_MODE */
#ifdef __cplusplus
}
#endif
/** @endcond*/

#endif /* CH_HAL_USE_CAN */

#endif /* _CAN_LLD_H_ */

/** @} */
