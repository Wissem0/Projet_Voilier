#include "MyADC.h"



void MyADC_Init ( ADC_TypeDef * ADC , int channel) 
{
	if (ADC == ADC1) {
	      	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			
	} else if (ADC == ADC2) {
		//RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}

	// Division de la frequence
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

	// Fixe le nombre de conversion � 1
	ADC->SQR1 &= ADC_SQR1_L;
	ADC->SQR3|= channel;
	ADC->CR2 |= ADC_CR2_CAL; // d�but de la calibration
	while ((ADC->CR2 & ADC_CR2_CAL));
}







void MyADC_Start( ADC_TypeDef * ADC ) 
{
	ADC->CR2 |= ADC_CR2_ADON; // lancement de la conversion
}

int MyADC_Convert ( ADC_TypeDef * ADC )
{
	ADC1->CR2 |= ADC_CR2_ADON; 
	while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
	ADC1->SR &= ~ADC_SR_EOC;
	return ADC1->DR & ~((0x0F) << 12); 

}

