#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"
#include "MyTimer.h"
//#include "Gestion_Plateau.h"

MyTimer_Struct_TypeDef Timer_PWM = {TIM2 , 3600 , 1};
MyGPIO_Struct_TypeDef GPIO_PWM = {GPIOA , 1 , AltOut_Ppull};
MyGPIO_Struct_TypeDef GPIO_SENS = {GPIOB,5 , Out_Ppull};
USART_TypeDef * UART = USART1 ;
MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA,10,In_PullDown};


signed char valeur = 0;
float valeurf;
float vv;
void UpdateVitesse () {
	valeur = MyUART_Receive(UART) ;
	valeurf = (float)valeur ;
	vv=((valeurf/20.0)+5.0);
	if (valeurf>=0) {
		MyGPIO_Reset (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM2, (float)((valeurf/20.0)+5.0), '2') ;
	} else {
		MyGPIO_Set (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM2, (float)(((valeurf*(-1))/20.0)+5.0), '2') ;
	}
	
}
int main(void) {	

	
	//Gestion_Plateau_Init(&Timer_PWM, &GPIO_PWM,&GPIO_SENS, UART, SpeedUpdate) ;
	
	MyTimer_Base_Init (&Timer_PWM,Timer_PWM.ARR,Timer_PWM.PSC ) ;
	MyGPIO_Init (&GPIO_PWM) ;
	MyGPIO_Init (&GPIO_SENS) ;
	MyUART_Init(UART, 9600);
	MyGPIO_Init(&GPIO_USART_RX);

	MyTimer_Base_Start(Timer_PWM.Timer);
	MyTimer_PWM (Timer_PWM.Timer, 2) ;
	MyUART_ActiveIT(UART, 3 ,UpdateVitesse);
	
	
	
	do {
		
		
	} while(1) ;
}
