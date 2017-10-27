// extio.c

#include "main.h"

void LEDKey_Config(void)
{
    // MCU LED Configuration: MLED1/2: PB0/1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = MLED1_GPIOB | MLED2_GPIOB;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // KEY Configuration: KEY1/2: PA6/7
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = KEY1_GPIOA | KEY2_GPIOA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Buzzer_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = BUZZER_GPIOA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOA, BUZZER_GPIOA);
}

u8 Key_Read(void)
{
    u8 sw = 0;
    if( KEY1_CK ) sw |= 0x01;
    if( KEY2_CK ) sw |= 0x02;

    return sw;
}

void BuzzerOn(u8 count)
{
    BUZZER(1);
    Status.buzzerCount = count;
}

