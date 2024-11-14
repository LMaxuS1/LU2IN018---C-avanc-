//Maximilien Piron-Palliser
//Yanis Baouche

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

float p_ch_dir=0.4;
float p_reproduce_proie=0.25;
float p_reproduce_predateur=0.20;
int temps_repousse_herbe=-14;

/* PARTIE 1*/
//Fourni: Part 1, exercice 4, question 2 
// Permet de créer un nouvel animal en position x y avec une certaine énergie
Animal *creer_animal(int x, int y, float energie) {
    Animal *na = (Animal *)malloc(sizeof(Animal));
    assert(na);
    na->x = x;
    na->y = y;
    na->energie = energie;
    na->dir[0] = rand() % 3 - 1;
    na->dir[1] = rand() % 3 - 1;
    na->suivant = NULL;
    return na;
}

// Fourni: Part 1, exercice 4, question 3
// Permet d'ajouter un animal en tête de liste
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
    assert(animal);
    assert(!animal->suivant);
    animal->suivant = liste;
    return animal;
}

// A faire. Part 1, exercice 6, question 2
// Permet de créer et d'ajouter un animal en tête de liste en seule fonction
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
    Animal *new=creer_animal(x,y,energie);
    *liste_animal=ajouter_en_tete_animal(*liste_animal,new); 
}

// A Faire. Part 1, exercice 5, question 5
// Permet de retirer un animal de la liste 
void enlever_animal(Animal **liste, Animal *animal) {
    Animal *tmp1=*liste;
    Animal *tmp2=NULL;

    if  (tmp1==animal){
        tmp2=tmp1;
        *liste=(*liste)->suivant;
        free(tmp2);
    }
    else{
        while(tmp1){
        if(tmp1->suivant==animal){
            tmp2=tmp1->suivant;
            tmp1->suivant=tmp1->suivant->suivant;
            free(tmp2);
        }
        tmp1=tmp1->suivant;
        }
    }
}

// A Faire. Part 1, exercice 6, question 7
// Permet de libérer entièrement une liste d'animaux
Animal* liberer_liste_animaux(Animal *liste) {
    Animal *tmp1=liste;
    Animal *tmp2=NULL;

    while (tmp1) {
        tmp2=tmp1;
        tmp1=tmp1->suivant;
        free(tmp2);
    }

    return NULL;
}

// Fourni: part 1, exercice 4, question 4
// Permet de compter le nomber d'animaux dans une liste de manière récursive
unsigned int compte_animal_rec(Animal *la) {
    if (!la) return 0;
    return 1 + compte_animal_rec(la->suivant);
}

// Fourni: part 1, exercice 4, question 4
// Permet de compter le nomber d'animaux dans une liste de manière itérativee
unsigned int compte_animal_it(Animal *la) {
    int cpt=0;
    while (la) {
        ++cpt;
        la=la->suivant;
    }
    return cpt;
}

// Part 1. Exercice 5, question 1
// Permet d'afficher notre écosystème de taille SIZE_X * SIZE_Y
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
    unsigned int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    Animal *pa=NULL;

    for (i = 0; i < SIZE_X; ++i) {
        for (j = 0; j < SIZE_Y; ++j) {
        ecosys[i][j]=' ';
        }
    }

    // On ajoute les proies
    pa = liste_proie;
    while (pa) {
        ecosys[pa->x][pa->y] = '*';
        pa=pa->suivant;
    }

    // On ajoute les predateurs
    pa = liste_predateur;
    while (pa) {
        if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { 
            ecosys[pa->x][pa->y] = '@';
        } else {
            ecosys[pa->x][pa->y] = 'O';
        }
        pa = pa->suivant;
    }

    // On affiche le tableau
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }  
    printf("+\n");
    for (i = 0; i < SIZE_X; ++i) {
        printf("|");
        for (j = 0; j < SIZE_Y; ++j) {
        putchar(ecosys[i][j]);
        }
        printf("|\n");
    }
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }
    printf("+\n");
    int nbproie=compte_animal_it(liste_proie);
    int nbpred=compte_animal_it(liste_predateur);
    
    printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
    
    //Pour les boucles, il fallait mettre i < SIZE_X et j < SIZE_Y, pas l'inverse.

}

// code ANSI X3.4 pour effacer l'ecran 
// Permet d'effacer ce qu"il y a sur le terminal 
void clear_screen() {
    printf("\x1b[2J\x1b[1;1H");  
}


    /* PARTIE 2*/

// Part 2. Exercice 4, question 1
// Permet de faire bouger les animaux d'une liste avec une certaine probabilité qu'ils le fassent
void bouger_animaux(Animal *la) {
    Animal *a = la;
    while(a){
        if(rand()/(float)RAND_MAX<p_ch_dir){
            a->dir[0]=rand()%3-1;
            a->dir[1]=rand()%3-1;
        }
        a->x =(a->x+a->dir[0]+SIZE_X)%SIZE_X;
        a->y =(a->y+a->dir[1]+SIZE_Y)%SIZE_Y;
        a=a->suivant;
    }
}

// Part 2. Exercice 4, question 3
// Permet de faire reproduire les animaux d'une liste avec une certain probabilité que cela arrive
void reproduce(Animal **liste_animal, float p_reproduce) {
    Animal *a = liste_animal?*liste_animal:NULL;
    while(a){
        if(rand()/(float)RAND_MAX<p_reproduce){
            ajouter_animal(a->x,a->y,a->energie/2,liste_animal);
            a->energie=a->energie/2;
        }
        a=a->suivant;
    }
}

// Part 2. Exercice 3
// Permet de créer un fichier texte dans lequel nous écrirons les données des animaux de chaque listes
void ecrire_ecosys (const char * nom_fichier, Animal * liste_predateur, Animal * liste_proie){
    FILE * f = fopen (nom_fichier,"w");
    if (f==NULL){printf("Erreur lors de l'ouverture"); return;}
    fprintf(f,"<proies>\n");
    Animal * tmp = liste_proie;
    while(tmp){
        fprintf(f,"x=%d y=%d dir[%d %d] e=%f\n",tmp->x,tmp->y,tmp->dir[0],tmp->dir[1],tmp->energie);
        tmp=tmp->suivant;
    }
    fprintf(f,"</proies>\n");
    tmp = liste_predateur;
    fprintf(f,"<predateurs>\n");
    while(tmp){
        fprintf(f,"x=%d y=%d dir[%d %d] e=%f\n",tmp->x,tmp->y,tmp->dir[0],tmp->dir[1],tmp->energie);
        tmp=tmp->suivant;
    }
    fprintf(f,"</predateurs>\n");
    fclose(f);
}

// Part 2. Exercice 3
// Permet de créer deux listes d'animaux (respectivement proies et prédateurs) à partir d'un fichier texte
void lire_ecosys (const char * nom_fichier, Animal ** liste_predateur, Animal ** liste_proie){
    FILE * f=fopen (nom_fichier,"r");
    if (f==NULL){printf("Erreur lecture\n");return;}
    char buffer[256];
    fgets(buffer,256,f);
    assert(strncmp(buffer,"<proies>",8)==0);
    int x_lu,y_lu,dir0,dir1;
    float e_lu;
    fgets(buffer,256,f);
    while(strncmp(buffer,"</proies>",9)!=0){
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x_lu,&y_lu,&dir0,&dir1,&e_lu);
        Animal * a = creer_animal(x_lu,y_lu,e_lu);
            a->dir[0]=dir0;
            a->dir[1]=dir1;
            a->suivant=*liste_proie;
            *liste_proie = a;
        fgets(buffer,256,f);
    }
    fgets(buffer,256,f);
    assert(strncmp(buffer,"<predateurs>",12)==0);
    fgets(buffer,256,f);
    while(strncmp(buffer,"</predateurs>",13)!=0){
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x_lu,&y_lu,&dir0,&dir1,&e_lu);
        Animal * a = creer_animal(x_lu,y_lu,e_lu);
            a->dir[0]=dir0;
            a->dir[1]=dir1;
            a->suivant=*liste_predateur;
            *liste_predateur = a;
        fgets(buffer,256,f);
    }
    fclose(f);
}

// Part 2. Exercice 6, question 1
// Permet de faire vivre les proies (Bouger, manger(de l'herbe), se reproduire et mourir)
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    Animal *a = liste_proie?*liste_proie:NULL;
    bouger_animaux(*liste_proie);
    while (a){
        a->energie--;
        if (a->energie<=0){
            enlever_animal(liste_proie, a);
        }
        else if(monde[a->x][a->y]>0){
            a->energie+=monde[a->x][a->y];
            monde[a->x][a->y]=temps_repousse_herbe;
        }
        a=a->suivant;
    }
    reproduce(liste_proie,p_reproduce_proie);
}

// Part 2. Exercice 7, question 1
// Permet de vérifier qu'un animal est à une certain position x y 
Animal *animal_en_XY(Animal *l, int x, int y) {
    Animal *a =l;
    while(a){
        if ((a->x == x)&& (a->y ==y)){
            return a;
        }
        a=a->suivant;
    }
    return NULL;
} 

// Part 2. Exercice 7, question 2
// Permet de faire vivre les prédateurs (Bouger, manger(des proies), se reproduire et mourir)
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
    Animal *a = liste_predateur?*liste_predateur:NULL;
    bouger_animaux(*liste_predateur);
    while (a){
        a->energie--;
        if (a->energie<0){
            enlever_animal(liste_predateur, a);
        }
        else{
            Animal *pv = animal_en_XY(*liste_proie, a->x, a->y);
            if (pv!=NULL){
                a->energie+=pv->energie;
                enlever_animal(liste_proie, pv);
            }
        }
        a=a->suivant;
    }
    reproduce(liste_predateur,p_reproduce_predateur); 
}

// Part 2. Exercice 5, question 2
// Permet de faire pousser de l'herbe dans notre 'monde' 
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
    for (int i=0;i<SIZE_X;i++){
        for(int j=0;j<SIZE_Y;j++){
            monde[i][j]++;
        }
    }
}