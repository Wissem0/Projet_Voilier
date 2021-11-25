#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MyUART.h"
#include "GestionGirouette.h"
#include "Gestion_Plateau.h"

//STRUCTURES POUR BORDAGE AUTOMATIQUE
MyTimer_Struct_TypeDef Timer_Enc = {TIM2,1439,0}; 
MyTimer_Struct_TypeDef Timer_moteur = {TIM3,999,1439} ; //20ms
MyTimer_Struct_TypeDef Timer_IT = {TIM4,1439,999} ; //20ms

MyGPIO_Struct_TypeDef GPIO_Girouette_A = {GPIOA,0,In_Floating}; 
MyGPIO_Struct_TypeDef GPIO_Girouette_B = {GPIOA,1,In_Floating};
MyGPIO_Struct_TypeDef GPIO_moteur = {GPIOA,7,AltOut_Ppull}; 

//STRUCTURES POUR ORIENTTION PLATEAU
MyGPIO_Struct_TypeDef GPIO_PWM = {GPIOB , 0 , AltOut_Ppull};
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
		MyTimer_PWM_Cycle (TIM3, (valeurf), 3) ;
	} else {
		MyGPIO_Set (GPIOB, 5) ;
		MyTimer_PWM_Cycle (TIM3, (valeur*(-1)), 3) ;
	}
	
}


int main ( void )

{
	init_girouette(&Timer_Enc , &Timer_moteur, &GPIO_Girouette_A, &GPIO_Girouette_B, &GPIO_moteur, &Timer_IT);
	Gestion_Plateau_Init(&Timer_moteur, &GPIO_PWM,&GPIO_SENS, &GPIO_RX, UART, Update_Vitesse) ;
	
	
	do
	{

	}	


	while (1) ;

}
