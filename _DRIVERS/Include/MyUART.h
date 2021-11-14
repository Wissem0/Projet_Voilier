#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"


void MyUART_Init (USART_TypeDef * UARTStructPtr, int BdRate) ;
void MyUART_ActiveIT (USART_TypeDef * UART, char Prio, void (*IT_function) (void));
void MyUART_Send (USART_TypeDef * UART, char * test);
char MyUART_Receive (USART_TypeDef * UART) ;


#endif
