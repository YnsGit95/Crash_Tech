#include "avl.h"

struct noeud_avl {
    usine_t *usine;
    int hauteur;
    struct noeud_avl *gauche;
    struct noeud_avl *droite;
};

pArbre creation_a+vl (){

}

static int hauteurnoeud(noeud_avl_t *noeud) {
    return noeud ? noeud->hauteur : 0;
}

static int maximum(int a, int b) {
    return (a > b) ? a : b;
}

static int minimum(int a, int b){
  return (a < b) ? a : b;
}

static int equilibre(noeud_avl_t *noeud) {
    return noeud ? (hauteurnoeud(noeud->gauche) - hauteurnoeud(noeud->droite)) : 0;
}

void insertion_avl(){

}

void liberer_avl
