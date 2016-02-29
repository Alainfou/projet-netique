#include "graphe.h"

/* Constructeurs */

Arc consArcVide()
{
    Arc newArc;
    newArc.cout = -1;
    newArc.noeudArrive = -1;
    newArc.noeudDepart = -1;
    newArc.ponderation = -1;

    return newArc;
}

Graphe consGrapheVide()
{
    Graphe nouveauGraphe;
    nouveauGraphe.nbArc = -1;
    nouveauGraphe.nbNoeuds = -1;
    nouveauGraphe.nbLevel = -1;
    nouveauGraphe.tabArcs = NULL;
    nouveauGraphe.tabNoeuds = NULL;

    return nouveauGraphe;
}

Noeud consNoeudVide()
{
    Noeud nouveauNoeud;
    nouveauNoeud.listePrec = consListeVide();
    nouveauNoeud.listeSuiv = consListeVide();
    nouveauNoeud.niveau = -1;

    return nouveauNoeud;
}

Graphe consGrapheManuel()
{
    Graphe graphe = consGrapheVide();
    int nbArcsmin, i, j, nbSuccesseurs;
    int compteurArc = 0;

    //Saisie sécurisée du nombre de noeuds
    printf("Saisir le nombre de sommets (minimum 2): ");
    graphe.nbNoeuds = secure_INTMin(2);
    nbArcsmin = graphe.nbNoeuds - 1;

    //Saisie sécurisée du nombre d'arcs
    printf("Saisir le nombre d'arcs (minimum %d): ", nbArcsmin);
    graphe.nbArc = secure_INTMin(nbArcsmin);

    graphe.tabNoeuds = (Noeud*)malloc(graphe.nbNoeuds*(sizeof(Noeud)));
    //Verification de l'allocation
    if(graphe.tabNoeuds == NULL)
    {
        perror("Allocation du tableau de noeuds (consGrapheManuel) impossible");
        exit(-1);
    }

    graphe.tabArcs = (Arc*)malloc(graphe.nbArc*(sizeof(Arc)));
    if(graphe.tabArcs == NULL)
    {
        free(graphe.tabNoeuds);
        perror("Allocation du tableau d'arcs (consGrapheMauel) impossible");
        exit(-1);
    }

    //On construit toutes les listes vides
    for(i = 0; i < graphe.nbNoeuds; i++)
    {
        graphe.tabNoeuds[i] = consNoeudVide();
    }
    for(i = 0; i < graphe.nbArc; i++)
    {
        graphe.tabArcs[i] = consArcVide();
    }

    //Saisie utilisateur
    for (i = 0; i < graphe.nbNoeuds; i++)
    {
        printf("Combien de successeurs possede le noeud %d : ", i);
        nbSuccesseurs = secure_INTMinMax(0, graphe.nbNoeuds - (i + 1));
        for(j = 0; j < nbSuccesseurs; j++)
        {
            printf("Donner le numero du %d eme successeur du noeud %d : ", j+1, i);
            graphe.tabArcs[compteurArc].noeudArrive = secure_INTMin(0);
            graphe.tabArcs[compteurArc].noeudDepart = i;

            printf("Donner la ponderation de l'arc : ");
            graphe.tabArcs[compteurArc].ponderation = secure_INTMin(0);
            graphe.tabArcs[compteurArc].cout = 0;

            graphe.tabNoeuds[i].listeSuiv = ajoutListeFin(graphe.tabNoeuds[i].listeSuiv, compteurArc);
            graphe.tabNoeuds[graphe.tabArcs[compteurArc].noeudArrive].listePrec = ajoutListeFin(graphe.tabNoeuds[graphe.tabArcs[compteurArc].noeudArrive].listePrec, compteurArc);
            compteurArc++;
        }
    }
    return graphe;
}

/* Affichage */

void afficherArc(Arc arc)
{
    printf("Dep : %d -> Arr : %d | Ponder : %d | Cout : %d\n", arc.noeudDepart, arc.noeudArrive, arc.ponderation, arc.cout);
}

void afficherListeArcNoeud(ListeArc listeArc, Graphe graphe, bool afficheSuivant)
{
    ElementListeArc* temp = listeArc.pdebut;
    if(estVideListe(listeArc))
    {
        printf("Liste vide");
    }

    while(temp !=NULL)
    {
        if(afficheSuivant)
        {
            printf(" -> %d", graphe.tabArcs[temp->numeroArc].noeudArrive);
        }
        else
        {
            printf(" -> %d", graphe.tabArcs[temp->numeroArc].noeudDepart);
        }
        temp = temp->psuivant;
    }
}

void afficherGraphe(Graphe graphe)
{
    int i;
    if(graphe.nbNoeuds == 0)
    {
        printf("Graphe vide\n");
    }
    else
    {
        for(i = 0; i < graphe.nbNoeuds; i++)
        {
            printf("Noeud numero %d :\n",i);
            printf("Niveau %d :\n",graphe.tabNoeuds[i].niveau);

            printf("Suivant :");
            afficherListeArcNoeud(graphe.tabNoeuds[i].listeSuiv, graphe, true);

            printf("\nPrecedent :");
            afficherListeArcNoeud(graphe.tabNoeuds[i].listePrec, graphe, false);
            printf("\n\n");
        }

        for(i = 0; i < graphe.nbArc; i++)
        {
            afficherArc(graphe.tabArcs[i]);
        }

        printf("\n\n");
    }
}

/* Utilitaires */

void supprimerGraphe(Graphe *graphe)
{
    int i;
    if(graphe->tabArcs != NULL)
    {
        for(i = 0; i < graphe->nbNoeuds; i++)
        {
            supprimerListe(&graphe->tabNoeuds[i].listePrec);
            supprimerListe(&graphe->tabNoeuds[i].listeSuiv);
        }
        free(graphe->tabArcs);
        graphe->tabArcs = NULL;
    }

    if(graphe->tabNoeuds != NULL)
    {
        free(graphe->tabNoeuds);
        graphe->tabNoeuds = NULL;
    }

    graphe->nbArc = 0;
    graphe->nbNoeuds = 0;
    graphe->tabArcs = NULL;
    graphe->tabNoeuds = NULL;
}

bool testEtage(ListeArc liste, bool tabVirtuel[], int tailleTab, Arc* tabArc)
{
    int i;
    ElementListeArc* temp = liste.pdebut;
    if(estVideListe(liste))
    {
        return true;
    }

    for(i = 0; i < tailleTab; i++)
    {
        while(temp!=NULL)
        {
            if(!tabVirtuel[tabArc[temp->numeroArc].noeudDepart])
            {
                return false;
            }
            temp = temp->psuivant;
        }
    }
    return true;
}

Graphe decomposition(Graphe graphe)
{
    int i, compteur, etage;
    bool tabVirtuel[graphe.nbNoeuds];
    bool tabEtage[graphe.nbNoeuds];
    bool cycle = true;

    //Initialisation des tableaux
    for(i = 0; i < graphe.nbNoeuds; i++)
    {
        tabVirtuel[i] = tabEtage[i] = false;
    }

    compteur = etage = 0;

    while(compteur < graphe.nbNoeuds)
    {
        for(i = 0; i < graphe.nbNoeuds; i++)
        {
            if(graphe.tabNoeuds[i].niveau != -1)
            {
                continue;
            }
            tabEtage[i] = testEtage(graphe.tabNoeuds[i].listePrec, tabVirtuel, graphe.nbNoeuds, graphe.tabArcs);
        }
        for(i = 0; i < graphe.nbNoeuds; i++)
        {
            if(tabEtage[i])
            {
                graphe.tabNoeuds[i].niveau = etage;
                tabVirtuel[i] = true;
                compteur ++;
                cycle = false;
            }
        }
        for(i = 0; i < graphe.nbNoeuds; i++)
        {
            tabEtage[i] = false;
        }

        etage++;
        if(cycle)
        {
            perror("Le graphe contient un cycle");
            exit(-1);
        }
        cycle = true;
    }
    return graphe;
}

ListeArc plusCourtChemin(Graphe graphe)
{
    int dist[graphe.nbNoeuds];
    int previous[graphe.nbNoeuds];
    int i, pos, calcDist, arret;
    ListeArc Q = consListeVide();
    ListeArc shortest_Path = consListeVide();
    ElementListeArc* temp = NULL;
    ElementListeArc* tempB = NULL;
    ElementListeArc* position = NULL;
    ElementListeArc* supprimer = NULL;
    ElementListeArc* temp2 = NULL;
    int minDist = -1;

    //Initialisation
    for(i = 0; i < graphe.nbNoeuds; i++)
    {
        dist[i] = -1;
        previous[i] = -1;
        Q = ajoutListeFin(Q, i);
    }

    if(estVideListe(graphe.tabNoeuds[0].listeSuiv))
    {
        supprimerListe(&Q);
        return shortest_Path;
    }

    dist[0] = 0;
    previous[0] = -1;

    while(!estVideListe(Q))
    {
        temp = Q.pdebut;
        pos = temp->numeroArc;
        minDist = dist[pos];
        tempB = position = supprimer = temp;
        while(temp !=NULL)
        {
            if(dist[temp->numeroArc] != -1)
            {
                if(dist[temp->numeroArc] < minDist)
                {
                    minDist = dist[temp->numeroArc];
                    supprimer = tempB;
                    position = temp;
                    pos = temp->numeroArc;
                }
            }
            tempB = temp;
            temp = temp->psuivant;
        }

        if(dist[pos] == -1)
        {
            perror("Graphe non connexe (dijsktra)");
            exit(-1);
        }
        if(position == Q.pdebut)
        {
            Q.pdebut = Q.pdebut->psuivant;
        }
        else
        {
            supprimer->psuivant = position->psuivant;
        }
        free(position);
        position = supprimer = NULL;

        if(estVideListe(graphe.tabNoeuds[pos].listeSuiv))
        {
            arret = pos;
	    //Construction du chemin
            if(estVideListe(shortest_Path))
            {
                shortest_Path.pdebut = shortest_Path.pfin = consElementListeArc(pos);
            }
            else
            {
                temp2 = consElementListeArc(pos);
                temp2->psuivant = shortest_Path.pdebut;
                shortest_Path.pdebut = temp2;
            }
            pos = previous[pos];
            while(pos != -1)
            {
                temp2 = consElementListeArc(pos);
                temp2->psuivant = shortest_Path.pdebut;
                shortest_Path.pdebut = temp2;
                pos = previous[pos];
            }

            //Rajout de la longueur du chemin dans la liste
            shortest_Path.pdebut = temp2;
            temp2 = consElementListeArc(dist[arret]);
            temp2->psuivant = shortest_Path.pdebut;
            shortest_Path.pdebut = temp2;
            supprimerListe(&Q);
            return shortest_Path;
        }

        //Parcours des voisins
        temp = graphe.tabNoeuds[pos].listeSuiv.pdebut;

        while(temp != NULL)
        {
            calcDist = dist[pos] + graphe.tabArcs[temp->numeroArc].ponderation;
            if(dist[graphe.tabArcs[temp->numeroArc].noeudArrive] == -1)
            {
                dist[graphe.tabArcs[temp->numeroArc].noeudArrive] = calcDist;
                previous[graphe.tabArcs[temp->numeroArc].noeudArrive] = pos;
            }
            else
            {
                if(calcDist < dist[graphe.tabArcs[temp->numeroArc].noeudArrive])
                {
                    dist[graphe.tabArcs[temp->numeroArc].noeudArrive] = calcDist;
                    previous[graphe.tabArcs[temp->numeroArc].noeudArrive] = pos;
                }
            }
            temp = temp->psuivant;
        }
    }
    supprimerListe(&Q);
    return shortest_Path;
}
