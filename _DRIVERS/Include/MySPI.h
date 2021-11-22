#ifndef MYSPI_H
#define MYSPI_H
#include "stm32f10x.h"

//Initialisation
void MySPI_Init (SPI_TypeDef *SPI) ;
void MySPI_ActiveIT(SPI_TypeDef * SPI, void (*IT_function) (void));

//Ecriture 
void MySPI_Write (SPI_TypeDef *SPI, char a) ;

//Lecture
char MySPI_Read (SPI_TypeDef *SPI);

//char MySPI_ReadWrite(SPI_TypeDef * SPI, char data) ;
#endif 