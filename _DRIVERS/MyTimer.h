#ifndef MY_TIMER
#define MY_TIMER
#include "stm32f10x.h"



typedef struct{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;


void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) ;
void MyTimer_Active_IT ( TIM_TypeDef * , char Prio, void (*IT_function)(void)) ;
void MyTimer_PWM( TIM_TypeDef * Timer, char Channel) ;
void MyTimer_PWM_Cycle(TIM_TypeDef * Timer, float percent, char channel);


#define MyTimer_Base_Start(Timer) ( Timer->CR1 |= TIM_CR1_CEN  )
#define MyTimer_Base_Stop(Timer) ( Timer->CR1 &= (~(TIM_CR1_CEN)) )




#endif

