//Maximilien Piron-Palliser
//Yanis Baouche

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ecosys.h"

int main(){

    srand(time(NULL));
    // Création de deux listes d'animaux, et initialisation de leur premier élément
    Animal *liste_proies = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, 10);
    Animal *liste_predateurs = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, 10);

    // Ajout de 19 autres animaux
    for(int i = 0; i < 19; i++){
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_proies);
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_predateurs);
    }

    // Affichage de l'écosystème
    afficher_ecosys(liste_predateurs,liste_proies);

    // Ecriture de l'écosystème dans un fichier
    ecrire_ecosys("ecosys.txt",liste_predateurs,liste_proies);
    
    //Création de deux listes vides 
    Animal * l_proies = NULL;
    Animal * l_pred = NULL;

    // Lecture dans le fichier et initialisation des listes, puis affichage
    lire_ecosys("ecosys.txt",&l_pred,&l_proies);
    afficher_ecosys(l_pred,l_proies);

    //Test enlever_animal :
    // Création de deux listes d'animaux
    Animal* liste_proi=NULL;
    Animal* liste_pre=NULL;

    // Création de 5 animaux
    Animal* test1=creer_animal(19,25,9.9);
    Animal* test2=creer_animal(17,24,9.9);
    Animal* test3=creer_animal(16,23,9.9);
    Animal* test4=creer_animal(15,22,9.9);
    Animal* test5=creer_animal(14,21,9.9);
    
    // Ajout des animaux aux deux listes et affichage
    liste_proi=ajouter_en_tete_animal(liste_proi,test1);
    liste_proi=ajouter_en_tete_animal(liste_proi,test2);
    liste_proi=ajouter_en_tete_animal(liste_proi,test3);
    liste_pre=ajouter_en_tete_animal(liste_pre,test4);
    liste_pre=ajouter_en_tete_animal(liste_pre,test5);
    afficher_ecosys(liste_proi,liste_pre);
    
    // On retire des animaux des listes et on affiche
    enlever_animal(&liste_pre,test4); 
    enlever_animal(&liste_proi,test3);
    afficher_ecosys(liste_proi,liste_pre);

    // Libération de toutes les listes
    liste_pre=liberer_liste_animaux(liste_pre);
    liste_proi=liberer_liste_animaux(liste_proi);
    liste_predateurs=liberer_liste_animaux(liste_predateurs);
    liste_proies=liberer_liste_animaux(liste_proies);
    l_pred=liberer_liste_animaux(l_pred);
    l_proies=liberer_liste_animaux(l_proies);
    afficher_ecosys(liste_predateurs,liste_proies);
    return 0;
}
