#include "csv.h"

int lire_ligne(char *texte, LigneCsv *res)
{
    char *champs[9];   // champs[0] = début de la colonne 1 jusqu'a champs[8] = debut de la colonne 9
    char *p =texte;   // endroit où on est dans la ligne (on commence au début)
    
    int i;

    for (i = 0;i<9; i++){      // On répète pour chacune des 9 colonnes
        champs[i] = p;             // La colonne i commence ici
        p = strchr(p, ';');        // On cherche le ';' qui la termine
        if (p == NULL){           // Pas de ';' trouvé...
            break;                 // ...on arrête de chercher
        }
        *p ='\0'; // On remplace le ';' par '\0' : la colonne est terminée
        p++;   // On avance d'un cran pour commencer la colonne suivante
    }

    if (i != 8){ // Si on n'a pas trouvé 9 colonnes (la 9e n'a pas de ';' donc i vaut 8 à la sortie du break)
        return 0; // la ligne est mauvaise
    }

    // On convertit chaque colonne et on la range dans la structure
    res->annee = atoi(champs[0]);

     //pour mettre le champs 2 dans la structure
    strncpy(res->collision_id, champs[1], 8);
    res->collision_id[8] = '\0';
   //pour mettre le  champs 3 dans la structure
    strncpy(res->vehicule_id, champs[2], 3);
    res->vehicule_id[3] = '\0';
    
   //pour mettre le champs 4 dans notre structure
    res->place = atoi(champs[3]);
    
    //pour mettre le champs 5 dans notre structure
    res->type = atoi(champs[4]);
    //pour mettre le champs 6 dans notre structure
    res->gravite = atoi(champs[5]);
    
    //pour mettre le champs 7 dans notre structure
    res->genre = atoi(champs[6]);
    //pour mettre le  champs 8 dans la structure
     res->annee_naissance = atoi(champs[7]);
    //pour mettre le champs 9 dans la structure
    res->trajet = atoi(champs[8]);

return 1;
}
