#include "MyADC.h"



void MyADC_Init ( ADC_TypeDef * ADC , int channel) 
{
	if (ADC == ADC1) {
	    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; 
	}

	
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	ADC->CR2 |= ADC_CR2_ADON;
	// Fixe le nombre de conversion à 1
	ADC->SQR1 &= ADC_SQR1_L;
	ADC->SQR3|= channel;
	ADC->CR2 |= ADC_CR2_CAL; // début de la calibration
	while ((ADC->CR2 & ADC_CR2_CAL));
}




int MyADC_Read ( ADC_TypeDef * ADC )
{
	ADC->CR2 |= ADC_CR2_ADON; 
	while(!(ADC->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
	ADC->SR &= ~ADC_SR_EOC;
	return ADC->DR & ~((0x0F) << 12); // renvoie les 12 premiers bits

}

