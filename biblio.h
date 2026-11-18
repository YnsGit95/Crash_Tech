#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef struct victime{
    
    struct victime* suivant;
}Victime;

typedef struct vehicule{
    
    Victime* pVictime;
    struct vehicule* suivant;
}Vehicule;

typedef struct accident{
    Vehicule* pVehicule;
    struct accident* fg;
    struct accident* fd;
}Accident;

typedef struct {
    Accident* p;
}pAccident;
