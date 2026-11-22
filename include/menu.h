#ifndef MENU_H
#define MENU_H

#include "biblio.h"

/* demande un entier entre min et max, redemande tant que c'est faux */
int lire_entier(const char* invite, int min, int max);

/* affiche le menu principal et renvoie le mode choisi */
Mode menu_choisir_mode(void);

void afficher_titre(const char* titre);

#endif
