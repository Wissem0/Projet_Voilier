#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"

typedef struct
{
	USART_TypeDef * UART ;
	int UART_BPS ; 

} MyUART_Struct_TypeDef ;


//Configure l'UART
void MyUART_Init ( MyUART_Struct_TypeDef * UART ) ;
//Envoie le message 
void MyUART_Send ( USART_TypeDef * UART, char* String);



#endif
