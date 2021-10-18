#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

//Fonction qui récupère l'angle donné par le codeur incrémental
int Girouette_recup_angle(TIM_TypeDef * timer);

//Fonction qui récupère la direction du mouvement de la girouette
int Girouette_recup_direction(TIM_TypeDef * timer);

void Girouette_init_girouette(MyTimer_Struct_TypeDef * timer_encodeur,GPIO_TypeDef * GPIO);