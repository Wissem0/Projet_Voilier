#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyUART.h"
#include "GestionGirouette.h"
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

float alpha; 
int theta;
float result;
float percent;
int compteur = 0;
char allure[25];
char str2[25]; // Le string envoyé à la télécommande

//Fonction interruption appelée chaque 20ms pour récupérer l'angle de la Girouette
//TIM2 pour Timer encodeur et TIM3 pour Timer moteur

void Girouette_recup_angle(void){
	
	
	alpha = (TIM2->CNT)/4.;
	if (alpha<45 && alpha>0){
		theta = 0;
	}
	else if (alpha < 45.0 || alpha > 315){
		percent = 0.0;
		theta = 0;
		
		
	}
	else if (alpha <= 180){
		result = (90.0/135.0)*(alpha-45.0);
		theta = (int)((90.0/135.0)*(alpha-45.0));
	}
	else
	{
		result = (90.0/135.0)*(315-alpha);
		theta = (int)((90.0/135.0)*(315-alpha));
	}
	percent = (1.0/18.0)*result+5.0;
	MyTimer_PWM_Cycle(TIM3,percent, 2);
	
	compteur++ ;

	// Envoie de l'allure sur la telecommande
	if ((alpha >= 305.0 && alpha <= 315.0)||(alpha <= 55.0 && alpha >= 45.0)) {
		strcpy(allure , ": Pres \n");
	} 
	else if (alpha < 45.0 || alpha > 315) {
		strcpy(allure , ": Vent debout \n");
	}
	else if ((alpha >= 295.0 && alpha < 305.0)||(alpha > 55.0 && alpha <= 65.0)) {
		strcpy(allure , ": Bon Plein \n");
	}
	else if ((alpha >= 280.0 && alpha < 295.0)||(alpha > 65.0 && alpha <= 80.0)) {
		strcpy(allure , ": Petit Largue \n");
	}
	else if ((alpha >= 260.0 && alpha < 280.0)||(alpha > 80.0 && alpha <= 100.0)) {
		strcpy(allure , ": Travers \n");
	}
	else if ((alpha >= 240.0 && alpha < 260.0)||(alpha > 100.0 && alpha <= 120.0)) {
		strcpy(allure , ": Largue \n");
	}
	else if ((alpha >= 190.0 && alpha < 240.0)||(alpha > 120.0 && alpha <= 170.0)) {
		strcpy(allure , ": Grand Largue \n");
	}
	else if (alpha > 170.0 && alpha < 190.0) {
		strcpy(allure , ": Vent Arriere \n");
	}
	
	
	sprintf(str2, "%s%d%s%s","L'angle des voiles: ",theta,allure," \n");


	if (compteur >= 150) { // 20ms x 150 = 3s => on envoie l'angle et l'allure toutes les 3s.
		compteur =0 ;
		MyUART_Send(USART1, str2);
	}


	
	
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

	//Interruption
	MyTimer_Base_Init(Timer_interruption,Timer_interruption->ARR,Timer_interruption->PSC);
	MyTimer_Active_IT(Timer_interruption->Timer,3,Girouette_recup_angle);
	MyTimer_Base_Start(Timer_interruption->Timer);
	

	
}
