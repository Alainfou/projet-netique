#include "genetique.h"

/* Constructeurs */

Allele consAlleleVide()
{
    Allele newAllele;
    newAllele.mesure = consMesureVide();
    newAllele.numeroArc = -1;
    newAllele.actif = false;

    return newAllele;
}

Individu consIndividuVide()
{
    Individu newIndividu;
    newIndividu.genome = NULL;
    newIndividu.id = -1;
    newIndividu.nbAllele = -1;
    newIndividu.score = -1;
    newIndividu.lenght = -1;
    newIndividu.budget = -1;

    return newIndividu;
}

Population consPopulationVide()
{
    Population newPopulation;
    newPopulation.taillePopulation = 0;
    newPopulation.listePopulation = consListePopulationvide();

    return newPopulation;
}

ElementListePopulation* consElementListePopulation(Individu individu)
{
    ElementListePopulation* newElement = (ElementListePopulation*)malloc(sizeof(ElementListePopulation));
    if(newElement == NULL)
    {
        perror("Allocation du maillon de chaine (consElementListePopulation) impossible");
        exit(-1);
    }
    newElement->individu = individu;
    newElement->psuivant = NULL;

    return newElement;
}

ListePopulation consListePopulationvide()
{
    ListePopulation newListe;
    newListe.pdebut = NULL;
    newListe.pfin = NULL;

    return newListe;
}

ListePopulation ajoutListePopulationFin(ListePopulation liste, Individu individu)
{
    if(estVideListePopulation(liste))
    {
        liste.pfin = consElementListePopulation(individu);
        liste.pdebut = liste.pfin;
    }
    else
    {
        liste.pfin->psuivant = consElementListePopulation(individu);
        liste.pfin = liste.pfin->psuivant;
    }

    return liste;
}

Individu genererIndividu(int id, Mesures mesures, Graphe graphe)
{
    int i, j;
    ElementListeArc* temp;
    Allele allele = consAlleleVide();
    Individu newIndividu = consIndividuVide();
    newIndividu.id = id;
    newIndividu.nbAllele = mesures.nbMesuresTotales;
    newIndividu.genome = (Allele*)malloc(mesures.nbMesuresTotales*(sizeof(Allele)));
    if(newIndividu.genome == NULL)
    {
        perror("Allocation du genome (genererIndividu) impossible");
        exit(-1);
    }

    for(i = 0; i < newIndividu.nbAllele; i++)
    {
        newIndividu.genome[i] = consAlleleVide();
    }

    j = 0;
    for(i = 0; i < mesures.nbMesure; i++)
    {
        temp = mesures.tabMesure[i].arcApplicables.pdebut;
        while(temp != NULL)
        {
            allele.mesure = mesures.tabMesure[i];
            allele.numeroArc = temp->numeroArc;
            allele.actif = rand()%2;
            newIndividu.genome[j] = allele;
            temp = temp->psuivant;
            j++;
        }
    }
    newIndividu.score = -1;
    newIndividu.lenght = -1;
    newIndividu.budget = -1;

    return newIndividu;
}

Individu consIndividuFonctionnel(int nbAllele)
{
    int i;
    Individu individu = consIndividuVide();
    individu.genome = (Allele*)malloc(nbAllele*(sizeof(Allele)));
    individu.nbAllele = nbAllele;
    if(individu.genome == NULL)
    {
        perror("Allocation du genome (ConsIndividuFonctionnel) impossible");
        exit(-1);
    }
    for(i = 0; i < individu.nbAllele; i++)
    {
        individu.genome[i] = consAlleleVide();
    }
    individu.score = -1;
    individu.lenght = -1;

    return individu;
}

/* Affichage */

void afficherIndividu(Individu individu)
{
    int i;
    printf("Identifiant de l'individu : %d\n", individu.id);
    printf("Nombre d'alleles : %d\n\n", individu.nbAllele);
    printf("Score de l'individu : %f\n", individu.score);
    printf("Longueur de l'individu : %f\n", individu.lenght);
    printf("Cout de l'individu : %f\n\n", individu.budget);

    for(i = 0; i < individu.nbAllele; i++)
    {
        printf("Allele numero : %d\n", i);
        afficherAllele(individu.genome[i]);
        printf("\n\n");
    }
}

void afficherAllele(Allele allele)
{
    afficherMesure(allele.mesure);
    printf("Numero d'arc %d  |%d", allele.numeroArc, allele.actif);
}

void afficherPopulation(Population population)
{
    printf("Taille de la population : %d\n",population.taillePopulation);
    afficherListePopulation(population.listePopulation);
}

void afficherListePopulation(ListePopulation liste)
{
    if(estVideListePopulation(liste))
    {
        printf("Liste vide");
    }
    else
    {
        ElementListePopulation* temp = liste.pdebut;
        while(temp != NULL)
        {
            afficherIndividu(temp->individu);
            printf("\n------------------------------------------------------\n");
            temp = temp -> psuivant;
        }
    }
}

void afficherIndividuFinal(Individu individu)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    printf("\n\nIdentifiant de l'individu : %d\n", individu.id);
    printf("Nombre d'alleles : %d\n\n", individu.nbAllele);
    printf("Score de l'individu : %f\n", individu.score);
    printf("Longueur de l'individu : %f\n", individu.lenght);
    printf("Cout de l'individu : %f\n\n", individu.budget);
    printf("\nMesures finales a appliquer :\n");

    for(i = 0; i < individu.nbAllele; i++)
    {
        if(individu.genome[i].actif)
        {
            tempEffi = individu.genome[i].mesure.efficacite.pdebut;
            tempArc = individu.genome[i].mesure.arcApplicables.pdebut;
            while(tempArc->numeroArc != individu.genome[i].numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            printf("Appliquer la mesure %d sur l'arc %d\n", individu.genome[i].mesure.id, individu.genome[i].numeroArc);
        }
    }
}

/* Utilitaires */

void supprimerIndividu(Individu* individu)
{
    if(individu->genome != NULL)
    {
        free(individu->genome);
        individu->genome = NULL;
    }
    individu->id = -1;
    individu->nbAllele = -1;
    individu->score = -1;
    individu->genome = NULL;
}

bool estVideListePopulation(ListePopulation liste)
{
    return liste.pdebut == NULL;
}

void supprimerPopulation(Population* population)
{
    if(!estVideListePopulation(population->listePopulation))
    {
        supprimerListePopulation(&(population->listePopulation));
    }
    population->taillePopulation = 0;
}

void supprimerListePopulation(ListePopulation* liste)
{
    ElementListePopulation* temp = liste->pdebut;

    if(!estVideListePopulation(*liste))
    {
        while(liste->pdebut != NULL)
        {
            temp = liste->pdebut;
            supprimerIndividu(&temp->individu);
            liste->pdebut = liste->pdebut->psuivant;
            free(temp);
        }
    }

    liste->pdebut = liste->pfin = NULL;
}

Individu dupliquerIndividu(Individu individu)
{
    Individu clone;
    int i;
    clone = individu;
    clone.genome = (Allele*)malloc(individu.nbAllele*(sizeof(Allele)));
    if(clone.genome == NULL)
    {
        perror("Clone impossible (dupliquerIndividu)");
        exit(-1);
    }
    for(i = 0; i < individu.nbAllele; i++)
    {
        clone.genome[i] = individu.genome[i];
    }
    return clone;
}


/* Génétique */

Population croisements(Population population, float crossesRate, int idBegin)
{
    int i, j, k;
    int cross_rate = (int)(ceil(population.taillePopulation*crossesRate/2));
    Individu fils = consIndividuVide();
    Individu fille = consIndividuVide();
    int pere = -1;
    int mere = -1;
    int nbAllele = -1;
    ListeArc listeTempTransformation = consListeVide();
    ListeArc listeTempTransformation2 = consListeVide();
    ElementListeArc* suppression1 = NULL;
    ElementListeArc* position1 = NULL;
    ElementListeArc* suppression2 = NULL;
    ElementListeArc* position2 = NULL;
    ElementListePopulation* pPere = NULL;
    ElementListePopulation* pMere = NULL;
    int cpt = -1;
    int random1, random2;
    random1 = random2 = -1;

    if(population.taillePopulation < 2)
    {
        perror("La population doit contenir au moins deux individus (croisements)");
        exit(-1);
    }

    nbAllele = population.listePopulation.pdebut->individu.nbAllele;

    for(i = 0; i < cross_rate; i++)
    {
        pere = random_number(0,population.taillePopulation - 1);
        //On vérifie que le père et la mère ne sont pas le même individu
        do
        {
            mere = random_number(0,population.taillePopulation - 1);
        }while(pere == mere);

        //On récupère le père et la mère dans la population
        pPere = population.listePopulation.pdebut;
        for(j = 0; j < pere; j++)
        {
            pPere = pPere->psuivant;
        }

        pMere = population.listePopulation.pdebut;
        for(j = 0; j < mere; j++)
        {
            pMere = pMere->psuivant;
        }

        //On créé un fils et une fille
        for(j = 0; j < nbAllele; j++)
        {
            listeTempTransformation = ajoutListeFin(listeTempTransformation, j);
            listeTempTransformation2 = ajoutListeFin(listeTempTransformation2, j);
        }

        //Création d'un compteur pour les enfants
        cpt = 0;

        //On construit les enfants
        fils = consIndividuFonctionnel(nbAllele);
        fille = consIndividuFonctionnel(nbAllele);

        fils.id = idBegin;
        idBegin++;
        fille.id = idBegin;
        idBegin++;

        //On croise tous les alleles
        for(k = 0; k < nbAllele; k++)
        {
            //On tire au hasard un numéro de la liste
            random1 = random_number(0,nbAllele - cpt - 1);
            random2 = random_number(0,nbAllele - cpt - 1);

            //On atteint ce maillon pour le supprimer
            position1 = suppression1 = listeTempTransformation.pdebut;
            for(j = 0; j < random1; j++)
            {
                suppression1 = position1;
                position1 = position1 ->psuivant;
            }

            position2 = suppression2 = listeTempTransformation2.pdebut;
            for(j = 0; j < random2; j++)
            {
                suppression2 = position2;
                position2 = position2->psuivant;
            }

            if(k%2 == 0)
            {
                //On procède à un croisement
                fils.genome[cpt] = pPere->individu.genome[position1->numeroArc];

                fille.genome[cpt] = pMere->individu.genome[position2->numeroArc];
            }
            else
            {
                //Sinon on procède à un autre croisement
                fils.genome[cpt] = pMere->individu.genome[position1->numeroArc];

                fille.genome[cpt] = pPere->individu.genome[position2->numeroArc];
            }
            cpt++;

            //On supprime les maillons temporaires
            if(position1 == listeTempTransformation.pdebut)
            {
                listeTempTransformation.pdebut = listeTempTransformation.pdebut->psuivant;
            }
            else
            {
                suppression1->psuivant = position1->psuivant;
            }
            free(position1);
            position1 = suppression1 = NULL;

            if(position2 == listeTempTransformation2.pdebut)
            {
                listeTempTransformation2.pdebut = listeTempTransformation2.pdebut->psuivant;
            }
            else
            {
                suppression2->psuivant = position2->psuivant;
            }
            free(position2);
            position2 = suppression2 = NULL;
        }
        supprimerListe(&listeTempTransformation);
        supprimerListe(&listeTempTransformation2);

        //Et on finit par ajouter les nouveaux individus à la population
        population.listePopulation = ajoutListePopulationFin(population.listePopulation,fils);
        population.taillePopulation++;
        population.listePopulation = ajoutListePopulationFin(population.listePopulation,fille);
        population.taillePopulation++;
    }
    return population;
}

Population mutations(Population population, float mutationRate)
{
    int i, j, k, n, m, random;
    Individu* aMuter = NULL;
    int nbAllele = -1;
    ListeArc listeTempIndividu = consListeVide();
    ListeArc listeTempAlelle = consListeVide();
    ElementListeArc* positionIndividu = NULL;
    ElementListeArc* positionAllele = NULL;
    ElementListeArc* supprimerIndividu = NULL;
    ElementListeArc* supprimerAllele = NULL;
    ElementListePopulation* pIndividu = NULL;

    if(population.taillePopulation < 1)
    {
        perror("La population doit avoir au moins un element(mutation)");
        exit(-1);
    }

    //On récupère le nombre d'alleles
    nbAllele = population.listePopulation.pdebut->individu.nbAllele;

    //On calcul les taux de mutations
    n = (int)(ceil(population.taillePopulation*mutationRate));
    m = (int)(ceil(population.listePopulation.pdebut->individu.nbAllele*mutationRate));

    //On initialise la liste temporaire des individus
    for(i = 0; i < population.taillePopulation; i++)
    {
        listeTempIndividu = ajoutListeFin(listeTempIndividu, i);
    }

    //Boucle qui choisit les individus de manière aléatoire
    for(i = 0; i < n; i++)
    {
        //On recuperer l'individu qui doit muter
        random = random_number(0, population.taillePopulation - i - 1);
        pIndividu = population.listePopulation.pdebut;
        positionIndividu = supprimerIndividu = listeTempIndividu.pdebut;
        for(j = 0; j < random; j++)
        {
            supprimerIndividu = positionIndividu;
            positionIndividu = positionIndividu->psuivant;
            pIndividu = pIndividu->psuivant;
        }

        //On créé un pointeur dessus
        aMuter = &pIndividu->individu;

        //On initialise la liste sans doublon pour les alleles
        for(j = 0; j < nbAllele; j++)
        {
            listeTempAlelle = ajoutListeFin(listeTempAlelle, j);
        }

        for(j = 0; j < m; j++)
        {
            random = random_number(0, nbAllele - 1 - j);
            positionAllele = supprimerAllele = listeTempAlelle.pdebut;
            for(k = 0; k < random; k++)
            {
                supprimerAllele = positionAllele;
                positionAllele = positionAllele->psuivant;
            }

            //On mute
            aMuter->genome[positionAllele->numeroArc].actif = !aMuter->genome[positionAllele->numeroArc].actif;

            //On supprime le maillon

            if(positionAllele == listeTempAlelle.pdebut)
            {
                listeTempAlelle.pdebut = listeTempAlelle.pdebut->psuivant;
            }
            else
            {
                supprimerAllele->psuivant = positionAllele->psuivant;
            }
            free(positionAllele);
            positionAllele = supprimerAllele = NULL;
        }
        supprimerListe(&listeTempAlelle);

        //On supprime le maillon
        if(positionIndividu == listeTempIndividu.pdebut)
        {
            listeTempIndividu.pdebut = listeTempIndividu.pdebut->psuivant;
        }
        else
        {
            supprimerIndividu->psuivant = positionIndividu->psuivant;
        }
        free(positionIndividu);
        positionIndividu = supprimerIndividu = NULL;
    }
    supprimerListe(&listeTempIndividu);
    return population;
}

Graphe appliquerIndividu(Individu individu, Graphe graphe)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    int numArcApplicable;
    for(i = 0; i < individu.nbAllele; i++)
    {
        if(individu.genome[i].actif)
        {
            numArcApplicable = individu.genome[i].numeroArc;
            tempEffi = individu.genome[i].mesure.efficacite.pdebut;
            tempArc = individu.genome[i].mesure.arcApplicables.pdebut;
            while(numArcApplicable != tempArc->numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            graphe.tabArcs[individu.genome[i].numeroArc].ponderation += tempEffi->numeroArc;
            graphe.tabArcs[individu.genome[i].numeroArc].cout += individu.genome[i].mesure.cout;
        }
    }
    return graphe;
}
Graphe retirerIndividu(Individu individu, Graphe graphe)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    int numArcApplicable;
    for(i = 0; i < individu.nbAllele; i++)
    {
        if(individu.genome[i].actif)
        {
            numArcApplicable = individu.genome[i].numeroArc;
            tempEffi = individu.genome[i].mesure.efficacite.pdebut;
            tempArc = individu.genome[i].mesure.arcApplicables.pdebut;
            while(numArcApplicable != tempArc->numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            graphe.tabArcs[individu.genome[i].numeroArc].ponderation -= tempEffi->numeroArc;
            graphe.tabArcs[individu.genome[i].numeroArc].cout -= individu.genome[i].mesure.cout;
        }
    }
    return graphe;
}

float score(GeneticSolver geneticSolver, Individu individu)
{
    return geneticSolver.ratioPriority * individu.lenght + (1 - geneticSolver.ratioPriority) * (100 - individu.budget / geneticSolver.targetBudget * 100);
}

Individu majIndividu(GeneticSolver geneticSolver, Individu individu)
{
    int i, somme;
    if(individu.genome != NULL)
    {
        somme = 0;
        for(i = 0; i < individu.nbAllele; i++)
        {
            somme += individu.genome[i].actif * individu.genome[i].mesure.cout;
        }
        individu.budget = somme;
    }
    individu.score = score(geneticSolver, individu);
    return individu;
}

Population selection(Population population, int n)
{
    ElementListePopulation* tabTemp[population.taillePopulation];
    bool tabMarq[population.taillePopulation];
    ElementListePopulation* temp = population.listePopulation.pdebut;
    ListePopulation newPopulation = consListePopulationvide();
    int i = 0;
    int j;
    float scoreMax;
    int max;
    while(temp != NULL)
    {
        tabTemp[i] = temp;
        tabMarq[i] = false;
        temp = temp->psuivant;
        i++;
    }
    //On détache la liste de la population
    population.listePopulation = consListePopulationvide();
    population.taillePopulation = n;
    for(i = 0; i < n; i++)
    {
        scoreMax  = -1;
        max = 0;
        for(j = 0; j < population.taillePopulation; j++)
        {
            if(tabTemp[j]->individu.score > scoreMax && tabMarq[j] == false)
            {
                max = j;
                scoreMax = tabTemp[j]->individu.score;
            }
        }
        tabMarq[max] = true;
        newPopulation = ajoutListePopulationFin(newPopulation, tabTemp[max]->individu);
    }

    for(i = 0; i < n; i++)
    {
        if(tabMarq[i] == false)
        {
            supprimerIndividu(&tabTemp[i]->individu);
            free(tabTemp[i]);
        }
    }
    population.listePopulation = newPopulation;
    return population;
}

Individu selectionONE(Population population)
{
    ElementListePopulation* temp = population.listePopulation.pdebut;
    Individu garde = temp->individu;
    while(temp != NULL)
    {
        if(temp->individu.score > garde.score)
        {
            garde = temp->individu;
        }
        temp = temp->psuivant;
    }

    return garde;
}
