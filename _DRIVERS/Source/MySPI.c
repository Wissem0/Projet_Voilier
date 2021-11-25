#include "MySPI.h"
#include "MyGPIO.h"
#include "MyUART.h"

void (*pHandler_SPI_RX1) (void) ;
void (*pHandler_SPI_RX2) (void) ;
void (*pHandler_SPI_RX3) (void) ;

<<<<<<< HEAD
//Déclaration des Pins utilisés pour la liaison SPI (page 180 Manuel)
=======
//D?claration des Pins utilis?s pour la liaison SPI (page 180 Manuel)
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9
MyGPIO_Struct_TypeDef GPIO_NSS = {GPIOA, 4, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_SCK = {GPIOA, 5, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_MISO = {GPIOA, 6, In_PullDown} ;
MyGPIO_Struct_TypeDef GPIO_MOSI = {GPIOA, 7, AltOut_Ppull} ;



<<<<<<< HEAD
void MySPI_Config (SPI_TypeDef *SPI) {
=======
void MySPI_Init (SPI_TypeDef *SPI) {
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9
	
	//Configuration du SPI en mode Master
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; //Enable SPI1 clock
	
<<<<<<< HEAD
	SPI->CR1 |= (1<<2) ; //Master Mode
	
=======
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9
	//Select the BR[2:0] bits (les bits 3, 4 et 5) to define the serial clock baud rate. Clock speed < 5 MHz
	SPI->CR1 |= (0x3>3) ;
	
	//Select the CPOL and CPHA bits to define transmission mode
	//Ici, CPHA = 1 ET CPOL = 1
	SPI->CR1 |= SPI_CR1_CPHA ;
	SPI->CR1 |= SPI_CR1_CPOL ;
	
	//Set the DFF bit to define the data frame format
<<<<<<< HEAD
	//Ici, 8 bits de transmission, on laisse donc DFF à 0
	
	//Configure the LSBFIRST bit to define the frame format
	//On laisse LSBFIRST à 0 ici car les bits de poids fort sont en premier
=======
	//Ici, 8 bits de transmission, on laisse donc DFF ? 0
	
	//Configure the LSBFIRST bit to define the frame format
	//On laisse LSBFIRST ? 0 ici car les bits de poids fort sont en premier
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9
	
	//Set the SSM and SSI bits
	SPI->CR1 |= SPI_CR1_SSM ;
	SPI->CR1 |= SPI_CR1_SSI ;
	
	//Set the MSTR and SPE bits
	SPI->CR1 |= SPI_CR1_MSTR ;
	SPI->CR1 |= SPI_CR1_SPE ;
	
	
	SPI->CR2 |= SPI_CR2_RXDMAEN ; //Enable Receiver
	SPI->CR2 |= SPI_CR2_TXDMAEN ; //Enable Transmiter 
	
<<<<<<< HEAD
	MyGPIO_Activate(4);
	MyGPIO_Activate(5);
	MyGPIO_Activate(6);
	MyGPIO_Activate(7);
=======
	//MyGPIO_Activate(4);
	//MyGPIO_Activate(5);
	//MyGPIO_Activate(6);
	//MyGPIO_Activate(7);
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9
	MyGPIO_Init(&GPIO_NSS);
	MyGPIO_Init(&GPIO_SCK);
	MyGPIO_Init(&GPIO_MISO); //Data input
	MyGPIO_Init(&GPIO_MOSI); //Data Output
} 
<<<<<<< HEAD
=======

void MySPI_ActiveIT(SPI_TypeDef * SPI, void (*IT_function) (void)){
	
	// Enable interrupt on RXNE event
	SPI->CR2 |= SPI_CR2_RXNEIE;
	
	switch((int)SPI) {
			case (int)(USART1) :
				pHandler_SPI_RX1 = IT_function ;
				NVIC_SetPriority(SPI1_IRQn, 1);
				NVIC_EnableIRQ(SPI1_IRQn);
				break;
			
			case (int)(USART2) : 
				pHandler_SPI_RX2 = IT_function ;
				NVIC_SetPriority(SPI2_IRQn, 1);
				NVIC_EnableIRQ(SPI2_IRQn);
				break;
		}
}

void SPI1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE ;
	if (pHandler_SPI_RX1 != 0){
		(*pHandler_SPI_RX1) ();
	}
}

void SPI2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE ;
	if (pHandler_SPI_RX2 != 0){
		(*pHandler_SPI_RX2) ();
	}
}
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9

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

<<<<<<< HEAD
//Chip Select
void MySPI_CS_Enable() {
	MyGPIO_Reset(GPIOA,4);
}

void MySPI_CS_Disable() {
	MyGPIO_Set(GPIOA,4);
}


=======
void MySPI_Write (SPI_TypeDef *SPI, char a) {
	SPI->DR = a ;
	while (!(SPI->SR & SPI_SR_TXE)) {} ;
}

char MySPI_Read  (SPI_TypeDef *SPI) {
	while (!(SPI->SR & SPI_SR_RXNE)) {} ;
	return SPI->DR ;
} 
>>>>>>> ba8de205f83e8c94abd9f4a81318105350897ca9




