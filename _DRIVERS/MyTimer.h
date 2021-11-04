#ifndef MY_TIMER
#define MY_TIMER
#include "stm32f10x.h"


typedef struct{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;


void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer, int ARR, int PSC ) ;
void MyTimer_Active_IT ( TIM_TypeDef * , char Prio, void (*IT_function)(void)) ;
void MyTimer_PWM( TIM_TypeDef * Timer, char Channel) ;
void MyTimer_PWM_Cycle(TIM_TypeDef * Timer, float percent, char channel);
void MyTimer_timer_encodeur_init(TIM_TypeDef * Timer_encodeur);

#define MyTimer_Base_Start(Timer) ( Timer->CR1 |= TIM_CR1_CEN  )
#define MyTimer_Base_Stop(Timer) ( Timer->CR1 &= (~(TIM_CR1_CEN)) )

//Fonction de configuration initiale du codeur incrémental
//Il faut configurer le timer du codeur et les GPIO associés
void Mytimer_codeur_recup_angle(MyTimer_Struct_TypeDef * timer);


#endif

