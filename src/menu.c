#include "menu.h"
#include "utils.h"

void afficher_titre(const char* titre) {
    printf("\n==================================================\n");
    printf("   %s\n", titre);
    printf("==================================================\n");
}

/* lit une ligne et enlève le '\n' */
static void lire_ligne(char* buffer, size_t taille) {
    if (fgets(buffer, (int)taille, stdin) == NULL)
        erreur_fatale("Entrée clavier interrompue");

    size_t lg = strlen(buffer);
    if (lg > 0 && buffer[lg - 1] == '\n') {
        buffer[lg - 1] = '\0';
    } else {
        /* la saisie était plus longue que le tampon : on vide le reste */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int lire_entier(const char* invite, int min, int max) {
    char saisie[64];
    char* fin;

    while (1) {
        printf("%s", invite);
        lire_ligne(saisie, sizeof saisie);

        long valeur = strtol(saisie, &fin, 10);
        if (fin != saisie && *fin == '\0' && valeur >= min && valeur <= max)
            return (int)valeur;

        printf("  Saisie invalide, entrez un nombre entre %d et %d.\n", min, max);
    }
}

Mode menu_choisir_mode(void) {
    afficher_titre("CRASH TECH - Accidents de la route 2005-2024");
    printf("  1. Statistiques par année        (YEAR_DATA)\n");
    printf("  2. Statistiques par âge          (AGE_DATA)\n");
    printf("  3. Rechercher un accident        (CRASH_DATA)\n");
    printf("  0. Quitter\n");

    switch (lire_entier("> ", 0, 3)) {
        case 1: return MODE_YEAR;
        case 2: return MODE_AGE;
        case 3: return MODE_CRASH;
        default: return MODE_QUITTER;
    }
}
