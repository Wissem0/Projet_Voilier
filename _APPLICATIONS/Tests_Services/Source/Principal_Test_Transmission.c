#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"

MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA,10,In_PullDown};
USART_TypeDef * UART ;
char test ;

void Callback() {
	test = MyUART_Receive(UART);
}

int main(void) 
{ 
	// Interruption
	MyTimer_Base_Init(Timer_interruption,Timer_interruption->ARR,Timer_interruption->PSC);
	MyTimer_Active_IT(Timer_interruption->Timer,3,Girouette_recup_angle);
	MyTimer_Base_Start(Timer_interruption->Timer);
	



	UART=USART1 ;
	MyGPIO_Init(&GPIO_USART_RX);
	MyUART_Init (UART, 9600) ;
	MyUART_ActiveIT (UART, 1, Callback);
	MyUART_Send(UART, "quelque chose");
	
	while(1){ 
	
	}

}
