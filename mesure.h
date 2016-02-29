#ifndef mesureH_
#define mesureH_

#include "liste.h"

/* Structure */

typedef struct Mesure
{
    int cout;
    ListeArc efficacite;
    int id;
    ListeArc arcApplicables;
}Mesure;

typedef struct Mesures
{
    int nbMesure;
    int nbMesuresTotales;
    Mesure* tabMesure;
}Mesures;

/* Constructeurs */

Mesures consMesuresVide();
Mesure consMesureVide();
Mesure consMesureManuel(int nbArc, int id);
Mesures consMesuresManuel(int nbArc);

/* Affichage */

void afficherMesure(Mesure mesure);
void afficherMesures(Mesures mesures);

/* Outils */

void supprimerMesure(Mesure* mesure);
void supprimerMesures(Mesures *mesures);

#endif
