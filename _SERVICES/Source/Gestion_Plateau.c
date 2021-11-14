#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "Gestion_Plateau.h"
#include "MyUART.h"


/*MyGPIO_Struct_TypeDef sortiePWM = {GPIOA, 1, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef sortieBitSens = {GPIOC, 7, Out_Ppull} ;
MyTimer_Struct_TypeDef MonTimer;*/
	
void Gestion_Plateau_Init(MyTimer_Struct_TypeDef * Timer_PWM, MyGPIO_Struct_TypeDef* BROCHE_PWM,
MyGPIO_Struct_TypeDef* PIN_SENS, USART_TypeDef * UART, void (*IT_function) (void)){

	MyTimer_Base_Init (Timer_PWM,Timer_PWM->ARR,Timer_PWM->PSC ) ;
	MyGPIO_Init (BROCHE_PWM) ;
	MyGPIO_Init (PIN_SENS) ;
	MyUART_Init(UART, 9600);
	MyUART_ActiveIT(UART, 3 ,IT_function);
	MyTimer_PWM (Timer_PWM->Timer, 1) ;
	

}





