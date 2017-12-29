// main.c

#include "main.h"

NVIC_InitTypeDef NVIC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

SysVerType SysVer = {
    100, //u16 main;
    0, //u16 sub;
    2017, //u16 year;
    10, //u16 mon;
    27, //u16 date;
};

StatusType Status = {
    STATE_STANDBY, // u8 state;
    0, // u8 secFlag;
    0, // u8 dsecFlag;
    0, // u8 csecFlag;
    0, // u8 msecFlag;

    0, // u32 secCount;
    0, // u32 dsecCount;
    0, // u32 csecCount;
    0, // u32 msecCount;
    
    0, // u32 buzzerCount;
    0, // u32 beepCount;
    0, // u32 piBipCount;
	
	0, // u8 monitor;

    0, // u32 time;
    0, // u32 standbyTime;
    0, // u32 remTime;

    0, // u32 errorCode;
};

SettingType Setting = {
    0, //u8 empty;
};

char s[256];

int main(void)
{
    int i;

    
    Sys_Config();
    printf("***** Bead-type Sample Prep Rev. %03d.%02d *****\r\n", SysVer.main, SysVer.sub);
	printf(">> %04d. %02d. %02d. \r\n", SysVer.year, SysVer.mon, SysVer.date);

    Delay_mSec(500);
    
    while(1)
    {
        if( Status.msecFlag )
        {
            Status.msecFlag = 0;
            msecFunction();
        }
        if( Status.csecFlag )
        {
            Status.csecFlag = 0;
            csecFunction();
        }
        if( Status.dsecFlag )
        {
            Status.dsecFlag = 0;
            dsecFunction();
        }
        if( Status.secFlag )
        {
            Status.secFlag = 0;
            secFunction();
        }
    }
		
		return 0;
}

void secFunction(void)
{
    MLED2(!(Status.time % 2));
}

void dsecFunction(void)
{
    
}
void csecFunction(void)
{
    
}

void msecFunction(void)
{
    
}

void Sys_Config(void)
{
    NVIC_Config();
    SysTimer_Config();

    Comm_Config();
    Buzzer_Config();
    LEDKey_Config();
}

void NVIC_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    NVIC_InitStructure.NVIC_IRQChannel = (u8)SysTick_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 16;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 16;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
