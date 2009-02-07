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
 * @file chdebug.c
 * @brief ChibiOS/RT Debug code.
 * @addtogroup CondVars
 * @{
 */

#include <ch.h>

#if CH_USE_DEBUG

char *panicmsg;

/**
 * @brief Debug subsystem initialization.
 */
void debug_init(void) {

#if CH_USE_TRACE
  dbgtb.tb_size = TRACE_BUFFER_SIZE;
  dbgtb.tb_ptr = &dbgtb.tb_buffer[0];
#endif
}

/**
 * @brief Prints a panic message on the console/debugger and then halts the
 * system.
 *
 * @param msg the pointer to the message string
 */
void chDbgPanic(char *msg) {

  panicmsg = msg;
  chSysPuts("PANIC: ");
  chSysPuts(msg);
  chSysHalt();
}

#if CH_USE_TRACE
/**
 * @brief Public trace buffer.
 */
TraceBuffer dbgtb;

/**
 * @brief Inserts in the circular debug trace buffer a context switch record.
 *
 * @param otp the thread being switched out
 * @param ntp the thread to be resumed
 */
void chDbgTrace(Thread *otp, Thread *ntp) {

  dbgtb.tb_ptr->cse_wtobjp = otp->p_wtobjp;
  dbgtb.tb_ptr->cse_time = chSysGetTime();
  dbgtb.tb_ptr->cse_state = otp->p_state;
  dbgtb.tb_ptr->cse_tid = (unsigned)ntp >> 4;
  if (++dbgtb.tb_ptr >= &dbgtb.tb_buffer[TRACE_BUFFER_SIZE])
    dbgtb.tb_ptr = &dbgtb.tb_buffer[0];
}
#endif /* CH_USE_TRACE */

#endif /* CH_USE_DEBUG */

/** @} */
