#ifndef GESTION_PLATEAU_H
#define GESTION_PLATEAU_H
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyUART.h"

void Gestion_Plateau_Init(MyTimer_Struct_TypeDef * Timer_PWM, MyGPIO_Struct_TypeDef* GPIO_PWM,
MyGPIO_Struct_TypeDef* GPIO_SENS, USART_TypeDef * UART, void (*IT_function) (void)) ;


#endif
