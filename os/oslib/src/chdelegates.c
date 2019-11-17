/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    chdelegates.c
 * @brief   Delegate threads code.
 * @details Delegate threadss.
 *          <h2>Operation mode</h2>
 *          A delegate thread is a thread performing function calls triggered
 *          by other threads. This functionality is especially useful when
 *          encapsulating a library not designed for threading into a
 *          delegate thread. Other threads have access to the library without
 *          having to worry about mutual exclusion.
 * @pre     In order to use the pipes APIs the @p CH_CFG_USE_DELEGATES
 *          option must be enabled in @p chconf.h.
 * @note    Compatible with RT and NIL.
 *
 * @addtogroup oslib_delegates
 * @{
 */

#include "ch.h"

#if (CH_CFG_USE_DELEGATES == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing a delegate call.
 */
typedef struct {
  /**
   * @brief   The delegate veneer function.
   */
  delegate_veneer_t veneer;
  /**
   * @brief   Pointer to the caller @p va_list object.
   */
  va_list           *argsp;
} call_message_t;

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Veneer for functions with no parameters.
 *
 * @param[in] argsp     the list of arguments
 * @return              The function return value.
 */
msg_t __ch_delegate_fn0(va_list *argsp) {
  delegate_fn0_t fn0 = va_arg(*argsp, delegate_fn0_t);
  return fn0();
}

/**
 * @brief   Veneer for functions with one parameter.
 *
 * @param[in] argsp     the list of arguments
 * @return              The function return value.
 */
msg_t __ch_delegate_fn1(va_list *argsp) {
  delegate_fn1_t fn1 = va_arg(*argsp, delegate_fn1_t);
  msg_t p1 = va_arg(*argsp, msg_t);
  return fn1(p1);
}

/**
 * @brief   Veneer for functions with two parameters.
 *
 * @param[in] argsp     the list of arguments
 * @return              The function return value.
 */
msg_t __ch_delegate_fn2(va_list *argsp) {
  delegate_fn2_t fn2 = va_arg(*argsp, delegate_fn2_t);
  msg_t p1 = va_arg(*argsp, msg_t);
  msg_t p2 = va_arg(*argsp, msg_t);
  return fn2(p1, p2);
}

/**
 * @brief   Veneer for functions with three parameters.
 *
 * @param[in] argsp     the list of arguments
 * @return              The function return value.
 */
msg_t __ch_delegate_fn3(va_list *argsp) {
  delegate_fn3_t fn3 = va_arg(*argsp, delegate_fn3_t);
  msg_t p1 = va_arg(*argsp, msg_t);
  msg_t p2 = va_arg(*argsp, msg_t);
  msg_t p3 = va_arg(*argsp, msg_t);
  return fn3(p1, p2, p3);
}

/**
 * @brief   Veneer for functions with four parameters.
 *
 * @param[in] argsp     the list of arguments
 * @return              The function return value.
 */
msg_t __ch_delegate_fn4(va_list *argsp) {
  delegate_fn4_t fn4 = va_arg(*argsp, delegate_fn4_t);
  msg_t p1 = va_arg(*argsp, msg_t);
  msg_t p2 = va_arg(*argsp, msg_t);
  msg_t p3 = va_arg(*argsp, msg_t);
  msg_t p4 = va_arg(*argsp, msg_t);
  return fn4(p1, p2, p3, p4);
}

/**
 * @brief   Triggers a function call on a delegate thread.
 * @note    The thread must be executing @p chDelegateDispatchTimeout() in
 *          order to have the functions called.
 *
 * @param[in] tp        pointer to the delegate thread
 * @param[in] func      pointer to the function to be called
 * @param[in] argc      number of parameters
 * @param[in] ...       variable number of parameters
 * @return              The function return value casted to msg_t. It is
 *                      garbage for functions returning @p void.
 */
msg_t chDelegateCallVeneer(thread_t *tp, delegate_veneer_t veneer, ...) {
  va_list args;
  call_message_t cm;
  msg_t msg;

  va_start(args, veneer);

  /* Preparing the call message.*/
  cm.veneer = veneer;
  cm.argsp  = &args;

  /* Sending the message to the dispatcher thread, the return value is
     contained in the returned message.*/
  msg = chMsgSend(tp, (msg_t)&cm);

  va_end(args);

  return msg;
}

/**
 * @brief   Call messages dispatching.
 * @details The function awaits for an incoming call messages and calls the
 *          specified functions, then it returns. In case multiple threads
 *          are sending messages then the requests are served in priority
 *          order.
 *
 * @param[in] timeout   function timeout in system ticks
 * @
 *
 */
msg_t chDelegateDispatchTimeout(sysinterval_t timeout) {
  thread_t *tp;
  const call_message_t *cmp;
  msg_t ret;

  (void)timeout;

  tp = chMsgWait();
  cmp = (const call_message_t *)chMsgGet(tp);
  ret = cmp->veneer(cmp->argsp);

  chMsgRelease(tp, ret);

  return MSG_OK;
}

#endif /* CH_CFG_USE_DELEGATES == TRUE */

/** @} */
