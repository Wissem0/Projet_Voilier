#include "ADXL.h"
#include "MySPI.h"
#include "MyGPIO.h"



void ADXLWrite(SPI_TypeDef *SPI, uint8_t registre, uint8_t value) {
	MySPI_CS_Enable(); //Pull the CS low
	MySPI_Transmit(SPI,registre); //Write data to register
	MySPI_Transmit(SPI,value);
	MySPI_CS_Disable();
}

void ADXLRead(SPI_TypeDef *SPI, uint8_t registre, uint8_t data) {
	MySPI_CS_Enable(); //pull the pin low
	MySPI_Transmit(SPI, registre); //send address
	MySPI_Receive (SPI,data); //Receive 6 byte data
	MySPI_CS_Disable(); //pull the pin high
}

void ADXLInit (SPI_TypeDef *SPI) {
	ADXLWrite(SPI,0x31, 0x01); //Clearing the SPI bit in the DATA_FORMAT
	ADXLWrite(SPI,0x2d, 0x00); //reset all bits 
	ADXLWrite(SPI,0x2d, 0x08); //power_ctl measure and wake up 8hz
}
	

