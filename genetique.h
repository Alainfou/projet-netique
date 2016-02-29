#ifndef genetiqueH_
#define genetiqueH_

#include <math.h>

#include "mesure.h"
#include "graphe.h"

/* Structures de données*/

typedef struct Allele
{
    Mesure mesure;
    int numeroArc;
    bool actif;
}Allele;

typedef struct Personne
{
    int id;
    int nbAllele;
    Allele* genome;
    float score;
    float lenght;
    float budget;
}Personne;

typedef struct ElementListePopulation
{
    Personne personne;
    struct ElementListePopulation *psuivant;
}ElementListePopulation;

typedef struct ListePopulation
{
    ElementListePopulation *pdebut;
    ElementListePopulation *pfin;
}ListePopulation;

typedef struct Population
{
    int taillePopulation;
    ListePopulation listePopulation;
}Population;

typedef struct GeneticSolver
{
    float ratioPriority;
    float mutationRate;
    float crossesRate;
    int targetBudget;
}GeneticSolver;

/* Constructeurs */

Personne genererPersonne(int id, Mesures mesures, Graphe graphe);
Allele consAlleleVide();
Personne consPersonneVide();
Population consPopulationVide();
ListePopulation consListePopulationvide();
ElementListePopulation* consElementListePopulation();
ListePopulation ajoutListePopulationFin(ListePopulation liste, Personne personne);
Personne consPersonneFonctionnel(int nbAllele);

/* Utilitaires */

void supprimerPersonne(Personne* personne);
void supprimerListePopulation(ListePopulation* liste);
void supprimerPopulation(Population* population);
bool estVideListePopulation(ListePopulation liste);
Personne dupliquerPersonne(Personne personne);

/* Affichage */

void afficherPersonne(Personne personne);
void afficherAllele(Allele allele);
void afficherListePopulation(ListePopulation liste);
void afficherPopulation(Population population);
void afficherPersonneFinal(Personne personne);

/* Génétique */

Population croisements(Population population, float crossesRate, int idBegin);
Population mutations(Population population, float mutationRate);
Graphe appliquerPersonne(Personne personne, Graphe graphe);
Graphe retirerPersonne(Personne personne, Graphe graphe);
float score(GeneticSolver geneticSolver, Personne personne);
Personne majPersonne(GeneticSolver geneticSolver, Personne personne);
Population selection(Population population, int n);
Personne selectionONE(Population population);


#endif
