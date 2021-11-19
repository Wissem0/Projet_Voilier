#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "GestionGirouette.h"

//STRUCTURES POUR BORDAGE AUTOMATIQUE
MyTimer_Struct_TypeDef Timer_Enc = {TIM2,1439,0}; 
MyTimer_Struct_TypeDef Timer_moteur = {TIM3,999,1439} ; //20ms
MyTimer_Struct_TypeDef Timer_IT = {TIM4,1439,99} ; //200ms

MyGPIO_Struct_TypeDef GPIO_Girouette_A = {GPIOA,0,In_Floating}; 
MyGPIO_Struct_TypeDef GPIO_Girouette_B = {GPIOA,1,In_Floating};
MyGPIO_Struct_TypeDef GPIO_moteur = {GPIOA,7,AltOut_Ppull}; 



int main ( void )

{

	init_girouette(&Timer_Enc , &Timer_moteur, &GPIO_Girouette_A, &GPIO_Girouette_B, &GPIO_moteur, &Timer_IT);

	do
	{

	}	


	while (1) ;

}