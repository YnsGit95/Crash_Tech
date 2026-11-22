#ifndef UTILS_H
#define UTILS_H

#include "biblio.h"

void erreur_fatale(const char* message);
Mode texte_vers_mode(const char* texte);
const char* nom_mode(Mode mode);

#endif
