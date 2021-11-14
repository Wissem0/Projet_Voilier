#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"

USART_TypeDef * UART ;
char test ;

void Callback() {
	test = MyUART_Receive(UART);
}

int main(void) 
{ 
	UART=USART1 ;
	
	MyUART_Init (UART, 9600) ;
	MyUART_ActiveIT (UART, 1, Callback);
	
	MyUART_Send(UART, "quelque chose");
	while(1) ;
}