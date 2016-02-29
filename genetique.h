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

typedef struct Individu
{
    int id;
    int nbAllele;
    Allele* genome;
    float score;
    float lenght;
    float budget;
}Individu;

typedef struct ElementListePopulation
{
    Individu individu;
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

Individu genererIndividu(int id, Mesures mesures, Graphe graphe);
Allele consAlleleVide();
Individu consIndividuVide();
Population consPopulationVide();
ListePopulation consListePopulationvide();
ElementListePopulation* consElementListePopulation();
ListePopulation ajoutListePopulationFin(ListePopulation liste, Individu individu);
Individu consIndividuFonctionnel(int nbAllele);

/* Utilitaires */

void supprimerIndividu(Individu* individu);
void supprimerListePopulation(ListePopulation* liste);
void supprimerPopulation(Population* population);
bool estVideListePopulation(ListePopulation liste);
Individu dupliquerIndividu(Individu individu);

/* Affichage */

void afficherIndividu(Individu individu);
void afficherAllele(Allele allele);
void afficherListePopulation(ListePopulation liste);
void afficherPopulation(Population population);
void afficherIndividuFinal(Individu individu);

/* Génétique */

Population croisements(Population population, float crossesRate, int idBegin);
Population mutations(Population population, float mutationRate);
Graphe appliquerIndividu(Individu individu, Graphe graphe);
Graphe retirerIndividu(Individu individu, Graphe graphe);
float score(GeneticSolver geneticSolver, Individu individu);
Individu majIndividu(GeneticSolver geneticSolver, Individu individu);
Population selection(Population population, int n);
Individu selectionONE(Population population);


#endif
