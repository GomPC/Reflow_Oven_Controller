// main.h

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "timer.h"
#include "extio.h"
#include "comm.h"

#define STATE_STANDBY   0
#define STATE_INIT      1

typedef struct __SysVerType__
{
    u16 main;
    u16 sub;
    u16 year;
    u16 mon;
    u16 date;
} SysVerType;

typedef struct __StatusType__
{
    u8 state;
    u8 secFlag;
    u8 dsecFlag;
    u8 csecFlag;
    u8 msecFlag;

    u32 secCount;
    u32 dsecCount;
    u32 csecCount;
    u32 msecCount;
    
    u32 buzzerCount;
    u32 beepCount;
    u32 piBipCount;
	
	u8 monitor;
	
    u32 time;
    u32 standbyTime;
    u32 remTime;

    u32 errorCode;
} StatusType;

typedef struct __SettingType__
{
    u8 empty;
} SettingType;

void secFunction(void);
void dsecFunction(void);
void csecFunction(void);
void msecFunction(void);

void Sys_Config(void);
void NVIC_Config(void);
void ErrorCK(void);

extern SysVerType SysVer;
extern StatusType Status;
extern SettingType Setting;

extern char s[256];

extern NVIC_InitTypeDef NVIC_InitStructure;
extern GPIO_InitTypeDef GPIO_InitStructure;
extern USART_InitTypeDef USART_InitStructure;
extern TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

#endif
