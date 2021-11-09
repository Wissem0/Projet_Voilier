#include "MyUART.h"
#include "MyGPIO.h"


//Envoie le message 
void MyUART_Send (char String) {
	USART1->DR |= String; // Ecriture de la donnée dans le registre DR
	while(!(USART1->SR & USART_SR_TC)) {} // Attente de la fin de transmission
}


