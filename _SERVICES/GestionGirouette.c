#include "MyGPIO.h"
#include "MyTimer.h"
#include "GestionGirouette.h"

	//Fonction interruption appelée chaque 20ms pour récupérer l'angle de la Girouette
	//TIM2 pour Timer encodeur et TIM3 pour Timer moteur
void Girouette_recup_angle(void){
	
	int angle_alpha=(TIM2->CNT/2.0); //on récupère ce qu'il y a dans CNT
	int angle_teta = 0;
	if (angle_alpha>0 || angle_alpha<45) {angle_teta = 0;}
	if (angle_alpha>45 || angle_alpha<180){
		angle_teta=(angle_alpha-45)*(90.0/135.0);
	}
	//Position du moteur selon l'angle
	MyTimer_PWM_Cycle(TIM3,(angle_teta*10./9.0),2);
	}


void init_girouette (MyTimer_Struct_TypeDef *Timer_encodeur, MyTimer_Struct_TypeDef *Timer_moteur,
MyGPIO_Struct_TypeDef * GPIO_Girouette,MyGPIO_Struct_TypeDef * GPIO_Moteur, MyTimer_Struct_TypeDef *Timer_interruption){
	
	MyTimer_Base_Init(Timer_encodeur,Timer_encodeur->ARR,Timer_encodeur->PSC);
	MyTimer_timer_encodeur_init(Timer_encodeur->Timer);

	//Init
	MyGPIO_Init(GPIO_Girouette);
	//On attend qu'il y ait un input au niveau du GPIO
	while(!MyGPIO_Read(GPIO_Girouette->GPIO,GPIO_Girouette->GPIO_Pin)){}
	MyTimer_Base_Start(Timer_encodeur->Timer);


	//PWM
	MyTimer_Base_Init (Timer_moteur,Timer_moteur->ARR,Timer_moteur->PSC);
	MyTimer_PWM(Timer_moteur->Timer,2);
	MyGPIO_Init(GPIO_Moteur);
	MyTimer_Base_Start(Timer_moteur->Timer);
	

	//Interruption
	MyTimer_Base_Init(Timer_interruption,Timer_interruption->ARR,Timer_interruption->PSC);
	MyTimer_Active_IT(Timer_interruption->Timer,3,Girouette_recup_angle);
	MyTimer_Base_Start(Timer_interruption->Timer);
}

