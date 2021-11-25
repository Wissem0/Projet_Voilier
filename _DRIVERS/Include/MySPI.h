#ifndef MYSPI_H
#define MYSPI_H
#include "stm32f10x.h"

//Initialisation
void MySPI_Config(SPI_TypeDef *SPI) ;

//SPI Transmit
void MySPI_Transmit(SPI_TypeDef * SPI, uint8_t data);

//SPI_Receive
void MySPI_Receive(SPI_TypeDef * SPI, uint8_t data) ;

void MySPI_Enable(SPI_TypeDef * SPI);
void MySPI_Disable(SPI_TypeDef * SPI);

//Chip Select
void MySPI_CS_Enable(void);
void MySPI_CS_Disable(void);



/*
//Ecriture 
void MySPI_Write (SPI_TypeDef *SPI, char a) ;

//Lecture
char MySPI_Read (SPI_TypeDef *SPI);*/






#endif 
