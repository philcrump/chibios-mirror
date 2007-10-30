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

#include <ch.h>

#include "lpc214x.h"
#include "lpc214x_ssp.h"

static BYTE8 *ip, *op;
static t_size icnt, ocnt;
static t_sspnotify callback;

void SSPIrq(void) {
}

/*
 * Starts an asynchronous SSP transfer.
 * @param in pointer to the incoming data buffer, if this parameter is set to
 *           \p NULL then the incoming data is discarded.
 * @param out pointer to the outgoing data buffer, if this parameter is set to
 *           \p NULL then 0xFF bytes will be output.
 * @param n the number of bytes to be transferred
 * @param fn callback function invoked when the operation is done
 * @return \p SSP_OK if the trasfer is started else \p SSP_RUNNING if a
 *         an operation was already started
 */
t_msg sspRWI(BYTE8 *in, BYTE8 *out, t_size n, t_sspnotify fn) {

  if (callback)
    return SSP_RUNNING;

  callback = fn, ip = in, op = out, icnt = ocnt = n;
  SSPIMSC = IMSC_ROR | IMSC_RT | IMSC_RX | IMSC_TX;
  return SSP_OK;
}

/*
 * SSP setup, must be invoked with interrupts disabled.
 * Do not invoke while an operation is in progress.
 */
void SetSSPI(int cpsr, int cr0, int cr1) {
  SSP *ssp = SSPBase;

  ssp->SSP_CR1 = cr1 & ~CR1_SSE;
  ssp->SSP_CR0 = cr0;
  ssp->SSP_CPSR = cpsr;
  ssp->SSP_CR1 = cr1 | CR1_SSE;
}

/*
 * SSP subsystem initialization.
 */
void InitSSP(void) {

  /* Enables the SPI1 clock */
  PCONP = (PCONP & PCALL) | PCSPI1;

  /* Clock = PCLK / 2 */
  SetSSPI(2, CR0_DSS8BIT | CR0_FRFSPI | CR0_CLOCKRATE(0), 0);

  VICIntEnable = INTMASK(SOURCE_SPI1);
}
