#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genetique.h"

#define TAILLEPOPULATION 100

int menu()
{
   
    printf("			MENU	");
    printf("		1) Construire votre graphe et vos mesures manuellement \n");
    printf("		2) Utiliser notre graphe et mesures par defaut\n");
    printf("		3) Quitter\n");
    printf("Votre choix : ");
    return secure_INTMinMax(1,3);
}

Graphe grapheTest()
{
    //Création d'un graphe de test pour que les utilisateurs qui n'ont pas de graphe
    //puissent tester le logiciel
    int i;
    Graphe graphe = consGrapheVide();

    //Nombre d'arcs et de noeuds
    graphe.nbArc = 16;
    graphe.nbNoeuds = 12;

    //On créé le graphe dynamiquement et on vérifie que l'allocation s'est déroulée correctement
    graphe.tabNoeuds = (Noeud*)malloc(graphe.nbNoeuds*(sizeof(Noeud)));
    if(graphe.tabNoeuds == NULL)
    {
        perror("Allocation du tableau de noeuds (grapheTest) impossible");
        exit(-1);
    }

    graphe.tabArcs = (Arc*)malloc(graphe.nbArc*(sizeof(Arc)));
    if(graphe.tabArcs == NULL)
    {
        if(graphe.tabArcs != NULL)
        {
            free(graphe.tabArcs);
        }
        perror("Allocation du tableau d'arcs (grapheTest) impossible");
        exit(-1);
    }

    //On initialise le graphe a vide
    for(i = 0; i < graphe.nbNoeuds; i++)
    {
        graphe.tabNoeuds[i] = consNoeudVide();
    }

    for(i = 0; i < graphe.nbArc; i++)
    {
        graphe.tabArcs[i] = consArcVide();
    }

    //Initialisation des successeurs

    //Successeurs de 0
    graphe.tabNoeuds[0].listeSuiv = ajoutListeFin(graphe.tabNoeuds[0].listeSuiv, 0);
    graphe.tabNoeuds[0].listeSuiv = ajoutListeFin(graphe.tabNoeuds[0].listeSuiv, 1);
    graphe.tabNoeuds[0].listeSuiv = ajoutListeFin(graphe.tabNoeuds[0].listeSuiv, 11);

    //Successeurs de 1
    graphe.tabNoeuds[1].listeSuiv = ajoutListeFin(graphe.tabNoeuds[1].listeSuiv, 2);
    graphe.tabNoeuds[1].listeSuiv = ajoutListeFin(graphe.tabNoeuds[1].listeSuiv, 3);

    //Successeurs de 2
    graphe.tabNoeuds[2].listeSuiv = ajoutListeFin(graphe.tabNoeuds[2].listeSuiv, 4);

    //Successeurs de 3
    graphe.tabNoeuds[3].listeSuiv = ajoutListeFin(graphe.tabNoeuds[3].listeSuiv, 12);

    //Successeurs de 4
    graphe.tabNoeuds[4].listeSuiv = ajoutListeFin(graphe.tabNoeuds[4].listeSuiv, 6);
    graphe.tabNoeuds[4].listeSuiv = ajoutListeFin(graphe.tabNoeuds[4].listeSuiv, 7);

    //Successeurs de 5
    graphe.tabNoeuds[5].listeSuiv = ajoutListeFin(graphe.tabNoeuds[5].listeSuiv, 5);
    graphe.tabNoeuds[5].listeSuiv = ajoutListeFin(graphe.tabNoeuds[5].listeSuiv, 8);

    //Successeurs de 6
    graphe.tabNoeuds[6].listeSuiv = ajoutListeFin(graphe.tabNoeuds[6].listeSuiv, 9);
    graphe.tabNoeuds[6].listeSuiv = ajoutListeFin(graphe.tabNoeuds[6].listeSuiv, 15);

    //Successeurs de 7
    graphe.tabNoeuds[7].listeSuiv = ajoutListeFin(graphe.tabNoeuds[7].listeSuiv, 13);

    //Successeurs de 8
    graphe.tabNoeuds[8].listeSuiv = ajoutListeFin(graphe.tabNoeuds[8].listeSuiv, 14);

    //Successeurs de 9
    graphe.tabNoeuds[9].listeSuiv = ajoutListeFin(graphe.tabNoeuds[9].listeSuiv, 10);

    //Successeurs de 10
    //Pas de successeur

    //Successeurs de 11
    //Pas de successeur


    //Initialisation des prédécesseurs

    //Prédécesseurs de 0
    //Pas de prédécesseur => premier noeud du graphe

    //Prédécesseurs de 1
    graphe.tabNoeuds[1].listePrec = ajoutListeFin(graphe.tabNoeuds[1].listePrec, 0);

    //Prédécesseurs de 2
    graphe.tabNoeuds[2].listePrec = ajoutListeFin(graphe.tabNoeuds[2].listePrec, 1);

    //Prédécesseurs de 3
    graphe.tabNoeuds[3].listePrec = ajoutListeFin(graphe.tabNoeuds[3].listePrec, 11);

    //Prédécesseurs de 4
    graphe.tabNoeuds[4].listePrec = ajoutListeFin(graphe.tabNoeuds[4].listePrec, 2);

    //Prédécesseurs de 5
    graphe.tabNoeuds[5].listePrec = ajoutListeFin(graphe.tabNoeuds[5].listePrec, 3);

    //Prédécesseurs de 6
    graphe.tabNoeuds[6].listePrec = ajoutListeFin(graphe.tabNoeuds[6].listePrec, 4);
    graphe.tabNoeuds[6].listePrec = ajoutListeFin(graphe.tabNoeuds[6].listePrec, 5);

    //Prédécesseurs de 7
    graphe.tabNoeuds[7].listePrec = ajoutListeFin(graphe.tabNoeuds[7].listePrec, 6);
    graphe.tabNoeuds[7].listePrec = ajoutListeFin(graphe.tabNoeuds[7].listePrec, 12);

    //Prédécesseurs de 8
    graphe.tabNoeuds[8].listePrec = ajoutListeFin(graphe.tabNoeuds[8].listePrec, 7);
    graphe.tabNoeuds[8].listePrec = ajoutListeFin(graphe.tabNoeuds[8].listePrec, 10);

    //Prédécesseurs de 9
    graphe.tabNoeuds[9].listePrec = ajoutListeFin(graphe.tabNoeuds[9].listePrec, 8);
    graphe.tabNoeuds[9].listePrec = ajoutListeFin(graphe.tabNoeuds[9].listePrec, 9);

    //Prédécesseurs de 10
    graphe.tabNoeuds[10].listePrec = ajoutListeFin(graphe.tabNoeuds[10].listePrec, 13);
    graphe.tabNoeuds[10].listePrec = ajoutListeFin(graphe.tabNoeuds[10].listePrec, 14);

    //Prédécesseurs de 11
    graphe.tabNoeuds[11].listePrec = ajoutListeFin(graphe.tabNoeuds[11].listePrec, 15);

    //Initialisation des arcs

    graphe.tabArcs[0].noeudDepart = 0;
    graphe.tabArcs[0].noeudArrive = 1;

    graphe.tabArcs[1].noeudDepart = 0;
    graphe.tabArcs[1].noeudArrive = 2;

    graphe.tabArcs[2].noeudDepart = 1;
    graphe.tabArcs[2].noeudArrive = 4;

    graphe.tabArcs[3].noeudDepart = 1;
    graphe.tabArcs[3].noeudArrive = 5;

    graphe.tabArcs[4].noeudDepart = 2;
    graphe.tabArcs[4].noeudArrive = 6;

    graphe.tabArcs[5].noeudDepart = 5;
    graphe.tabArcs[5].noeudArrive = 6;

    graphe.tabArcs[6].noeudDepart = 4;
    graphe.tabArcs[6].noeudArrive = 7;

    graphe.tabArcs[7].noeudDepart = 4;
    graphe.tabArcs[7].noeudArrive = 8;

    graphe.tabArcs[8].noeudDepart = 5;
    graphe.tabArcs[8].noeudArrive = 9;

    graphe.tabArcs[9].noeudDepart = 6;
    graphe.tabArcs[9].noeudArrive = 9;

    graphe.tabArcs[10].noeudDepart = 9;
    graphe.tabArcs[10].noeudArrive = 8;

    graphe.tabArcs[11].noeudDepart = 0;
    graphe.tabArcs[11].noeudArrive = 3;

    graphe.tabArcs[12].noeudDepart = 3;
    graphe.tabArcs[12].noeudArrive = 7;

    graphe.tabArcs[13].noeudDepart = 7;
    graphe.tabArcs[13].noeudArrive = 10;

    graphe.tabArcs[14].noeudDepart = 8;
    graphe.tabArcs[14].noeudArrive = 10;

    graphe.tabArcs[15].noeudDepart = 6;
    graphe.tabArcs[15].noeudArrive = 11;

    //Ajout des pondérations sur les arcs

    graphe.tabArcs[0].ponderation = 0;
    graphe.tabArcs[1].ponderation = 5;
    graphe.tabArcs[2].ponderation = 10;
    graphe.tabArcs[3].ponderation = 40;
    graphe.tabArcs[4].ponderation = 5;
    graphe.tabArcs[5].ponderation = 20;
    graphe.tabArcs[6].ponderation = 50;
    graphe.tabArcs[7].ponderation = 50;
    graphe.tabArcs[8].ponderation = 0;
    graphe.tabArcs[9].ponderation = 40;
    graphe.tabArcs[10].ponderation = 10;
    graphe.tabArcs[11].ponderation = 55;
    graphe.tabArcs[12].ponderation = 0;
    graphe.tabArcs[13].ponderation = 0;
    graphe.tabArcs[14].ponderation = 10;
    graphe.tabArcs[15].ponderation = 50;

    //Initialisation à 0 du coût des arcs
    for(i = 0; i < graphe.nbArc; i++)
    {
        graphe.tabArcs[i].cout = 0;
    }

    return graphe;
}

Mesures mesuresTest()
{
    Mesure mesure1 = consMesureVide();
    Mesure mesure2 = consMesureVide();
    Mesure mesure3 = consMesureVide();
    Mesure mesure4 = consMesureVide();
    Mesure mesure5 = consMesureVide();
    Mesure mesure6 = consMesureVide();
    Mesure mesure7 = consMesureVide();
    Mesure mesure8 = consMesureVide();
    Mesure mesure9 = consMesureVide();
    Mesure mesure10 = consMesureVide();
    Mesures mesures = consMesuresVide();

    //Nombre de mesures et nombre total de mesures (une mesure par arc, plusieurs arcs)
    mesures.nbMesure = 10;
    mesures.nbMesuresTotales = 18;
    mesures.tabMesure = (Mesure*)malloc(mesures.nbMesure*(sizeof(Mesure)));
    if(mesures.tabMesure == NULL)
    {
        perror("Allocation du tableau de mesures (mesuresTest) impossible");
        exit(-1);
    }

    //Arcs sur lesquels s'appliquent les mesures

    //Mesure 1
    mesure1.arcApplicables = ajoutListeFin(mesure1.arcApplicables, 0);

    //Mesure 2
    mesure2.arcApplicables = ajoutListeFin(mesure2.arcApplicables, 0);
    mesure2.arcApplicables = ajoutListeFin(mesure2.arcApplicables, 1);

    //Mesure 3
    mesure3.arcApplicables = ajoutListeFin(mesure3.arcApplicables, 2);
    mesure3.arcApplicables = ajoutListeFin(mesure3.arcApplicables, 3);

    //Mesure 4
    mesure4.arcApplicables = ajoutListeFin(mesure4.arcApplicables, 4);
    mesure4.arcApplicables = ajoutListeFin(mesure4.arcApplicables, 5);

    //Mesure 5
    mesure5.arcApplicables = ajoutListeFin(mesure5.arcApplicables, 6);

    //Mesure 6
    mesure6.arcApplicables = ajoutListeFin(mesure6.arcApplicables, 2);
    mesure6.arcApplicables = ajoutListeFin(mesure6.arcApplicables, 7);
    mesure6.arcApplicables = ajoutListeFin(mesure6.arcApplicables, 6);

    //Mesure 7
    mesure7.arcApplicables = ajoutListeFin(mesure7.arcApplicables, 8);
    mesure7.arcApplicables = ajoutListeFin(mesure7.arcApplicables, 9);
    mesure7.arcApplicables = ajoutListeFin(mesure7.arcApplicables, 10);

    //Mesure 8
    mesure8.arcApplicables = ajoutListeFin(mesure8.arcApplicables, 12);

    //Mesure 9
    mesure9.arcApplicables = ajoutListeFin(mesure9.arcApplicables, 11);
    mesure9.arcApplicables = ajoutListeFin(mesure9.arcApplicables, 1);

    //Mesure 10
    mesure10.arcApplicables = ajoutListeFin(mesure10.arcApplicables, 15);

    mesure1.id = 1;
    mesure2.id = 2;
    mesure3.id = 3;
    mesure4.id = 4;
    mesure5.id = 5;
    mesure6.id = 6;
    mesure7.id = 7;
    mesure8.id = 8;
    mesure9.id = 9;
    mesure10.id = 10;

    //Coût de ces mesures
    mesure1.cout = 30;
    mesure2.cout= 10;
    mesure3.cout = 20;
    mesure4.cout = 5;
    mesure5.cout = 40;
    mesure6.cout = 25;
    mesure7.cout = 15;
    mesure8.cout = 35;
    mesure9.cout = 200;
    mesure10.cout = 40;


    //Remplissage de l'efficacité des mesures
    //Mesure 1
    mesure1.efficacite = ajoutListeFin(mesure1.efficacite, 50);

    //Mesure 2
    mesure2.efficacite = ajoutListeFin(mesure2.efficacite, 20);
    mesure2.efficacite = ajoutListeFin(mesure2.efficacite, 25);

    //Mesure 3
    mesure3.efficacite = ajoutListeFin(mesure3.efficacite, 15);
    mesure3.efficacite = ajoutListeFin(mesure3.efficacite, 40);

    //Mesure 4
    mesure4.efficacite = ajoutListeFin(mesure4.efficacite, 60);
    mesure4.efficacite = ajoutListeFin(mesure4.efficacite, 25);

    //Mesure 5
    mesure5.efficacite = ajoutListeFin(mesure5.efficacite, 50);

    //Mesure 6
    mesure6.efficacite = ajoutListeFin(mesure6.efficacite, 30);
    mesure6.efficacite = ajoutListeFin(mesure6.efficacite, 30);
    mesure6.efficacite = ajoutListeFin(mesure6.efficacite, 30);

    //Mesure 7
    mesure7.efficacite = ajoutListeFin(mesure7.efficacite, 20);
    mesure7.efficacite = ajoutListeFin(mesure7.efficacite, 20);
    mesure7.efficacite = ajoutListeFin(mesure7.efficacite, 20);

    //Mesure 8
    mesure8.efficacite = ajoutListeFin(mesure8.efficacite, 70);

    //Mesure 9
    mesure9.efficacite = ajoutListeFin(mesure9.efficacite, 100);
    mesure9.efficacite = ajoutListeFin(mesure9.efficacite, 100);

    //Mesure 10
    mesure10.efficacite = ajoutListeFin(mesure10.efficacite, 40);

    //Ajout des mesures dans le tableau les regroupant
    mesures.tabMesure[0] = mesure1;
    mesures.tabMesure[1] = mesure2;
    mesures.tabMesure[2] = mesure3;
    mesures.tabMesure[3] = mesure4;
    mesures.tabMesure[4] = mesure5;
    mesures.tabMesure[5] = mesure6;
    mesures.tabMesure[6] = mesure7;
    mesures.tabMesure[7] = mesure8;
    mesures.tabMesure[8] = mesure9;
    mesures.tabMesure[9] = mesure10;

    return mesures;
}

Personne personneTest(Mesures mesure, Graphe graphe, int id)
{
    Personne personne = consPersonneVide();
    personne = genererPersonne(id, mesure, graphe);
    return personne;
}

Population populationTest(Mesures mesure, Graphe graphe)
{
    int i;
    Population population = consPopulationVide();
    population.taillePopulation = TAILLEPOPULATION;

    for(i = 0; i < population.taillePopulation; i++)
    {
        population.listePopulation = ajoutListePopulationFin(population.listePopulation, personneTest(mesure, graphe, i));
    }

    return population;
}

Personne testerInd()
{
    Personne testerInd = consPersonneFonctionnel(2);
    testerInd.genome[0].actif = true;
    testerInd.genome[1].actif = true;
    testerInd.genome[0].numeroArc = 1;
    testerInd.genome[1].numeroArc = 11;
    testerInd.genome[0].mesure.cout = 200;
    testerInd.genome[1].mesure.cout = 200;
    testerInd.genome[0].mesure.efficacite = consListeVide();
    testerInd.genome[1].mesure.efficacite = consListeVide();
    testerInd.genome[0].mesure.efficacite = ajoutListeFin(testerInd.genome[0].mesure.efficacite, 100);
    testerInd.genome[0].mesure.efficacite = ajoutListeFin(testerInd.genome[0].mesure.efficacite, 100);
    testerInd.genome[1].mesure.efficacite = ajoutListeFin(testerInd.genome[1].mesure.efficacite, 100);
    testerInd.genome[1].mesure.efficacite = ajoutListeFin(testerInd.genome[1].mesure.efficacite, 100);
    testerInd.genome[0].mesure.arcApplicables = consListeVide();
    testerInd.genome[1].mesure.arcApplicables = consListeVide();
    testerInd.genome[0].mesure.arcApplicables = ajoutListeFin(testerInd.genome[0].mesure.arcApplicables, 1);
    testerInd.genome[0].mesure.arcApplicables = ajoutListeFin(testerInd.genome[0].mesure.arcApplicables, 11);
    testerInd.genome[1].mesure.arcApplicables = ajoutListeFin(testerInd.genome[1].mesure.arcApplicables, 1);
    testerInd.genome[1].mesure.arcApplicables = ajoutListeFin(testerInd.genome[1].mesure.arcApplicables, 11);
    return testerInd;
}

void programme()
{
    srand(time(NULL));
    int max = 2000;
    int i = 1;
    int choix = 0;
    int id;
    Personne theBest = consPersonneVide();
    Personne pretendToTheBest = consPersonneVide();
    ElementListePopulation* temp = NULL;
    ListeArc testShortestPath = consListeVide();
    Graphe graphe = consGrapheVide();
    Mesures mesures = consMesuresVide();
    Population population = consPopulationVide();

    GeneticSolver geneticSolver;
    geneticSolver.crossesRate = 0.25;
    geneticSolver.mutationRate = 0.25;
    geneticSolver.ratioPriority = 0.75;
    geneticSolver.targetBudget = 300;

    choix = menu();

    if(choix == 1)
    {
        graphe = consGrapheManuel();
        mesures = consMesuresManuel(graphe.nbArc);
        printf("\n\n Choix du budget : ");
        geneticSolver.targetBudget = secure_INTMin(0);
    }

    if(choix == 2)
    {

        graphe = grapheTest();
        mesures = mesuresTest();
    }

    if(choix == 3)
    {
        exit(0);
    }

    graphe = decomposition(graphe);
    population = populationTest(mesures, graphe);


    //Croisements et mutations
    //On calcule le plus court chemin, on met à jour les personnes
    //On supprime les personnes du graphe

    id = 2;
    while(i < max)
    {
        population = croisements(population, geneticSolver.crossesRate, i*population.taillePopulation + id);
        population = mutations(population, geneticSolver.mutationRate);
        temp = population.listePopulation.pdebut;
        while(temp != NULL)
        {
            appliquerPersonne(temp->personne, graphe);
            testShortestPath = plusCourtChemin(graphe);
            if(testShortestPath.pdebut->numeroArc <= 100)
            {
                temp->personne.lenght = testShortestPath.pdebut->numeroArc;
            }
            else
            {
                temp->personne.lenght = 100;
            }
            temp->personne = majPersonne(geneticSolver, temp->personne);
            supprimerListe(&testShortestPath);
            retirerPersonne(temp->personne, graphe);
            temp = temp->psuivant;
        }

        population = selection(population, TAILLEPOPULATION);
        pretendToTheBest = selectionONE(population);

        if(pretendToTheBest.score > theBest.score)
        {
            supprimerPersonne(&theBest);
            theBest = dupliquerPersonne(pretendToTheBest);
        }

        i++;
    }

    afficherPersonneFinal(theBest);

    //Suppression
    supprimerPersonne(&theBest);
    supprimerGraphe(&graphe);
    supprimerMesures(&mesures);
    supprimerPopulation(&population);

    printf("Appuyer sur une touche pour terminer\n");
    i = getchar();
}

int main(int argc, char* argv[])
{
    programme();
    exit(0);
}
