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

#ifndef _CHCORE_H_
#define _CHCORE_H_

typedef void *regarm;

/*
 * Interrupt saved context, empty in this architecture.
 */
struct extctx {
};

/*
 * System saved context.
 */
struct intctx {
  regarm  r4;
  regarm  r5;
  regarm  r6;
#ifndef CH_CURRP_REGISTER_CACHE
  regarm  r7;
#endif
  regarm  r8;
  regarm  r9;
  regarm  r10;
  regarm  r11;
  regarm  lr_exc;
  regarm  r0;
  regarm  r1;
  regarm  r2;
  regarm  r3;
  regarm  r12;
  regarm  lr_thd;
  regarm  pc;
  regarm  xpsr;
};

/*
 * Port dependent part of the Thread structure, you may add fields in
 * this structure.
 */
typedef struct {
  struct intctx *r13;
} Context;

/*
 * Platform dependent part of the \p chThdCreate() API.
 */
#define SETUP_CONTEXT(workspace, wsize, pf, arg) {                      \
  tp->p_ctx.r13 = (struct intctx *)((uint8_t *)workspace +              \
                                     wsize -                            \
                                     sizeof(struct intctx));            \
  tp->p_ctx.r13->r0 = arg;                                              \
  tp->p_ctx.r13->r1 = pf;                                               \
  tp->p_ctx.r13->lr_exc = (regarm)0xFFFFFFFD;                           \
  tp->p_ctx.r13->pc = threadstart;                                      \
  tp->p_ctx.r13->xpsr = (regarm)0x01000000;                             \
}

#define chSysLock() asm("cpsid   i")
#define chSysUnlock() asm("cpsie   i")

#define INT_REQUIRED_STACK 0
#define StackAlign(n) ((((n) - 1) | 3) + 1)
#define UserStackSize(n) StackAlign(sizeof(Thread) +                    \
                                    sizeof(struct intctx) +             \
                                    sizeof(struct extctx) +             \
                                    (n) +                               \
                                    INT_REQUIRED_STACK)
#define WorkingArea(s, n) uint32_t s[UserStackSize(n) >> 2];

#define chSysIRQEnterI()

/* It should be 8.*/
#define IDLE_THREAD_STACK_SIZE 0
void _IdleThread(void *p) __attribute__((noreturn));

void chSysHalt(void);
void chSysSwitchI(Thread *otp, Thread *ntp);
void chSysPuts(char *msg);
void threadstart(void);
void chSysIRQExitI(void);

#endif /* _CHCORE_H_ */
