#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "Orientation.h"


MyGPIO_Struct_TypeDef sortiePWM = {GPIOA, 1, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef sortieBitSens = {GPIOC, 7, Out_Ppull} ;
MyTimer_Struct_TypeDef MonTimer;
	
void Orientation_Init(void){
	// PWM (PA1)
	MyGPIO_Init(&sortiePWM);
	// Bit de sens (PC7)
	MyGPIO_Init(&sortieBitSens);
	
	// Initialisation du Timer 2 pour une fréquence 20kHz)
	MonTimer.Timer = TIM2 ;
	MonTimer.ARR = 3599 ;
	MonTimer.PSC = 0 ;
	MyTimer_Base_Init(&MonTimer);
	
	// Initialisation de la PWM sur le channel 1 du Timer 4
	MyTimer_PWM(TIM4, 1);
	
	// Etablissement du rapport cyclique à 0%
	MyTimer_PWM_Cycle(TIM4, 1, 0);
	
	// Lancement du compteur
	MyTimer_Base_Start(TIM4);
}

