#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"

MyUART_Struct_TypeDef U ;
char test ;

void Callback() {
	test = MyUART_Receive(U.UART);
}

int main(void) 
{ 
	U.UART=USART1 ;
	U.UART_BdRate=9600;
	
	MyUART_Init (&U) ;
	MyUART_ActiveIT (U.UART, 1, Callback);
	
	MyUART_Send(U.UART, "quelque chose");
	while(1) ;
}
