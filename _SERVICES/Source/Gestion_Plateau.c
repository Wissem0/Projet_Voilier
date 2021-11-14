#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "Gestion_Plateau.h"
#include "MyUART.h"


	
void Gestion_Plateau_Init(MyTimer_Struct_TypeDef * Timer_PWM, MyGPIO_Struct_TypeDef* GPIO_PWM,
MyGPIO_Struct_TypeDef* GPIO_SENS, USART_TypeDef * UART, void (*IT_function) (void)){

	MyTimer_Base_Init (Timer_PWM,Timer_PWM->ARR,Timer_PWM->PSC );
	MyGPIO_Init (GPIO_PWM) ;
	MyGPIO_Init (GPIO_SENS) ;
	MyUART_Init(UART, 9600);
	MyTimer_PWM (Timer_PWM->Timer, 1) ;
	MyUART_ActiveIT(UART, 3 ,IT_function);

}





