#define _POSIX_C_SOURCE 200809L   /* pour getline */
#include "csv.h"
#include "utils.h"
#include <ctype.h>


/* Convertit une colonne en entier. Renvoie 0 si ce n'est pas un nombre */
static int champ_entier(const char* champ, int* resultat) {
    char* fin;
    long valeur = strtol(champ, &fin, 10);
    if (fin == champ || *fin != '\0')
        return 0;
    *resultat = (int)valeur;
    return 1;
}


/* Pareil, mais une colonne vide est acceptée et vaut -1 (ex : année de naissance non renseignée) */
static int champ_entier_optionnel(const char* champ, int* resultat) {
    if (*champ == '\0') {
        *resultat = -1;
        return 1;
    }
    return champ_entier(champ, resultat);
}


/* Copie une colonne texte si elle rentre dans le tableau (sinon on refuse) */
static int champ_texte(const char* champ, char* destination, size_t taille) {
    size_t lg = strlen(champ);
    if (lg == 0 || lg >= taille)
        return 0;
    strcpy(destination, champ);
    return 1;
}


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

    if (!champ_entier(champs[0], &res->annee)){
        return 0;
    } 
    if (!champ_texte(champs[1], res->collision_id, sizeof res->collision_id)){
        return 0;
    } 
    if (!champ_texte(champs[2], res->vehicule_id, sizeof res->vehicule_id)){
        return 0;
    } 
    if (!champ_entier(champs[3], &res->place)){
        return 0;
    } 
    if (!champ_entier(champs[4], &res->type)){
        return 0;
    } 
    if (!champ_entier(champs[5], &res->gravite)){
        return 0;
    } 
    if (!champ_entier(champs[6], &res->genre)){
        return 0;
    }
    if (!champ_entier_optionnel(champs[7], &res->annee_naissance)){
        return 0;
    } 
    if (!champ_entier_optionnel(champs[8], &res->trajet)){
        return 0;
    } 

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


void csv_fermer(LecteurCsv* lecteur) {
    free(lecteur->buffer);
    fclose(lecteur->fichier);
}



