// timer.h

#ifndef __TIMER_H__
#define __TIMER_H__

#define SYSTIMER_FREQ   (2000)

void SysTimer_Config(void);

void Delay_Sec(u32 sec);
void Delay_dSec(u32 dsec);
void Delay_cSec(u32 csec);
void Delay_mSec(u32 msec);

extern u32 tic;

#endif
