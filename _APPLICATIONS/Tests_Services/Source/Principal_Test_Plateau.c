#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"
#include "MyTimer.h"
#include "Gestion_Plateau.h"

MyTimer_Struct_TypeDef Timer_PWM = {TIM4 , 3600 , 1};
MyGPIO_Struct_TypeDef GPIO_PWM = {GPIOB , 6 , AltOut_Ppull};
MyGPIO_Struct_TypeDef GPIO_SENS = {GPIOB,5 , Out_Ppull};
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

	
	Gestion_Plateau_Init(&Timer_PWM, &GPIO_PWM,&GPIO_SENS, UART, SpeedUpdate) ;
	
	/*MyTimer_Base_Init (&Timer_PWM,Timer_PWM.ARR,Timer_PWM.PSC ) ;
	MyGPIO_Init (&GPIO_PWM) ;
	MyGPIO_Init (&GPIO_SENS) ;
	MyUART_Init(UART, 9600);
	MyUART_ActiveIT(UART, 3 ,SpeedUpdate);
	MyTimer_PWM (Timer_PWM.Timer, 1) ;*/
	
	
	do {
		
		
	} while(1) ;
}