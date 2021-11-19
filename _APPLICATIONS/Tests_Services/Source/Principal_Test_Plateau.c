#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUART.h"
#include "MyTimer.h"
#include "Gestion_Plateau.h"

MyTimer_Struct_TypeDef Timer_PWM = {TIM4 , 3600 , 1};
MyGPIO_Struct_TypeDef GPIO_PWM = {GPIOB , 6 , AltOut_Ppull};
MyGPIO_Struct_TypeDef GPIO_SENS = {GPIOB,5 , Out_Ppull};
MyGPIO_Struct_TypeDef GPIO_RX = {GPIOA,10,In_PullDown};
USART_TypeDef * UART = USART1 ;



signed char valeur = 0;
float valeurf;
void Update_Vitesse () {
	valeur = MyUART_Receive(UART) ;
	valeurf = (float)valeur ;
	if (valeur>=0) {
		MyGPIO_Reset (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM4, (valeurf), 1) ;
	} else {
		MyGPIO_Set (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM4, (valeur*(-1)), 1) ;
	}
	
}
int main(void) {	

	
	Gestion_Plateau_Init(&Timer_PWM, &GPIO_PWM,&GPIO_SENS, &GPIO_RX, UART, Update_Vitesse) ;
	
	
	do {
		
		
	} while(1) ;
}
