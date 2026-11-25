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



//on va ouvrir le fichier et initialisée notre nombre de ligne ainsi que la capacite a 0
void csv_ouvrir(LecteurCsv* lecteur, const char* chemin) {
    lecteur->fichier = fopen(chemin, "r");
    if (lecteur->fichier == NULL)
        erreur_fatale("Impossible d'ouvrir le fichier de données");
    lecteur->buffer = NULL;
    lecteur->capacite = 0;
    lecteur->num_ligne = 0;
    lecteur->nb_ignorees = 0;
}
//apres on retire les '\n' de fin de ligne et le '\r' qui est souvent présentdans des fichiers crées sur windows(on traite tous les cas pour que le code soit bien robuste 
 void retirer_fin_ligne(char* ligne) {
    size_t lg = strlen(ligne);
    while (lg > 0 && (ligne[lg - 1] == '\n' || ligne[lg - 1] == '\r')) {
        lg--;
        ligne[lg] = '\0'; //c'est dans cette ligne on le remplace avec \0
    }
}

    


//apres on va lire ligne parligne jusqua trouver une ligne correcte (sous le format quon voulait avoir) et on va le recuperer
int csv_suivante(LecteurCsv* lecteur, LigneCsv* res) {
    while (getline(&lecteur->buffer, &lecteur->capacite, lecteur->fichier) != -1) {
        lecteur->num_ligne++;
        retirer_fin_ligne(lecteur->buffer);

        if (lecteur->buffer[0] == '\0')
            continue;                                 
        if (lecteur->num_ligne == 1 && !isdigit((unsigned char)lecteur->buffer[0]))
            continue;                                  

        if (lire_ligne(lecteur->buffer, res))
            return 1;
        lecteur->nb_ignorees++;                         
    }
    return 0;                                           
}


