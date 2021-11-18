#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"


MyTimer_Struct_TypeDef Timer = {TIM2   ,999 ,1439} ; //frequence de 100kHz
//MyGPIO_Struct_TypeDef GPIOA5_Struct = { GPIOA , 5 , Out_Ppull}; //Led
MyGPIO_Struct_TypeDef GPIOA1_Struct = { GPIOA , 1 , AltOut_Ppull}; //PWM


/*
void handler(void) {
	MyGPIO_Toggle(GPIOA5_Struct.GPIO, GPIOA5_Struct.GPIO_Pin);
}
*/

int main ( void )
{
	
	
	// Configuration de la sortie PWM
	MyGPIO_Init(&GPIOA1_Struct);
	MyTimer_Base_Init(&Timer,Timer.ARR,Timer.PSC);
	MyTimer_Base_Start(Timer.Timer);

	
	//PWM
	MyTimer_PWM(Timer.Timer, 2);
	MyTimer_PWM_Cycle(Timer.Timer,5, 2);
	


	do
	{
		
	}while (1) ;

}