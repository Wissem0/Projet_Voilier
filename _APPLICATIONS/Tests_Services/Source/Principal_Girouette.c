#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "GestionGirouette.h"

MyTimer_Struct_TypeDef Timer_Enc = {TIM2,1439,0} ; //ARR et PSC changés dans la fonction MyTimer_timer_encodeur_init
MyTimer_Struct_TypeDef Timer_moteur = {TIM3,999,1439} ; //20ms
MyTimer_Struct_TypeDef Timer_IT = {TIM1,1439,99} ; //200ms

MyGPIO_Struct_TypeDef GPIO_Girouette_A = {GPIOA,0,In_Floating}; 
MyGPIO_Struct_TypeDef GPIO_Girouette_B = {GPIOA,1,In_Floating};
MyGPIO_Struct_TypeDef GPIO_moteur = {GPIOA,7,AltOut_Ppull}; 



int main ( void )

{
int angle_alpha;
int angle_teta;
int test;

	init_girouette(&Timer_Enc , &Timer_moteur, &GPIO_Girouette_A, &GPIO_Girouette_B, &GPIO_moteur, &Timer_IT);

	do
	{
	
	//test = (TIM2->CNT)*(5/1439)+5;
	//MyTimer_PWM_Cycle(Timer_moteur.Timer,test, 2);

/*
	angle_alpha=(TIM2->CNT/4.0);
	angle_teta = 0;
	if (angle_alpha>0 || angle_alpha<45) {angle_teta = 0;}
	if (angle_alpha>45 || angle_alpha<180){
		angle_teta=(angle_alpha-45)*(90.0/135.0);
	MyTimer_PWM_Cycle(Timer_moteur.Timer,angle_teta, 2);
*/
	}	


	while (1) ;

}