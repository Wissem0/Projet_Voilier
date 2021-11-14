#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MyADC.h"


MyTimer_Struct_TypeDef Timer3 = {TIM3   , 719 , 0} ; //frequence de 100kHz
MyGPIO_Struct_TypeDef GPIOA5_Struct = { GPIOA , 5 , Out_Ppull}; //Led
MyGPIO_Struct_TypeDef GPIOA6_Struct = { GPIOA , 6 , AltOut_Ppull}; //PWM
MyGPIO_Struct_TypeDef GPIOB0_Struct = { GPIOB , 0 , In_Analog}; //GPIO ADC

void handler(void) {
	MyGPIO_Toggle(GPIOA5_Struct.GPIO, GPIOA5_Struct.GPIO_Pin);
}


int main ( void )
{
	float res = 0 ;
	
	//RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	MyTimer_Base_Init(&Timer3,Timer3.ARR,Timer3.PSC );
	
	MyGPIO_Activate(1); //GPIOA
	MyGPIO_Init(&GPIOA5_Struct); // Diode
	
	// Configuration de la sortie PWM
	MyGPIO_Init(&GPIOA6_Struct);

	// Configuration GPIO ADC
	MyGPIO_Init(&GPIOB0_Struct);
	
	//PWM
	MyTimer_PWM(Timer3.Timer, 1);
	MyTimer_PWM_Cycle(Timer3.Timer, 0 , 1);
	
	//ADC
	MyADC_Init ( ADC1 , 8);
	
	// Demarrage PWM
	MyTimer_Base_Start(Timer3.Timer);

	while (1)
	{
		res = MyADC_Read (ADC1) ;
		MyTimer_PWM_Cycle(Timer3.Timer, 100*res / 0xFFF , 1); // la resolution de l'ADC sur 12 bits (0xFFF)
	}

}