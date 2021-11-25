#ifndef ADXL_H
#define ADXL_H
#include "stm32f10x.h"

//Initialisation de l'ADXL
void ADXLInit(SPI_TypeDef *SPI);

//Fonction Write de l'ADXL
void ADXLWrite(SPI_TypeDef *SPI, uint8_t registre, uint8_t data) ;

//Fonction read de l'ADXL
void ADXLRead(SPI_TypeDef *SPI, uint8_t registre, uint8_t data);

//Fonction Read de l'ADXL
#endif
