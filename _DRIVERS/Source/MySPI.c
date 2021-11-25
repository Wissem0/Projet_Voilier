#include "MySPI.h"
#include "MyGPIO.h"
#include "MyUART.h"

void (*pHandler_SPI_RX1) (void) ;
void (*pHandler_SPI_RX2) (void) ;
void (*pHandler_SPI_RX3) (void) ;

//Déclaration des Pins utilisés pour la liaison SPI (page 180 Manuel)
MyGPIO_Struct_TypeDef GPIO_NSS = {GPIOA, 4, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_SCK = {GPIOA, 5, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_MISO = {GPIOA, 6, In_PullDown} ;
MyGPIO_Struct_TypeDef GPIO_MOSI = {GPIOA, 7, AltOut_Ppull} ;



void MySPI_Config (SPI_TypeDef *SPI) {
	
	//Configuration du SPI en mode Master
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; //Enable SPI1 clock
	
	SPI->CR1 |= (1<<2) ; //Master Mode
	
	//Select the BR[2:0] bits (les bits 3, 4 et 5) to define the serial clock baud rate. Clock speed < 5 MHz
	SPI->CR1 |= (0x3>3) ;
	
	//Select the CPOL and CPHA bits to define transmission mode
	//Ici, CPHA = 1 ET CPOL = 1
	SPI->CR1 |= SPI_CR1_CPHA ;
	SPI->CR1 |= SPI_CR1_CPOL ;
	
	//Set the DFF bit to define the data frame format
	//Ici, 8 bits de transmission, on laisse donc DFF à 0
	
	//Configure the LSBFIRST bit to define the frame format
	//On laisse LSBFIRST à 0 ici car les bits de poids fort sont en premier
	
	//Set the SSM and SSI bits
	SPI->CR1 |= SPI_CR1_SSM ;
	SPI->CR1 |= SPI_CR1_SSI ;
	
	//Set the MSTR and SPE bits
	SPI->CR1 |= SPI_CR1_MSTR ;
	SPI->CR1 |= SPI_CR1_SPE ;
	
	
	SPI->CR2 |= SPI_CR2_RXDMAEN ; //Enable Receiver
	SPI->CR2 |= SPI_CR2_TXDMAEN ; //Enable Transmiter 
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init(&GPIO_NSS);
	MyGPIO_Init(&GPIO_SCK);
	MyGPIO_Init(&GPIO_MISO); //Data input
	MyGPIO_Init(&GPIO_MOSI); //Data Output
} 

void MySPI_Transmit(SPI_TypeDef * SPI, uint8_t data) {
	while (!((SPI->SR)&SPI_SR_TXE)) {}; //Wait for TXE bit to set
	SPI->DR = data; //load the data into the Data Register
}

	
void MySPI_Receive(SPI_TypeDef * SPI, uint8_t data) {
	while(!((SPI->SR)&SPI_SR_RXNE)) {}; //Wait for RXNE to set
	data = SPI->DR;
}


void MySPI_Enable(SPI_TypeDef * SPI) {
	SPI->CR1 |= (1<<6) ;; //SPE=1, Peripheral Enabled
}

void MySPI_Disable(SPI_TypeDef * SPI) {
	SPI->CR1 &= ~(1<<6);
}

//Chip Select
void MySPI_CS_Enable() {
	MyGPIO_Reset(GPIOA,4);
}

void MySPI_CS_Disable() {
	MyGPIO_Set(GPIOA,4);
}






