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

Personne consPersonneVide()
{
    Personne newPersonne;
    newPersonne.genome = NULL;
    newPersonne.id = -1;
    newPersonne.nbAllele = -1;
    newPersonne.score = -1;
    newPersonne.lenght = -1;
    newPersonne.budget = -1;

    return newPersonne;
}

Population consPopulationVide()
{
    Population newPopulation;
    newPopulation.taillePopulation = 0;
    newPopulation.listePopulation = consListePopulationvide();

    return newPopulation;
}

ElementListePopulation* consElementListePopulation(Personne personne)
{
    ElementListePopulation* newElement = (ElementListePopulation*)malloc(sizeof(ElementListePopulation));
    if(newElement == NULL)
    {
        perror("Allocation du maillon de chaine (consElementListePopulation) impossible");
        exit(-1);
    }
    newElement->personne = personne;
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

ListePopulation ajoutListePopulationFin(ListePopulation liste, Personne personne)
{
    if(estVideListePopulation(liste))
    {
        liste.pfin = consElementListePopulation(personne);
        liste.pdebut = liste.pfin;
    }
    else
    {
        liste.pfin->psuivant = consElementListePopulation(personne);
        liste.pfin = liste.pfin->psuivant;
    }

    return liste;
}

Personne genererPersonne(int id, Mesures mesures, Graphe graphe)
{
    int i, j;
    ElementListeArc* temp;
    Allele allele = consAlleleVide();
    Personne newPersonne = consPersonneVide();
    newPersonne.id = id;
    newPersonne.nbAllele = mesures.nbMesuresTotales;
    newPersonne.genome = (Allele*)malloc(mesures.nbMesuresTotales*(sizeof(Allele)));
    if(newPersonne.genome == NULL)
    {
        perror("Allocation du genome (genererPersonne) impossible");
        exit(-1);
    }

    for(i = 0; i < newPersonne.nbAllele; i++)
    {
        newPersonne.genome[i] = consAlleleVide();
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
            newPersonne.genome[j] = allele;
            temp = temp->psuivant;
            j++;
        }
    }
    newPersonne.score = -1;
    newPersonne.lenght = -1;
    newPersonne.budget = -1;

    return newPersonne;
}

Personne consPersonneFonctionnel(int nbAllele)
{
    int i;
    Personne personne = consPersonneVide();
    personne.genome = (Allele*)malloc(nbAllele*(sizeof(Allele)));
    personne.nbAllele = nbAllele;
    if(personne.genome == NULL)
    {
        perror("Allocation du genome (ConsPersonneFonctionnel) impossible");
        exit(-1);
    }
    for(i = 0; i < personne.nbAllele; i++)
    {
        personne.genome[i] = consAlleleVide();
    }
    personne.score = -1;
    personne.lenght = -1;

    return personne;
}

/* Affichage */

void afficherPersonne(Personne personne)
{
    int i;
    printf("Identifiant de la personne : %d\n", personne.id);
    printf("Nombre d'alleles : %d\n\n", personne.nbAllele);
    printf("Score de la personne : %f\n", personne.score);
    printf("Longueur de la personne : %f\n", personne.lenght);
    printf("Cout de la personne : %f\n\n", personne.budget);

    for(i = 0; i < personne.nbAllele; i++)
    {
        printf("Allele numero : %d\n", i);
        afficherAllele(personne.genome[i]);
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
            afficherPersonne(temp->personne);
            printf("\n------------------------------------------------------\n");
            temp = temp -> psuivant;
        }
    }
}

void afficherPersonneFinal(Personne personne)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    printf("\n\nIdentifiant de la personne : %d\n", personne.id);
    printf("Nombre d'alleles : %d\n\n", personne.nbAllele);
    printf("Score de la personne : %f\n", personne.score);
    printf("Longueur de la personne : %f\n", personne.lenght);
    printf("Cout de la personne : %f\n\n", personne.budget);
    printf("\nMesures finales a appliquer :\n");

    for(i = 0; i < personne.nbAllele; i++)
    {
        if(personne.genome[i].actif)
        {
            tempEffi = personne.genome[i].mesure.efficacite.pdebut;
            tempArc = personne.genome[i].mesure.arcApplicables.pdebut;
            while(tempArc->numeroArc != personne.genome[i].numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            printf("Appliquer la mesure %d sur l'arc %d\n", personne.genome[i].mesure.id, personne.genome[i].numeroArc);
        }
    }
}

/* Utilitaires */

void supprimerPersonne(Personne* personne)
{
    if(personne->genome != NULL)
    {
        free(personne->genome);
        personne->genome = NULL;
    }
    personne->id = -1;
    personne->nbAllele = -1;
    personne->score = -1;
    personne->genome = NULL;
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
            supprimerPersonne(&temp->personne);
            liste->pdebut = liste->pdebut->psuivant;
            free(temp);
        }
    }

    liste->pdebut = liste->pfin = NULL;
}

Personne dupliquerPersonne(Personne personne)
{
    Personne clone;
    int i;
    clone = personne;
    clone.genome = (Allele*)malloc(personne.nbAllele*(sizeof(Allele)));
    if(clone.genome == NULL)
    {
        perror("Clone impossible (dupliquerPersonne)");
        exit(-1);
    }
    for(i = 0; i < personne.nbAllele; i++)
    {
        clone.genome[i] = personne.genome[i];
    }
    return clone;
}


/* Génétique */

Population croisements(Population population, float crossesRate, int idBegin)
{
    int i, j, k;
    int cross_rate = (int)(ceil(population.taillePopulation*crossesRate/2));
    Personne fils = consPersonneVide();
    Personne fille = consPersonneVide();
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
        perror("La population doit contenir au moins deux personnes (croisements)");
        exit(-1);
    }

    nbAllele = population.listePopulation.pdebut->personne.nbAllele;

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
        fils = consPersonneFonctionnel(nbAllele);
        fille = consPersonneFonctionnel(nbAllele);

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
                fils.genome[cpt] = pPere->personne.genome[position1->numeroArc];

                fille.genome[cpt] = pMere->personne.genome[position2->numeroArc];
            }
            else
            {
                //Sinon on procède à un autre croisement
                fils.genome[cpt] = pMere->personne.genome[position1->numeroArc];

                fille.genome[cpt] = pPere->personne.genome[position2->numeroArc];
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
    Personne* aMuter = NULL;
    int nbAllele = -1;
    ListeArc listeTempPersonne = consListeVide();
    ListeArc listeTempAlelle = consListeVide();
    ElementListeArc* positionPersonne = NULL;
    ElementListeArc* positionAllele = NULL;
    ElementListeArc* supprimerPersonne = NULL;
    ElementListeArc* supprimerAllele = NULL;
    ElementListePopulation* pPersonne = NULL;

    if(population.taillePopulation < 1)
    {
        perror("La population doit avoir au moins un element(mutation)");
        exit(-1);
    }

    //On récupère le nombre d'alleles
    nbAllele = population.listePopulation.pdebut->personne.nbAllele;

    //On calcul les taux de mutations
    n = (int)(ceil(population.taillePopulation*mutationRate));
    m = (int)(ceil(population.listePopulation.pdebut->personne.nbAllele*mutationRate));

    //On initialise la liste temporaire des personnes
    for(i = 0; i < population.taillePopulation; i++)
    {
        listeTempPersonne = ajoutListeFin(listeTempPersonne, i);
    }

    //Boucle qui choisit les personnes de manière aléatoire
    for(i = 0; i < n; i++)
    {
        //On recuperer la personne qui doit muter
        random = random_number(0, population.taillePopulation - i - 1);
        pPersonne = population.listePopulation.pdebut;
        positionPersonne = supprimerPersonne = listeTempPersonne.pdebut;
        for(j = 0; j < random; j++)
        {
            supprimerPersonne = positionPersonne;
            positionPersonne = positionPersonne->psuivant;
            pPersonne = pPersonne->psuivant;
        }

        //On créé un pointeur sur elle
        aMuter = &pPersonne->personne;

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
        if(positionPersonne == listeTempPersonne.pdebut)
        {
            listeTempPersonne.pdebut = listeTempPersonne.pdebut->psuivant;
        }
        else
        {
            supprimerPersonne->psuivant = positionPersonne->psuivant;
        }
        free(positionPersonne);
        positionPersonne = supprimerPersonne = NULL;
    }
    supprimerListe(&listeTempPersonne);
    return population;
}

Graphe appliquerPersonne(Personne personne, Graphe graphe)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    int numArcApplicable;
    for(i = 0; i < personne.nbAllele; i++)
    {
        if(personne.genome[i].actif)
        {
            numArcApplicable = personne.genome[i].numeroArc;
            tempEffi = personne.genome[i].mesure.efficacite.pdebut;
            tempArc = personne.genome[i].mesure.arcApplicables.pdebut;
            while(numArcApplicable != tempArc->numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            graphe.tabArcs[personne.genome[i].numeroArc].ponderation += tempEffi->numeroArc;
            graphe.tabArcs[personne.genome[i].numeroArc].cout += personne.genome[i].mesure.cout;
        }
    }
    return graphe;
}
Graphe retirerPersonne(Personne personne, Graphe graphe)
{
    int i;
    ElementListeArc* tempEffi = NULL;
    ElementListeArc* tempArc = NULL;
    int numArcApplicable;
    for(i = 0; i < personne.nbAllele; i++)
    {
        if(personne.genome[i].actif)
        {
            numArcApplicable = personne.genome[i].numeroArc;
            tempEffi = personne.genome[i].mesure.efficacite.pdebut;
            tempArc = personne.genome[i].mesure.arcApplicables.pdebut;
            while(numArcApplicable != tempArc->numeroArc)
            {
                tempArc = tempArc->psuivant;
                tempEffi = tempEffi->psuivant;
            }
            graphe.tabArcs[personne.genome[i].numeroArc].ponderation -= tempEffi->numeroArc;
            graphe.tabArcs[personne.genome[i].numeroArc].cout -= personne.genome[i].mesure.cout;
        }
    }
    return graphe;
}

float score(GeneticSolver geneticSolver, Personne personne)
{
    return geneticSolver.ratioPriority * personne.lenght + (1 - geneticSolver.ratioPriority) * (100 - personne.budget / geneticSolver.targetBudget * 100);
}

Personne majPersonne(GeneticSolver geneticSolver, Personne personne)
{
    int i, somme;
    if(personne.genome != NULL)
    {
        somme = 0;
        for(i = 0; i < personne.nbAllele; i++)
        {
            somme += personne.genome[i].actif * personne.genome[i].mesure.cout;
        }
        personne.budget = somme;
    }
    personne.score = score(geneticSolver, personne);
    return personne;
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
            if(tabTemp[j]->personne.score > scoreMax && tabMarq[j] == false)
            {
                max = j;
                scoreMax = tabTemp[j]->personne.score;
            }
        }
        tabMarq[max] = true;
        newPopulation = ajoutListePopulationFin(newPopulation, tabTemp[max]->personne);
    }

    for(i = 0; i < n; i++)
    {
        if(tabMarq[i] == false)
        {
            supprimerPersonne(&tabTemp[i]->personne);
            free(tabTemp[i]);
        }
    }
    population.listePopulation = newPopulation;
    return population;
}

Personne selectionONE(Population population)
{
    ElementListePopulation* temp = population.listePopulation.pdebut;
    Personne garde = temp->personne;
    while(temp != NULL)
    {
        if(temp->personne.score > garde.score)
        {
            garde = temp->personne;
        }
        temp = temp->psuivant;
    }

    return garde;
}
