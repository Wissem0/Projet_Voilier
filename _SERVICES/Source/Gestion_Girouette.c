#include "MyGPIO.h"
#include "MyTimer.h"
#include "GestionGirouette.h"
int test;
float alpha;
float result;
float percent;
float test2;

	//Fonction interruption appelée chaque 20ms pour récupérer l'angle de la Girouette
	//TIM2 pour Timer encodeur et TIM3 pour Timer moteur

void Girouette_recup_angle(void){
	
	
	alpha = (TIM2->CNT)/4.;
	if (alpha<45 && alpha>0){
}
	else if (alpha < 45.0 || alpha > 315){
		percent = 0.0;
	}
	else if (alpha <= 180){
		result = (90.0/135.0)*(alpha-45.0);
	}
	else
	{
		result = (90.0/135.0)*(315-alpha);
	}
	percent = (1.0/18.0)*result+5.0;
	MyTimer_PWM_Cycle(TIM3,percent, 2);
	/*
	test = (TIM2->CNT);
	test2=(float)test*(5.0/1439.0)+5.0;
	MyTimer_PWM_Cycle(TIM3,pourcentage_PWM, 2);
	*/
	
	//Position du moteur selon l'angle
}


void init_girouette (MyTimer_Struct_TypeDef *Timer_encodeur, MyTimer_Struct_TypeDef *Timer_moteur,
MyGPIO_Struct_TypeDef * GPIO_Girouette_A, MyGPIO_Struct_TypeDef * GPIO_Girouette_B, MyGPIO_Struct_TypeDef * GPIO_Moteur,
MyTimer_Struct_TypeDef *Timer_interruption){
	//config Timer en mode encoder 
	MyTimer_Base_Init(Timer_encodeur,Timer_encodeur->ARR,Timer_encodeur->PSC);
	MyTimer_timer_encodeur_init(Timer_encodeur->Timer);

	//Init GPIO
	MyGPIO_Init(GPIO_Girouette_A);
	MyGPIO_Init(GPIO_Girouette_B);

	MyTimer_Base_Start(Timer_encodeur->Timer);


		// Configuration de la sortie PWM
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		MyGPIO_Init(GPIO_Moteur);
		MyTimer_Base_Init(Timer_moteur,Timer_moteur->ARR,Timer_moteur->PSC);
		MyTimer_Base_Start(Timer_moteur->Timer);

	
		//PWM
		MyTimer_PWM(Timer_moteur->Timer, 2);
		MyTimer_PWM_Cycle(Timer_moteur->Timer,5, 2);
		MyTimer_PWM_Cycle(Timer_moteur->Timer,6, 2);

	/*
	do{
	test = (TIM2->CNT);
	test2=(float)test*(5.0/1439.0)+5.0;
	MyTimer_PWM_Cycle(Timer_moteur->Timer,test2, 2);
	} while(1);
	*/

	//Interruption
	MyTimer_Base_Init(Timer_interruption,Timer_interruption->ARR,Timer_interruption->PSC);
	MyTimer_Active_IT(Timer_interruption->Timer,3,Girouette_recup_angle);
	MyTimer_Base_Start(Timer_interruption->Timer);
	

	
}