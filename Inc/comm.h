// comm.h
#ifndef __COMM_H__
#define __COMM_H__

#include "main.h"

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#define COMM_PORT	USART2

#define TX2_GPIOA   GPIO_Pin_2
#define RX2_GPIOA   GPIO_Pin_3

void Comm_Config(void);
void Comm_Printf(const char *format, ...);
void Comm_SendChar(char data);
void Comm_PrintStr(char* str);
void Comm_PrintNum(double num, int point);
void Comm_PrintDec(s32 dec);
void Comm_PrintBit(u32 bits);
void Comm_NextLine(void);


#endif
