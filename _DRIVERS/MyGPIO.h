#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct {
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ;
	char GPIO_Conf ;
} MyGPIO_Struct_TypeDef ;

#define In_Floating 0x4
#define In_PullDown 0x8
#define In_PullUp 0x9 // on le définit nous même 
#define In_Analog 0x0
#define Out_Ppull 0x2
#define Out_OD 0x6
#define AltOut_Ppull 0xA
#define AltOut_OD 0xE

void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr); 
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) ; //renvoie 0 ou autre chose différent de 0
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Activate(int nb_GPIO);

#endif
