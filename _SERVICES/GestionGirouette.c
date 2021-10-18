#include "MyGPIO.h"
#include "MyTimer.h"
#include "GestionGirouette.h"

//Fonction qui récupère l'angle donné par le codeur incrémental
int Girouette_recup_angle(TIM_TypeDef * timer){
	int angle_alpha=timer->CNT; //on récupère ce qu'il y a dans CNT
	if (angle_alpha>180) angle_alpha=angle_alpha-180;
	int angle_teta = 0;
	if (angle_alpha > 45){
		angle_teta = (float)(angle_alpha-30.0)/90*(2.0/3.0); //formule à revoir
	}
//On donne la main à un autre timer

}

void Girouette_init_girouette(MyTimer_Struct_TypeDef * timer_encodeur,GPIO_TypeDef * GPIO){
MyTimer_Base_Init(timer_encodeur, 719, 0);
Mytimer_codeur_recup_angle(timer_encodeur); //configure le timer de l'encodeur

while (GPIO->IDR==0){ //s'il n'y a rien on ne compte rien
timer_encodeur->Timer->CNT=0;
}
}

int Girouette_recup_direction(TIM_TypeDef * timer){

};

