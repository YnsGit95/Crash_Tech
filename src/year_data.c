#include "year_data.h"
#include "csv.h"
#include "menu.h"


static void initialiser_stats(StatAnnee tab[]){

}

static unsigned long charg_annee(const char* chemin , StatAnnee tab[]){

}

int main(){
    int choix = -1;
    Accident* tab_annee[NB_ANNEES];
    unsigned long nb_accidents;
    unsigned long indemne;
    unsigned long tue;
    unsigned long grave;
    unsigned long leger;
    
    //appel fct tab_statique
    //appel fct tri_annee
    
    printf("\n====================  YEAR_DATA  ====================\n");
    
    do{
        printf("\nDe quelle année voulez-vous voir les statistiques ? (Pour quitter, taper 0) : \n");

        if (scanf("%d", &choix) != 1) { //verif que l'utilisateur ne tape pas n'importe quoi
            // on vide le buffer pour éviter une boucle infinie
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choix = -1;
        }

        if (choix == 0) {
            break;  // l'utilisateur quitte
        }
        else if (choix >= ANNEE_MIN && choix <= ANNEE_MAX) {
            // nb_accidents = donnee_par_annee(tab_annee[choix - ANNEE_MIN], &indemne, &tue, &grave, &leger);
            printf("\nEn %d :\n", choix);
            printf("Accidents      : %lu\n", nb_accidents);
            printf("Indemnes       : %lu\n", indemne);
            printf("Tués           : %lu\n", tue);
            printf("Blessés graves : %lu\n", grave);
            printf("Blessés légers : %lu\n", leger);
        }
        else {
            printf("\n\nERREUR ! Veuillez rentrer une des années suivantes : 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024\n\n");
        }
    } while (choix != 0);
    
    printf("\n====================  YEAR_DATA  ====================\n");
    
    for (i = 0, i++, i < NB_ANNEES){
        //appel fct liberer_avl(i);
    }

    return 0;
}
