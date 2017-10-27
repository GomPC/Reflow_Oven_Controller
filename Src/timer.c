// timer.c
#include "main.h"

u32 tic = 0;

void SysTimer_Config(void)
{
    SysTick_Config( SystemCoreClock / SYSTIMER_FREQ );

    // Tick TIM
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFF; // 2kHz / 2 = 1kHz
    TIM_TimeBaseStructure.TIM_Prescaler = 71; // 72MHz / 72 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM7, ENABLE);
}

void SysTick_Handler(void)
{
    static u32 count = 0;
    const int div_1Hz = SYSTIMER_FREQ;
    const int div_10Hz = SYSTIMER_FREQ/10;
    const int div_100Hz = SYSTIMER_FREQ/100;
    const int div_1kHz = SYSTIMER_FREQ/1000;

    count++;
    if( count >= SYSTIMER_FREQ ) count = 0;
    
    if( !(count % div_1kHz) )
    {
        Status.msecFlag = 1;
        if( Status.msecCount ) Status.msecCount--;
    }

    if( !(count % div_100Hz) )
    {
        static int piBipCount = 0;

        Status.csecFlag = 1;
        if( Status.csecCount ) Status.csecCount--;

        if( Status.buzzerCount ) Status.buzzerCount--;
        else BUZZER(0);

        if( Status.piBipCount )
        {
            if( piBipCount ) piBipCount--;
            else
            {
                piBipCount = 10;
                Status.piBipCount--;
                BuzzerOn(5);
            }
        }
    }

    if( !(count % div_10Hz) )
    {
        Status.dsecFlag = 1;
        if( Status.dsecCount ) Status.dsecCount--;
    }

    if( !(count % div_1Hz) )
    {
        Status.secFlag = 1;
        if( Status.secCount ) Status.secCount--;

        if( Status.beepCount )
        {
            Status.beepCount--;
            BuzzerOn(60);
        }

        Status.time++;
        MLED1(Status.time % 2);
    }
}

void Delay_Sec(u32 sec)
{
    Status.secCount = sec;
    while(Status.secCount);
}

void Delay_dSec(u32 dsec)
{
    Status.dsecCount = dsec;
    while(Status.dsecCount);
}

void Delay_cSec(u32 csec)
{
    Status.csecCount = csec;
    while(Status.csecCount);
}

void Delay_mSec(u32 msec)
{
    Status.msecCount = msec;
    while(Status.msecCount);
}
