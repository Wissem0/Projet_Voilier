#include "MyGPIO.h"
#include "MyTimer.h"
#include "CodeurIncremental.h"

//Fonction qui récupère l'angle donné par le codeur incrémental
int recup_angle(TIM_TypeDef * timer){
}

void codeur_init(TIM_TypeDef * timer, GPIO_TypeDef * GPIO, int PIN){
    //La configuration du timer du codeur nécessite le renseignement du ARR et PSC
    //Le codeur compte 360 degrés * 2 car il compte deux tours
    //On prend donc un ARR de 720
    

}