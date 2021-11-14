#include "MyGPIO.h"
#include "MyTimer.h"
#include "GestionGirouette.h"

	//Fonction interruption appelée chaque 20ms pour récupérer l'angle de la Girouette
	//TIM2 pour Timer encodeur et TIM3 pour Timer moteur
void Girouette_recup_angle(void){
	
	int angle_alpha=(TIM2->CNT/4.0); //on récupère ce qu'il y a dans CNT
	int angle_teta = 0;
	if (angle_alpha>0 || angle_alpha<45) {angle_teta = 0;}
	if (angle_alpha>45 || angle_alpha<180){
		angle_teta=(angle_alpha-45)*(90.0/135.0);
	}
	//Position du moteur selon l'angle
	MyTimer_PWM_Cycle(TIM3,(angle_teta*10./9.0),2);
	}


void init_girouette (MyTimer_Struct_TypeDef *Timer_encodeur, MyTimer_Struct_TypeDef *Timer_moteur,
MyGPIO_Struct_TypeDef * GPIO_Girouette_A, MyGPIO_Struct_TypeDef * GPIO_Girouette_B, MyGPIO_Struct_TypeDef * GPIO_Moteur,
MyTimer_Struct_TypeDef *Timer_interruption){
	
	//init + config Timer_encodeur en mode encoder 
	MyTimer_Base_Init(Timer_encodeur,Timer_encodeur->ARR,Timer_encodeur->PSC);
	MyTimer_timer_encodeur_init(Timer_encodeur->Timer);
	MyTimer_Base_Start(Timer_encodeur->Timer);

	//init Timer_moteur
	MyTimer_Base_Init (Timer_moteur,Timer_moteur->ARR,Timer_moteur->PSC);
	MyTimer_Base_Start(Timer_moteur->Timer);

	//Init GPIOs encodeur + moteur
	MyGPIO_Init(GPIO_Girouette_A);
	MyGPIO_Init(GPIO_Girouette_B);
	MyGPIO_Init(GPIO_Moteur);

	//PWM
	MyTimer_PWM(Timer_moteur->Timer,2);

	//Interruption
	MyTimer_Base_Init(Timer_interruption,Timer_interruption->ARR,Timer_interruption->PSC);
	MyTimer_Base_Start(Timer_interruption->Timer);
	MyTimer_Active_IT(Timer_interruption->Timer,3,Girouette_recup_angle);

}

