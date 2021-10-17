#include "stm32f1xx_ll_tim.h"

//Fonction qui récupère l'angle donné par le codeur incrémental
int recup_angle(TIM_TypeDef * timer){
    //Fonction qui récupère l'angle fournit par l'encodeur
    //La fonction de l'encodeur prend en paramètre le timer associé à l'encodeur
    
    return LL_TIM_GetCounter(timer)/2
}