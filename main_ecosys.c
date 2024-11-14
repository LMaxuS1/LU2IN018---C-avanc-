//Maximilien Piron-Palliser
//Yanis Baouche

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define E_PRED 100
#define E_PROIE 10


void test (){
    // Création d'un animal
    Animal *animal = creer_animal(13, 35, 10.0);
    afficher_ecosys(animal,NULL);
    
    // Test du mouvement
    bouger_animaux  (animal);
    afficher_ecosys (animal,NULL);

    // Test de la reproduction à deux reprises
    reproduce(&animal, p_reproduce_proie);
    afficher_ecosys(animal, NULL);

    reproduce(&animal, p_reproduce_proie);
    afficher_ecosys(animal, NULL);
}

int main(void) {
    srand(time(NULL));

    // Déclaration et initalisation du monde
    int monde[SIZE_X][SIZE_Y] = {0};
    
    // Déclaration et initialisation des listes d'animaux (proies et prédateurs)
    Animal *liste_proies = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, E_PROIE);
    Animal *liste_pred = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, E_PRED);  

    // Ajout de 19 animaux de chaque, dans chaque liste 
    for(int i = 0; i < 19; i++){
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, E_PROIE, &liste_proies);
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, E_PRED, &liste_pred);
    }
    // Premier affichage
    afficher_ecosys(liste_proies,liste_pred);
    usleep(300000);

    // Création et ouverte d'un fichier texte
    FILE *f= fopen("Evol_Pop.txt","w");
    if (f==NULL){
        printf("Erreur à l'ouverture");
        exit(1);
    }
    fprintf(f,"Itération Proies Prédateurs\n");
    int i=0;

    // Vie de l'écosystème
    while ((liste_proies || liste_pred)&& i<200){
        fprintf(f,"%d %d %d\n",i,compte_animal_it(liste_proies),compte_animal_it(liste_pred));    
        afficher_ecosys(liste_proies,liste_pred);
        usleep(100000);
        clear_screen();
        rafraichir_proies(&liste_proies,monde);
        rafraichir_predateurs(&liste_pred, &liste_proies);
        rafraichir_monde(monde);
        i++;
    }

    // Fermeture du fichier et libération finale des listes
    fclose(f);
    liste_proies=liberer_liste_animaux(liste_proies);
    liste_pred=liberer_liste_animaux(liste_pred);
    printf("Simulation terminée\n");

    /*Pour faire apparaître les courbes,
    il faut utiiser gnuplot : 
    dans le terminal, écrire "gnuplot"
    puis
    taper les commandes suivantes : 
    plot "Evol_Pop.txt" using 1:2 with lines title "proies"
    replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
    exit
    */


    return 0;
}

