#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"

typedef struct
{
	ADC_TypeDef * ADC;
	


} MyADC_Struct_TypeDef ;

//Initialise l'ADC
void MyADC_Init ( MyADC_Struct_TypeDef * ADC ) ;
//Démarre l'ADC donné
void MyADC_Start( MyADC_Struct_TypeDef * ADC ) ;
//Récupère la valeur brute donnée par l'ADC
float MyADC_Read ( USART_TypeDef * ADC);


#endif