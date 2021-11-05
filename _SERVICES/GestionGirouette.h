#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

void Girouette_recup_angle();
void init_girouette (MyTimer_Struct_TypeDef *Timer_encodeur, MyTimer_Struct_TypeDef *Timer_moteur,
MyGPIO_Struct_TypeDef * GPIO_Girouette,MyGPIO_Struct_TypeDef * GPIO_Moteur, MyTimer_Struct_TypeDef *Timer_interruption);

