#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "Orientation.h"


MyGPIO_Struct_TypeDef sortiePWM = {GPIOA, 1, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef sortieBitSens = {GPIOC, 7, Out_Ppull} ;
MyTimer_Struct_TypeDef MonTimer;
	
void Orientation_Init(void){
	// Pin PWM (PA1)
	MyGPIO_Init(&sortiePWM);
	// Pin bit de sens (PC7)
	MyGPIO_Init(&sortieBitSens);
	
	// Initialisation du Timer 2 pour une fréquence 20kHz
	MonTimer.Timer = TIM2 ;
	MonTimer.ARR = 3599 ;
	MonTimer.PSC = 0 ;
	MyTimer_Base_Init(&MonTimer,MonTimer.ARR,MonTimer.PSC);
	
	// Initialisation de la PWM sur le channel 2 du Timer 2
	MyTimer_PWM(TIM2, 2);
	
	// Etablissement du rapport cyclique à 0%
	MyTimer_PWM_Cycle(TIM2, 1, 0);
	
	// Lancement du compteur
	MyTimer_Base_Start(TIM2);
}


