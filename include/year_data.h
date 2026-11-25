#ifndef YEAR_DATA_H
#define YEAR_DATA_H

#include "csv.h"
#include "menu.h"

typedef struct{
  unsigned int nb_accidents;
  unsigned int nb_indemnes;
  unsigned int nb_tues;
  unsigned int nb_graves;
  unsigned int nb_legers;
} StatAnne;

void lancer_year_data(const char* chemin);

#endif
