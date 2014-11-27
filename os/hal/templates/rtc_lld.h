/*
    ChibiOS/HAL - Copyright (C) 2006-2014 Giovanni Di Sirio

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
   Concepts and parts of this file have been contributed by Uladzimir Pylinsky
   aka barthess.
 */

/**
 * @file    rtc_lld.h
 * @brief   PLATFORM RTC subsystem low level driver header.
 *
 * @addtogroup RTC
 * @{
 */

#ifndef _RTC_LLD_H_
#define _RTC_LLD_H_

#if HAL_USE_RTC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Implementation capabilities
 */
/**
 * @brief   Callback support int the driver.
 */
#define RTC_SUPPORTS_CALLBACKS      PLATFORM_RTC_HAS_INTERRUPTS

/**
 * @brief   Number of alarms available.
 */
#define RTC_ALARMS                  PLATFORM_RTC_NUM_ALARMS

/**
 * @brief   Presence of a local persistent storage.
 */
#define RTC_HAS_STORAGE             FALSE
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   FileStream specific methods.
 */
#define _rtc_driver_methods                                                 \
  _file_stream_methods

/**
 * @brief   Type of an RTC alarm number.
 */
typedef uint32_t rtcalarm_t;

/**
 * @brief   Type of a structure representing an RTC alarm time stamp.
 */
typedef struct {
  /* End of the mandatory fields.*/
  uint32_t                  dummy;
} RTCAlarm;

#if RTC_HAS_STORAGE || defined(__DOXYGEN__)
/**
 * @extends FileStream
 *
 * @brief   @p RTCDriver virtual methods table.
 */
struct RTCDriverVMT {
  _rtc_driver_methods
};
#endif

/**
 * @brief   Structure representing an RTC driver.
 */
struct RTCDriver {
#if RTC_HAS_STORAGE || defined(__DOXYGEN__)
  /**
   * @brief Virtual Methods Table.
   */
  const struct RTCDriverVMT *vmt;
#endif
  /* End of the mandatory fields.*/
  uint32_t                  dummy;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
extern RTCDriver RTCD1;
#if RTC_HAS_STORAGE
extern struct RTCDriverVMT _rtc_lld_vmt;
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void rtc_lld_init(void);
  void rtc_lld_set_time(RTCDriver *rtcp, const RTCDateTime *timespec);
  void rtc_lld_get_time(RTCDriver *rtcp, RTCDateTime *timespec);
#if RTC_ALARMS > 0
  void rtc_lld_set_alarm(RTCDriver *rtcp,
                         rtcalarm_t alarm,
                         const RTCAlarm *alarmspec);
  void rtc_lld_get_alarm(RTCDriver *rtcp,
                         rtcalarm_t alarm,
                         RTCAlarm *alarmspec);
#endif
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_RTC */

#endif /* _RTC_LLD_H_ */

/** @} */
