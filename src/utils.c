#include "utils.h"

void erreur_fatale(const char* message) {
    fflush(stdout);  //permet de vider le tampon pour afficher tous les printf précedents avant que le programme s'arrète.
    fprintf(stderr, "\nERREUR : %s\n", message);
    exit(EXIT_FAILURE);
}

Mode texte_vers_mode(const char* texte) {
    if (strcmp(texte, "YEAR_DATA") == 0){
      return MODE_YEAR;
    }
    if (strcmp(texte, "AGE_DATA") == 0){
      return MODE_AGE;
    }
    if (strcmp(texte, "CRASH_DATA") == 0){
      return MODE_CRASH;
    }
    return MODE_INVALIDE;
}

const char* nom_mode(Mode mode) {
    switch (mode) {
        case MODE_YEAR:  return "YEAR_DATA";
        case MODE_AGE:   return "AGE_DATA";
        case MODE_CRASH: return "CRASH_DATA";
        default:         return "?";
    }
}
