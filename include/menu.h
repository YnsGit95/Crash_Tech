#ifndef MENU_H
#define MENU_H

#include "biblio.h"
#define DOSSIER_DONNEES "data"


/* demande un entier entre min et max, redemande tant que c'est faux */
int lire_entier(const char* invite, int min, int max);

/* affiche le menu principal et renvoie le mode choisi */
Mode menu_choisir_mode(void);

/* remplit "chemin" avec le fichier choisi. Renvoie 0 si l'utilisateur annule. */
int menu_choisir_fichier(char* chemin, size_t taille);

void afficher_titre(const char* titre);

#endif

