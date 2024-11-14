//Maximilien Piron-Palliser
//Yanis Baouche

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"



int main(void) {
    //Déclaration de deux listes d'animaux
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int energie=10;

    srand(time(NULL));

    // Création de 4 proies
    Animal *a1 = creer_animal(0,10, energie);
    Animal *a2 = creer_animal(15,35, energie);
    Animal *a3 = creer_animal(2,42, energie);
    Animal *a4 = creer_animal(18,13, energie);

    // Création de la liste chaînée de proies
    a1->suivant=a2;
    a2->suivant=a3;
    a3->suivant=a4;
    a4->suivant=NULL;

    // Initialisation de la liste de proies
    liste_proie=a1;

    //Création de 4 prédateurs
    Animal *a5 = creer_animal(2,5, energie);
    Animal *a6 = creer_animal(15,35, energie);
    Animal *a7 = creer_animal(9,22, energie);
    Animal *a8 = creer_animal(17,3, energie);

    // Création de la liste chaînée de prédateurs
    a5->suivant=a6;
    a6->suivant=a7;
    a7->suivant=a8;
    a8->suivant=NULL;

    // Initialisation de la liste de prédateurs
    liste_predateur=a5;

    // Affichage de l'écosystème puis libération des listes
    afficher_ecosys(liste_proie,liste_predateur);  
    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);

    return 0;
}
