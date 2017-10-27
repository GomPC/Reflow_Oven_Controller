// extio.h

#ifndef __EXTIO_H__
#define __EXTIO_H__

#define MLED1_GPIOB     GPIO_Pin_0
#define MLED2_GPIOB     GPIO_Pin_1

#define BUZZER_GPIOA    GPIO_Pin_11

#define KEY1_GPIOA      GPIO_Pin_6
#define KEY2_GPIOA      GPIO_Pin_7

#define MLED1(x)    (x ? GPIO_SetBits(GPIOB, MLED1_GPIOB):GPIO_SetBits(GPIOB, MLED1_GPIOB))
#define MLED2(x)    (x ? GPIO_SetBits(GPIOB, MLED2_GPIOB):GPIO_SetBits(GPIOB, MLED2_GPIOB))

#define KEY1_CK     (!GPIO_ReadInputDataBit(GPIOA, KEY1_GPIOA))
#define KEY2_CK     (!GPIO_ReadInputDataBit(GPIOA, KEY2_GPIOA))

#define BUZZER(x)   (x ? GPIO_SetBits(GPIOA, BUZZER_GPIOA):GPIO_ResetBits(GPIOA, BUZZER_GPIOA))

void LEDKey_Config(void);
void Buzzer_Config(void);
u8 Key_Read(void);
void BuzzerOn(u8 count);

#endif
