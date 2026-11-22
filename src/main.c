#include "biblio.h"
#include "utils.h"
#include "menu.h"

/*les modes seront branchés ici quand ils seront écrits */
static void lancer_mode(Mode mode, const char* chemin) {
    printf("\n  Mode %s sur le fichier %s : pas encore disponible.\n", nom_mode(mode), chemin);
}

int main(int argc, char* argv[]) {
    /* ./crashTech YEAR_DATA data.csv  : lancement direct si on doit respecter comme la commande dans le sujet*/
    if (argc == 3) {  
        Mode mode = texte_vers_mode(argv[1]);
        if (mode == MODE_INVALIDE)
            erreur_fatale("Mode inconnu. Modes possibles : YEAR_DATA, AGE_DATA, CRASH_DATA");
        lancer_mode(mode, argv[2]);
        return EXIT_SUCCESS;
    }

    /* ./crashTech : et ici c'est ma touche perso parce que je trouve ca plus simple avec une menu intéractif */
    if (argc == 1) {
        char chemin[512];
        Mode mode;
        while ((mode = menu_choisir_mode()) != MODE_QUITTER) {
            if (menu_choisir_fichier(chemin, sizeof chemin))
                lancer_mode(mode, chemin);
        }
        printf("Au revoir !\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Usage : %s                       (menu)\n", argv[0]);
    fprintf(stderr, "        %s MODE fichier.csv      (MODE = YEAR_DATA, AGE_DATA ou CRASH_DATA)\n", argv[0]);
    return EXIT_FAILURE;
}
