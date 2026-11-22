#include "menu.h"
#include "utils.h"
#include <dirent.h>

void afficher_titre(const char* titre) {
    printf("\n==================================================\n");
    printf("   %s\n", titre);
    printf("==================================================\n");
}

/* lit une ligne au clavier et enlève le '\n' */
static void lire_ligne(char* buffer, size_t taille) {
    if (fgets(buffer, (int)taille, stdin) == NULL)
        erreur_fatale("Entrée clavier interrompue");

    size_t lg = strlen(buffer);
    if (lg > 0 && buffer[lg - 1] == '\n') {
        buffer[lg - 1] = '\0';
    } else {
        /* la saisie était plus longue que le tampon on vide le reste */
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

static int est_un_csv(const char* nom) {
    size_t lg = strlen(nom);
    return lg > 4 && strcmp(nom + lg - 4, ".csv") == 0;
}

/* Affiche les .csv du dossier data/ numérotés à partir de 1 et renvoie leur nombre.
   Si "cible" vaut un numéro, copie le nom correspondant dans "nom_trouve". */
static int parcourir_csv(int cible, char* nom_trouve, size_t taille) {
    DIR* dossier = opendir(DOSSIER_DONNEES);
    if (dossier == NULL)
        return 0;

    int n = 0;
    struct dirent* entree;
    while ((entree = readdir(dossier)) != NULL) {
        if (!est_un_csv(entree->d_name))
            continue;
        n++;
        if (cible == 0)
            printf("  %d. %s\n", n, entree->d_name);
        else if (n == cible)
            snprintf(nom_trouve, taille, "%s", entree->d_name);
    }
    closedir(dossier);
    return n;
}

static int fichier_lisible(const char* chemin) {
    FILE* f = fopen(chemin, "r");
    if (f == NULL)
        return 0;
    fclose(f);
    return 1;
}

int menu_choisir_fichier(char* chemin, size_t taille) {
    char nom[256];

    printf("\nFichiers trouvés dans %s/ :\n", DOSSIER_DONNEES);
    int nb = parcourir_csv(0, NULL, 0);
    if (nb == 0)
        printf("  (aucun fichier .csv)\n");
    printf("  %d. Saisir un autre chemin\n", nb + 1);
    printf("  0. Retour\n");

    int choix = lire_entier("> ", 0, nb + 1);
    if (choix == 0)
        return 0;

    if (choix <= nb) {
        parcourir_csv(choix, nom, sizeof nom);
        snprintf(chemin, taille, "%s/%s", DOSSIER_DONNEES, nom);
    } else {
        printf("Chemin du fichier : ");
        lire_ligne(chemin, taille);
    }

    if (!fichier_lisible(chemin)) {
        printf("  Impossible d'ouvrir \"%s\".\n", chemin);
        return 0;
    }
    return 1;
}