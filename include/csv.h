
#ifndef CSV_H      // Si CSV_H n'est pas encore défini on le defini juste apres:
#define CSV_H      // c'est la ou on la défini sinon

#include "biblio.h"

typedef struct {
    int annee;              // Colonne 1:     année de l'accident(dee 2005 a 2024)
    char collision_id[TAILLE_ID_COLLISION];   // Colonne 2 : id de l'accident(on va lire dans chaque ligne)
    char vehicule_id[TAILLE_ID_VEHICULE];    // Colonne 3 :  id du véhicule(selon ce qui est marque sur le fichier)
    int place;              // Colonne 4 : place dans le véhicule(location)
    int type;               // Colonne 5 :  1 conducteur,2 passager,3 piéton(user_type)
    int gravite;            // Colonne 6 :1 indemne,2 tué,3 blessé grave,4 blessé léger
    int genre;              // Colonne 7 :1 masculin, 2 féminin,autre si non relevé
    int annee_naissance;    // Colonne 8 :année de naissance (0 si vide)
    int trajet;             // Colonne 9 :type de trajet (la raison)
} LigneCsv;

typedef struct{
    FILE* fichier;
    char* buffer;
    size_t capacite;
    unsigned long num_ligne;
    unsigned long nb_ignorees;
}LecteurCsv;

int lire_ligne(char *texte, LigneCsv *res);   // Annonce la fonction : renvoie 1 si la ligne est bonne, 0 sinon
void csv_ouvrir(LecteurCsv* lecteur, const char* chemin);
int csv_suivante(LecteurCsv* lecteur, LigneCsv* res);
void csv_fermer(LecteurCsv* lecteur);

#endif             
