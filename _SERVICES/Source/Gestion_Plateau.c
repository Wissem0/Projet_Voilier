#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "Gestion_Plateau.h"
#include "MyUART.h"


	
void Gestion_Plateau_Init(MyTimer_Struct_TypeDef * Timer_PWM, MyGPIO_Struct_TypeDef* GPIO_PWM,
MyGPIO_Struct_TypeDef* GPIO_SENS,MyGPIO_Struct_TypeDef* GPIO_USART_RX, USART_TypeDef * UART, void (*IT_function) (void)){
	
	MyTimer_Base_Init (Timer_PWM,Timer_PWM->ARR,Timer_PWM->PSC );
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	MyGPIO_Init (GPIO_PWM) ;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init (GPIO_SENS) ;
	MyGPIO_Init(GPIO_USART_RX);
	MyUART_Init(UART, 9600);
	MyUART_ActiveIT(UART, 3 ,IT_function);
	MyTimer_PWM (Timer_PWM->Timer, 3) ;
	MyTimer_Base_Start(Timer_PWM->Timer);

}






