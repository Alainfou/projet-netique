#ifndef grapheH_
#define grapheH_

#include "liste.h"
#include "utils.h"

/* Structures */

typedef struct Arc
{
	int noeudDepart;
	int noeudArrive;
	int ponderation;
	int cout;
} Arc;

typedef struct Noeud
{
    int niveau;
    ListeArc listePrec;
    ListeArc listeSuiv;
} Noeud;

typedef struct Graphe
{
    int nbLevel;
    int nbArc;
    int nbNoeuds;
    Noeud * tabNoeuds;
    Arc* tabArcs;
} Graphe;

/* Constructeurs */
Graphe consGrapheVide();
Graphe consGrapheManuel();
Arc consArcVide();
Noeud consNoeudVide();

/* Affichage */
void afficherArc(Arc arc);
void afficherGraphe(Graphe graphe);

/* Utilitaires */
void supprimerGraphe(Graphe *graphe);
Graphe decomposition(Graphe graphe);
ListeArc plusCourtChemin(Graphe graphe);


#endif
