Introduction :
Le but du projet est de programmer une carte NUCLEO STM32F103RB embarquée sur une maquette de voilier afin de 
contrôler le cap du bateau et l'écoute des voiles via une télécommande.

Fonctionnalité :
Bordage automatique : pleinement fonctionnel
Orientation voilier : pleinement fonctionnel
Système anti-chavirement : Implémentation du SPI et ADXL
Transmission d'informations : pleinement fonctionnel : la communication avec la télécommande est 
bidirectionnelle, avec possibilité d'envoi de l'angle et de l'allure du bateau avec un délai de 3secondes. 
Nous n'avons pas pu développé la transmission de l'état de batterie ainsi que la date et l'heure.


Déroulement temporel du programme :
- Déclaration des variables globales
- Déclaration et configuration des structures
- Appel des fonctions Services (Gestion_Girouette (et transmission), Gestion_Plateau)


Members :
ARFA Amine
BACCAR Rostom
FERCHICHI Wissem
MAHER Ghita
NOURDINE Alae