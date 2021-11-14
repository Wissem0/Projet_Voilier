#include "MyUART.h"
#include "MyGPIO.h"

//Pointeurs de l'UART
void (*ptrUART1) (void);
void (*ptrUART3) (void); 


void MyUART_Init (MyUART_Struct_TypeDef *UARTStructPtr) {
	
	//Configuration du GPIO
	MyGPIO_Struct_TypeDef gpio ;
	gpio.GPIO_Conf = AltOut_Ppull ;
	MyGPIO_Init(&gpio) ;
	
	//Configuration de l'UART
	UARTStructPtr -> UART->CR1 |= USART_CR1_UE; //USART activé
	UARTStructPtr -> UART->CR1 &= ~USART_CR1_M; //Taille de la donnée, ici 8 bits
	UARTStructPtr -> UART->CR2 &= USART_CR2_STOP; //Choix d'un seul bit de stop
	
	//Validation de l'horloge
	if (UARTStructPtr->UART == USART1) {
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //validation horloge USART1
		UARTStructPtr -> UART -> BRR |= (int) 72000000/(UARTStructPtr->UART_BdRate) ; //Fréquence d'horloge de l'USART1 = 72MHz
		
		gpio.GPIO = GPIOA ;
		gpio.GPIO_Pin = 9 ;
		
	}else if (UARTStructPtr->UART == USART3) {
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //validation horloge USART3
		UARTStructPtr -> UART -> BRR |= (int) 36000000/(UARTStructPtr->UART_BdRate) ; //Fréquence d'horloge de l'USART3 = 32MHZ
		
		gpio.GPIO = GPIOC ;
		gpio.GPIO_Pin = 10 ;
	}
	
	UARTStructPtr -> UART->CR1 |= USART_CR1_TE; //Enable transmitter
	UARTStructPtr -> UART->CR1 |= USART_CR1_RE; //Enable receiver
	
}

void MyUART_ActiveIT (USART_TypeDef * UART, char Prio, void (*IT_function) (void)) {
	
	UART->CR1 |= USART_CR1_RXNEIE ; //Envoie d'une demande d'interruption validée
	
	if (UART == USART1) {
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(USART1_IRQn, Prio);
		ptrUART1 = IT_function;
	}else if (UART == USART3) {
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, Prio);
		ptrUART3 = IT_function;
	}
}

void USART1_IRQHandler (void) {
	if (ptrUART1 != 0) (*ptrUART1) () ;
}
void USART3_IRQHandler (void) {
	if (ptrUART3 != 0) (*ptrUART3) () ;
}

void MyUART_Send (USART_TypeDef * UART,char * test) {
	while (*test != '\0') {
		while(!(UART->SR & USART_SR_TXE)); 
		UART->DR = *test; // Ecriture de la donnée dans le registre DR
		test++;
	}
}

char MyUART_Receive (USART_TypeDef * UART) {
	return (signed char) UART->DR ;
}
