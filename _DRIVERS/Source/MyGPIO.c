#include "MyGPIO.h" 


/*void MyGPIO_Activate(int nb_GPIO) {
	//activer la clock du GPIO donné
	RCC->APB2ENR |= (0x01 << (nb_GPIO +1)) ;
}*/

void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr) {
	//màj crl si on veut un pull up ou pull down
	//on reset la conf

/*	if ( GPIOStructPtr->GPIO == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if ( GPIOStructPtr->GPIO == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if ( GPIOStructPtr->GPIO == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else if ( GPIOStructPtr->GPIO == GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
*/

	if(GPIOStructPtr->GPIO_Pin > 7){
		GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin*4) - (8*4)));
		
		//on met la bonne conf
		if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
			//on est en pull up -> on met à 1 par d?faut
			GPIOStructPtr->GPIO->CRH |= (In_PullDown << ((GPIOStructPtr->GPIO_Pin*4) - (8*4)));
			MyGPIO_Set(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
		}
		else {
			GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin*4) - (8*4)));
		}		
	}
	else {
		GPIOStructPtr->GPIO->CRL &= ~(0xF << (GPIOStructPtr->GPIO_Pin*4));
		
		//on met la bonne conf
		if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
			//on est en pull up -> on met à 1 par d?faut
			GPIOStructPtr->GPIO->CRL |= (In_PullDown << (GPIOStructPtr->GPIO_Pin*4));
			MyGPIO_Set(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
		}
		else {
			GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4));
		}
	}
	
}


int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	return (GPIO->IDR & (1 << GPIO_Pin)) ;
}

void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->BSRR = (1 << GPIO_Pin) ;
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO->BSRR = (1 << (GPIO_Pin + 16)) ;
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin){
	if (GPIO->ODR & (1 << GPIO_Pin)) {
		MyGPIO_Reset(GPIO, GPIO_Pin);
	}
	else {
		MyGPIO_Set(GPIO, GPIO_Pin);
	}
}
