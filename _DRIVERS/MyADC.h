#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"

typedef struct
{
	ADC_TypeDef * ADC;
	


} MyADC_Struct_TypeDef ;

//Initialise l'ADC
void MyADC_Init ( MyADC_Struct_TypeDef * ADC ) ;
//D�marre l'ADC donn�
void MyADC_Start( MyADC_Struct_TypeDef * ADC ) ;
//R�cup�re la valeur brute donn�e par l'ADC
float MyADC_Read ( USART_TypeDef * ADC);


#endif