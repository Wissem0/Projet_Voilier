#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"


//Initialise l'ADC
void MyADC_Init ( ADC_TypeDef * ADC, int channel ) ;
//Démarre l'ADC donné
void MyADC_Start( ADC_TypeDef * ADC ) ;
//Récupère la valeur brute donnée par l'ADC
float MyADC_Read ( ADC_TypeDef * ADC);


#endif