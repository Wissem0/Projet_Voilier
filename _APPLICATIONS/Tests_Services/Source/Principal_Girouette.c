#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "GestionGirouette.h"

MyTimer_Struct_TypeDef Timer_Enc = {TIM2,1439,0} ; //ARR et PSC changés dans la fonction MyTimer_timer_encodeur_init
MyTimer_Struct_TypeDef Timer_Moteur = {TIM3,999,1439} ; //20ms
MyTimer_Struct_TypeDef Timer_IT = {TIM1,1439,99} ; //200ms

MyGPIO_Struct_TypeDef GPIO_Girouette_A = {GPIOA,0,In_Floating}; 
MyGPIO_Struct_TypeDef GPIO_Girouette_B = {GPIOA,1,In_Floating};
MyGPIO_Struct_TypeDef GPIO_Moteur = {GPIOA,7,AltOut_Ppull}; 



int main ( void )
{
	init_girouette(&Timer_Enc , &Timer_Moteur, &GPIO_Girouette_A, &GPIO_Girouette_B, &GPIO_Moteur, &Timer_IT);
	do
	{	
	}while (1) ;

}