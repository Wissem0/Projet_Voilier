#include "stm32f10x.h"
#include "MyTimer.h"


void (* IT_function_TIM1) (void) ; 
void (* IT_function_TIM2) (void) ; 
void (* IT_function_TIM3) (void) ; 
void (* IT_function_TIM4) (void) ; 

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer, int ARR, int PSC) {
	

	if (Timer ->Timer == TIM1 ) {
		RCC-> APB2ENR |= 0x01 << 11 ;
	} else if (Timer ->Timer == TIM2) {
		RCC-> APB1ENR |= 0x01 ;
	} else if (Timer ->Timer == TIM3) {
		RCC-> APB1ENR |= 0x01 << 1;
	} else if (Timer ->Timer == TIM4) {
		RCC-> APB1ENR |= 0x01 << 2;}	
	Timer->PSC = PSC;
	Timer->ARR = ARR;
}

void Activate_TIM(int i) {
	if (i==1) {
		//le timer1 est sur apb2enr
		RCC-> APB2ENR |= 0x01 << 11 ;
	}
	else {
		//les autres timers sont sur apb1enr
		RCC-> APB1ENR |= 0x01 << (i-2) ;
	}
}

void MyTimer_Active_IT ( TIM_TypeDef * Timer , char Prio, void (*IT_function)(void) ) {
	//active l'interruption sur timer avec la priorité prio
	
	Timer -> DIER |= 1;
	
	if (Timer == TIM1) {
		NVIC_EnableIRQ(TIM1_TRG_COM_IRQn);
		NVIC_SetPriority(TIM1_TRG_COM_IRQn, Prio);
		IT_function_TIM1 = IT_function ;
	}
	if (Timer == TIM2) {
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
		IT_function_TIM2 = IT_function;

	}
	else if (Timer == TIM3) {
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		IT_function_TIM3 = IT_function;

	}
	else if (Timer == TIM4) {
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		IT_function_TIM4 = IT_function;

	}
}


void TIM1_IRQHandler(void) {
	//on met à 0 le flag d'interruption
	TIM1->SR &= ~1;
	if (IT_function_TIM1)
	(* IT_function_TIM1) ();
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~1;
	(* IT_function_TIM2) ();
}

void TIM3_IRQHandler(void) {
	TIM3->SR &= ~1;
	(* IT_function_TIM3) ();
}

void TIM4_IRQHandler(void) {
	TIM4->SR &= ~1;
	(* IT_function_TIM4) ();
}


void MyTimer_PWM(TIM_TypeDef * Timer, char Channel) {
	if (Timer == TIM1) {
		TIM1 -> BDTR |= 1 << 15 ;
	}
	switch (Channel) {
		case 1 : 
			//On choisit le mode 1 
			//on écrit donc '110' dans le registre OC1M de TIM1_CCMR1
			Timer->CCMR1 &= ~TIM_CCMR1_OC1M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1M_2;
			//On autorise le registre de preload correspondant en écrivant 1 dans OC1PE
			Timer->CCMR1 |= TIM_CCMR1_OC1PE ;
			//On autorise la sortie OCx en mettant à 1 le registre CCxE
			Timer->CCER |= TIM_CCER_CC1E;        
			break ;
		case 2 : 
			Timer->CCMR1 &= ~TIM_CCMR1_OC2M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_1| TIM_CCMR1_OC2M_2;
			Timer->CCMR1 |= TIM_CCMR1_OC2PE ;
			Timer->CCER |= TIM_CCER_CC2E;
			break ;
		case 3 : 
			Timer->CCMR2 &= ~TIM_CCMR2_OC3M_0;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_1| TIM_CCMR2_OC3M_2;
			Timer->CCMR2 |= TIM_CCMR2_OC3PE ;
			Timer->CCER |= TIM_CCER_CC3E;
			break ;
		case 4 : 
			Timer->CCMR2 &= ~TIM_CCMR2_OC4M_0;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_1| TIM_CCMR2_OC4M_2;			
			Timer->CCMR2 |= TIM_CCMR2_OC4PE ;
			Timer->CCER |= TIM_CCER_CC4E;
			break ;
	}
	//on autorise le registre de auto-reload preload en ?crivant 1 dans le registre ARPE de CR1
	Timer -> CR1 |= TIM_CR1_ARPE ;
}

void MyTimer_PWM_Cycle(TIM_TypeDef * Timer, float percent, char channel)  {
	switch (channel) {
		case 1 : 
			Timer->CCR1 = (int) ((float)(Timer -> ARR) * (percent/100.0)) ;		
			break ;
		case 2 : 
			Timer->CCR2 = (int) ((float)(Timer -> ARR) * (percent/100.0)) ;	
			break ;
		case 3 : 
			Timer->CCR3 = (int) ((float)(Timer -> ARR) * (percent/100.0)) ;	
			break ;
		case 4 : 
			Timer->CCR4 = (int) ((float)(Timer -> ARR) * (percent/100.0)) ;	
			break ;
	}
}


void Mytimer_codeur_recup_angle(MyTimer_Struct_TypeDef * timer){
    //La configuration du timer du codeur nécessite le renseignement du ARR et PSC
    //Le codeur compte 360 degrés * 2 car il compte deux tours
    //On prend donc un ARR de 720
    MyTimer_Base_Init(timer,719,0);
    timer->Timer->SMCR&= TIM_SMCR_SMS;
    timer->Timer->SMCR|=TIM_SMCR_SMS_0;


}



// 
