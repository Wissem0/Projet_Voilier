#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

void Girouette_recup_angle();
void Girouette_init_girouette(MyTimer_Struct_TypeDef * timer_encodeur,GPIO_TypeDef * GPIO);

