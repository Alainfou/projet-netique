#ifndef listeH_
#define listeH_

#include "utils.h"

/* Structures */

typedef struct ElementListeArc
{
    int numeroArc;
    struct ElementListeArc* psuivant;
}ElementListeArc;

typedef struct ListeArc
{
	ElementListeArc* pdebut;
	ElementListeArc* pfin;
}ListeArc;

/* Constructeurs */

ElementListeArc* consElementListeArc(int numeroArc);
ListeArc consListeVide();
ListeArc ajoutListeFin(ListeArc liste, int numeroArc);

/* Affichage */

void afficherListeArc(ListeArc liste);

/* Utilitaires */

void supprimerListe(ListeArc* liste);
bool estVideListe(ListeArc liste);
ListeArc copieListeArc(ListeArc liste);


#endif
