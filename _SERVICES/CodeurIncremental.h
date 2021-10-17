#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

//Fonction qui récupère l'angle donné par le codeur incrémental
int recup_angle(TIM_TypeDef * timer);

//Fonction qui récupère la direction du mouvement de la girouette
int recup_direction(TIM_TypeDef * timer);

//Fonction de configuration initiale du codeur incrémental
//Il faut configurer le timer du codeur et les GPIO associés
void codeur_init(TIM_TypeDef * timer, GPIO_TypeDef * GPIO, int PIN);