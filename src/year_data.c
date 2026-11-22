#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define ANNEE_MIN 2005 //a mettre dans year_data.h
#define ANNEE_MAX 2024 //a mettre dans year_data.h
#define NB_ANNEES 20 //a mettre dans year_data.h

typedef enum{ 
    MODE_INVALIDE, 
    MODE_YEAR, 
    MODE_AGE, 
    MODE_CRASH,
    MODE_QUITTER
} Mode;


typedef struct victime{
    int place; //1 pour les conducteurs, 2 pour les passagers à l’avant, 10 pour les pietons, autre pour d’autres emplacements
    int genre; //1 masculin, 2 féminin, autre si non relevé ou autre genre
    int age;
    int gravite; //1 indemne, 2 tué, 3 blessé grave, 4 blessé léger
    int type; //1 pour conducteur, 2 pour passager, 3 pour pieton
    struct victime* suivant;
}Victime;

typedef struct vehicule{
    int vehicule_id;
    int purpose; //-1/0 : non renseigné, 1 :Domicile – travail, 2 Domicile – ecole, 3 Courses, 4 Déplacement professionnel, 5 loisirs, 6 et plus : autres
    Victime* pVictime;
    struct vehicule* suivant;
}Vehicule;

typedef struct accident{
    char cle[13];
    Vehicule* pVehicule;
    struct accident* fg;
    struct accident* fd;
}Accident;

typedef struct {
    Accident* p;
}pAccident;

//fct tab_statique_annee créer tableau statique avec un avl par année

//fct tri_annee qui lit une ligne et trie la ligne dans les arbres d'année (un avl avec tout les accidents de 2005, un avl avec tout les accidents de 2006, un avl avec tout les accidents de 2007, un avl avec tout les accidents de 2008, ...)

//fct donnee_par_annee parcours infixe de l'avl pour recuperation des données (nombre d’accidents total = somme des accidents, Les nombres des différents types de severités = une variable par severité -> somme des victimes (dans les vehicules eux memes dans les accidents pour chaque années)

//fct main demande a utilisateur, via menu, quelle est l’année pour laquelle il souhaite consulter les statistiques, puis si il veut consulter les stats d'un autre année ou quitter le programme

//fct liberer_avl pour liberation memoire

int main(){
    int choix = -1;
    Accident* tab_annee[NB_ANNEES];
    unsigned long nb_accidents;
    unsigned long indemne;
    unsigned long tue;
    unsigned long grave;
    unsigned long leger;
    
    //appel fct tab_statique
    //appel fct tri_annee
    
    printf("\n====================  YEAR_DATA  ====================\n");
    
    do{
        printf("\nDe quelle année voulez-vous voir les statistiques ? (Pour quitter, taper 0) : \n");

        if (scanf("%d", &choix) != 1) { //verif que l'utilisateur ne tape pas n'importe quoi
            // on vide le buffer pour éviter une boucle infinie
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choix = -1;
        }

        if (choix == 0) {
            break;  // l'utilisateur quitte
        }
        else if (choix >= ANNEE_MIN && choix <= ANNEE_MAX) {
            // nb_accidents = donnee_par_annee(tab_annee[choix - ANNEE_MIN], &indemne, &tue, &grave, &leger);
            printf("\nEn %d :\n", choix);
            printf("Accidents      : %lu\n", nb_accidents);
            printf("Indemnes       : %lu\n", indemne);
            printf("Tués           : %lu\n", tue);
            printf("Blessés graves : %lu\n", grave);
            printf("Blessés légers : %lu\n", leger);
        }
        else {
            printf("\n\nERREUR ! Veuillez rentrer une des années suivantes : 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024\n\n");
        }
    } while (choix != 0);
    
    printf("\n====================  YEAR_DATA  ====================\n");
    
    //appel fct liberer_avl

    return 0;
}
