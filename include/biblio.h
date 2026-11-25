#ifndef BIBLIO_H
#define BIBLIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define ANNEE_MIN 2005
#define ANNEE_MAX 2024
#define NB_ANNEES (ANNEE_MAX - ANNEE_MIN + 1)

#define TAILLE_ID_VEHICULE 7
#define TAILLE_ID_COLLISION 9


typedef enum{ 
    MODE_INVALIDE, 
    MODE_YEAR, 
    MODE_AGE, 
    MODE_CRASH,
    MODE_QUITTER
} Mode;

/*
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

*/

#endif
