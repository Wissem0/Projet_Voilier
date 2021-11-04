#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"

MyTimer_Struct_TypeDef Timer_Enc = {TIM2   , 719 , 0} ; 
MyTimer_Struct_TypeDef Timer_Moteur = {TIM3   , 1439 , 999} ; //20ms
MyTimer_Struct_TypeDef Timer_IT = {TIM1   , 1439 , 99} ; //200ms

MyGPIO_Struct_TypeDef GPIO_Girouette = { GPIOA , 2 , In_PullUp}; 
MyGPIO_Struct_TypeDef GPIO_Moteur = { GPIOA , 7 , AltOut_Ppull}; 



int main ( void )
{

	init_girouette(Timer_Enc , Timer_Moteur, GPIO_Girouette, Timer_IT, GPIO_Moteur);


	do
	{
		
	}while (1) ;

}