#include "year_data.h"
#include "csv.h"
#include "menu.h"


static void initialiser_stats(StatAnnee tab[]){
 for (int i = 0; i < NB_ANNEES; i++) {
        tab[i].nb_accidents = 0;
        tab[i].nb_indemnes = 0;
        tab[i].nb_tues = 0;
        tab[i].nb_graves = 0;
        tab[i].nb_legers = 0;
    }
}

static unsigned long charger_annees(const char* chemin, StatAnnee tab[]) {
    LecteurCsv lecteur;
    LigneCsv ligne;
    unsigned long hors_periode = 0;
    unsigned long nb_lignes = 0;

    /* accident de la ligne précédente, pour savoir quand on passe au suivant */
    int annee_prec = -1;
    char id_prec[TAILLE_ID_COLLISION] = "";

    csv_ouvrir(&lecteur, chemin);

    while (csv_suivante(&lecteur, &ligne)) {
        nb_lignes++;

        if (ligne.annee < ANNEE_MIN || ligne.annee > ANNEE_MAX) {
            hors_periode++;
            continue;
        }
        StatAnnee* s = &tab[ligne.annee - ANNEE_MIN];

        /* une ligne = une victime. Les victimes d'un même accident se suivent,
           donc un nouvel accident commence quand l'année ou l'id change. */
        if (ligne.annee != annee_prec || strcmp(ligne.collision_id, id_prec) != 0) {
            s->nb_accidents++;
            annee_prec = ligne.annee;
            strcpy(id_prec, ligne.collision_id);
        }

        switch (ligne.gravite) {
            case 1: s->nb_indemnes++; break;
            case 2: s->nb_tues++;     break;
            case 3: s->nb_graves++;   break;
            case 4: s->nb_legers++;   break;
            default: break;           /* gravité inconnue : on ne la compte pas */
        }
    }

    printf("  %lu lignes valides, %lu lignes ignorées (mal formées)\n", nb_lignes, lecteur.nb_ignorees);
    csv_fermer(&lecteur);
    return hors_periode;
}


static void afficher_annee(const StatAnnee* s, int annee) {
    unsigned int nb_victimes = s->nb_indemnes + s->nb_tues + s->nb_graves + s->nb_legers;

    afficher_titre("YEAR_DATA");
    printf("  Année %d\n\n", annee);
    printf("  Accidents          : %u\n", s->nb_accidents);
    printf("  Victimes           : %u\n", nb_victimes);
    printf("    - tués           : %u\n", s->nb_tues);
    printf("    - blessés graves : %u\n", s->nb_graves);
    printf("    - blessés légers : %u\n", s->nb_legers);
    printf("    - indemnes       : %u\n", s->nb_indemnes);
}


void lancer_year_data(const char* chemin) {
    StatAnnee tab[NB_ANNEES];    
    int annee;

    initialiser_stats(tab);

    printf("\nChargement de %s ...\n", chemin);
    unsigned long hors_periode = charger_annees(chemin, tab);
    if (hors_periode > 0)
        printf("  %lu lignes hors de la période %d-%d (ignorées)\n", hors_periode, ANNEE_MIN, ANNEE_MAX);

    do {
        printf("\nDe quelle année voulez-vous voir les statistiques ? (%d-%d, 0 pour revenir)\n",
               ANNEE_MIN, ANNEE_MAX);
        annee = lire_entier("> ", 0, ANNEE_MAX);

        if (annee != 0 && annee < ANNEE_MIN)
            printf("  Pas de données avant %d.\n", ANNEE_MIN);
        else if (annee != 0)
            afficher_annee(&tab[annee - ANNEE_MIN], annee);
    } while (annee != 0);

}
