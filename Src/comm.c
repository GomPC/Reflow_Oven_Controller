// comm.c
#include "main.h"

PUTCHAR_PROTOTYPE
{
	/* Loop until the end of transmission */
	while(USART_GetFlagStatus(COMM_PORT, USART_FLAG_TXE) == RESET);

	/* Write a character to the USART */
	USART_SendData(COMM_PORT, (u8)ch);
	
	
	return ch;
}

void Comm_Config(void)
{
	//GPIO Configuration for USART2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
											  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = RX2_GPIOA;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = TX2_GPIOA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART2 Configuration
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_Cmd(COMM_PORT, DISABLE);
	
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(COMM_PORT, &USART_InitStructure);
	
	USART_ITConfig(COMM_PORT, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(COMM_PORT, ENABLE);

	return;
}

void USART1_IRQHandler(void)
{
	static s32 unit = 100;
	static double funit = 1.0;

	if(USART_GetITStatus(COMM_PORT, USART_IT_RXNE) != RESET)
	{
		char c = USART_ReceiveData(COMM_PORT);
		
		switch( c )
		{
			case '`':
				Status.monitor = !Status.monitor;
				break;
			
			case ',':
				unit /= 10;
				if( unit < 1 && unit > -1 )
					unit = 1;
				printf(" Unit: %d\r\n", unit);
				break;
			case '.':
				unit *= 10;
				printf(" Unit: %d\r\n", unit);
				break;
			case '/':
				unit *= -1;
				printf(" Unit: %d\r\n", unit);
				break;
			
			case '<':
				funit /= 10.0L;
				printf(" Float Unit: %lf\r\n", funit);
				break;
			case '>':
				funit *= 10.0L;
				printf(" Float Unit: %lf\r\n", funit);
				break;
			case '?':
				funit *= -1.0L;
				printf(" Float Unit: %lf\r\n", funit);
				break;
			case 'p':
				printf(" Error Code: 0x%08X\r\n", Status.errorCode);
				break;
			default:
				printf(" Missing Command: %c\r\n", c);
				break;
		}
	}

	if(USART_GetITStatus(COMM_PORT, USART_IT_TXE) != RESET)
	{   
	  
	}
}

void Comm_Printf(const char *format, ...)
{
	va_list arg;
	char s[256];
	
	va_start(arg, format);
	vsprintf(s, format, arg);
	va_end(arg);
	
	Comm_PrintStr(s);
}


void Comm_SendChar(char data)
{
	while (USART_GetFlagStatus(COMM_PORT, USART_FLAG_TXE) == RESET);
	USART_SendData(COMM_PORT, data);
}

void Comm_PrintStr(char* str)
{
	char* strPtr = str;
	do{
		Comm_SendChar(*strPtr);
		strPtr++;
	} while(*strPtr != '\0');
}

void Comm_PrintNum(double num, int point)
{
	s32 numDec = 0;	

	numDec = (s32)num;
	
	Comm_PrintDec(numDec);

	num -= (double)numDec;
	if(num < 0.0) num *= -1.0;
	do
	{
		num *= 10.0;
	} while(--point);
	
	Comm_SendChar('.');

	Comm_PrintDec((s32)num);

	return;
}

void Comm_PrintDec(s32 dec)
{
	int sign = 0, digit = 0;
	s32 temp = dec;

	if(dec < 0)
	{
		dec *= -1;
		sign = -1;
	}
	
	do
	{
		temp /= 10;
		digit++;
	}while(temp);

	if(sign)
		Comm_SendChar('-');

	switch(digit)
	{
		case 10: Comm_SendChar(dec/1000000000 + '0'); dec %= 1000000000;
		case 9:	Comm_SendChar(dec/100000000 + '0'); dec %= 100000000;
		case 8:	Comm_SendChar(dec/10000000 + '0'); dec %= 10000000;
		case 7:	Comm_SendChar(dec/1000000 + '0'); dec %= 1000000;
		case 6:	Comm_SendChar(dec/100000 + '0'); dec %= 100000;
		case 5:	Comm_SendChar(dec/10000 + '0'); dec %= 10000;
		case 4:	Comm_SendChar(dec/1000 + '0'); dec %= 1000;
		case 3:	Comm_SendChar(dec/100 + '0'); dec %= 100;
		case 2:	Comm_SendChar(dec/10 + '0');
		case 1:	Comm_SendChar(dec%10 + '0');
	}

	return;
}

void Comm_PrintBit(u32 bits)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		if( (bits << i) & 0x80000000 )
			Comm_SendChar('1');
		else
			Comm_SendChar('0');

		if(!( (i+1)%4 ))
			Comm_SendChar(' ');
	}
	return;								   
}

void Comm_NextLine(void)
{
	Comm_SendChar('\r');
	Comm_SendChar('\n');
}
