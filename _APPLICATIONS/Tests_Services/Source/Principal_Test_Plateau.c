#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"
#include "MyTimer.h"
#include "Gestion_Plateau.h"

MyTimer_Struct_TypeDef TIMER4 = {TIM4 , 3600 , 1};
MyGPIO_Struct_TypeDef BROCHE_PWM = {GPIOB , 6 , AltOut_Ppull};
MyGPIO_Struct_TypeDef PIN_SENS = {GPIOB,5 , Out_Ppull};
USART_TypeDef * UART = USART1 ;

signed char valeur = 0;
void SpeedUpdate () {
	valeur = MyUART_Receive(UART) ;
	if (valeur>=0) {
		MyGPIO_Reset (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM4, (valeur)/100.0, 1) ;
	} else {
		MyGPIO_Set (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM4, (valeur*(-1))/100.0, 1) ;
	}
	
}
int main(void) {	

	
	Gestion_Plateau_Init(&TIMER4, &BROCHE_PWM,&PIN_SENS, UART, SpeedUpdate) ;
	
	/*MyTimer_Base_Init (&TIMER4,TIMER4.ARR,TIMER4.PSC ) ;
	MyGPIO_Init (&BROCHE_PWM) ;
	MyGPIO_Init (&PIN_SENS) ;
	MyUART_Init(UART, 9600);
	MyUART_ActiveIT(UART, 3 ,SpeedUpdate);
	MyTimer_PWM (TIMER4.Timer, 1) ;*/
	
	
	do {
		
		
	} while(1) ;
}