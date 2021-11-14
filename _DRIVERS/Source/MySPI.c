#include "MySPI.h"
#include "MyUART.h"


void MySPI_configuration(SPI_TypeDef * SPI){

RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //clock enable

SPI1->CR1 &= ~(0x1 << 9); //SSM



}
