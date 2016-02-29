#include "mesure.h"

/* Constructeurs */

Mesures consMesuresVide()
{
    Mesures newMesures;
    newMesures.tabMesure = NULL;
    newMesures.nbMesure = 0;
    newMesures.nbMesuresTotales = 0;

    return newMesures;
}

Mesure consMesureVide()
{
    Mesure newMesure;
    newMesure.cout = -1;
    newMesure.id = -1;
    newMesure.arcApplicables = consListeVide();
    newMesure.efficacite = consListeVide();

    return newMesure;
}

Mesure consMesureManuel(int nbArc, int id)
{
    Mesure newMesure = consMesureVide();
    ElementListeArc* temp = NULL;
    newMesure.id = id;
    int i, cptArc, efficacite;
    bool same;

    printf("\nVeuillez saisir le cout de la mesure n°%d : ", id);
    newMesure.cout = secure_INTMin(0);

    printf("\nVeuillez saisir le nombre d'arcs (0-%d) sur lesquels la mesure s'applique (-1 = tous les arcs) : ", nbArc);
    cptArc = secure_INTMinMax(-1, nbArc);

    printf("\nL'efficacite de la mesure est-elle la meme sur tous les arcs ? (0 non, 1 oui) : ");
    same = secure_INTMinMax(0,1);

    //Si l'efficacité est la même
    if(same)
    {
        printf("\nDonnez l'efficacite de la mesure : ");
        efficacite = secure_INTMin(0);
    }

    if(cptArc == nbArc)
    {
        cptArc = -1;
    }

    //Si l'efficacité n'est pas la même partout
    if(cptArc != -1)
    {
        for(i = 0; i < cptArc; i++)
        {
            printf("\nDonnez le numero du %d arc sur lequel la mesure s'applique : ", i + 1);
            newMesure.arcApplicables = ajoutListeFin(newMesure.arcApplicables, secure_INTMinMax(0,nbArc));
        }

        if(!same)
        {
            temp = newMesure.arcApplicables.pdebut;
            for(i = 0; i < cptArc; i++)
            {
                printf("\nDonnez l'efficacite de la mesure pour l'arc %d : ", temp->numeroArc);
                newMesure.efficacite = ajoutListeFin(newMesure.efficacite, secure_INTMin(0));
                temp = temp->psuivant;
            }
        }
        else
        {
            for(i = 0; i < cptArc; i++)
            {
                newMesure.efficacite = ajoutListeFin(newMesure.efficacite, efficacite);
            }
        }
    }

    //Si tous les arcs sont concernés
    if(cptArc == -1)
    {
        for(i = 0; i < nbArc; i++)
        {
            newMesure.arcApplicables = ajoutListeFin(newMesure.arcApplicables,i);
        }

        if(!same)
        {
            temp = newMesure.arcApplicables.pdebut;
            for(i = 0; i < nbArc; i++)
            {
                printf("\nDonnez l'efficacite de la mesure pour l'arc %d : ", temp->numeroArc);
                newMesure.efficacite = ajoutListeFin(newMesure.efficacite, secure_INTMin(0));
                temp = temp->psuivant;
            }
        }
        else
        {
            for(i = 0; i < nbArc; i++)
            {
                newMesure.efficacite = ajoutListeFin(newMesure.efficacite, efficacite);
            }
        }
    }
    return newMesure;
}

Mesures consMesuresManuel(int nbArc)
{
    int i;
    Mesures newMesures = consMesuresVide();
    ElementListeArc* temp = NULL;
    printf("Saisir le nombre de mesures : ");
    newMesures.nbMesure = secure_INTMin(0);
    newMesures.tabMesure = (Mesure*)malloc(newMesures.nbMesure*(sizeof(Mesure)));
    if(newMesures.tabMesure == NULL)
    {
        perror("Erreur d'allocation de mesures(consMesuresManuel)");
        exit(-1);
    }
    for(i = 0; i < newMesures.nbMesure; i++)
    {
        newMesures.tabMesure[i] = consMesureManuel(nbArc,i);
    }
    newMesures.nbMesuresTotales = 0;
    for(i = 0; i < newMesures.nbMesure; i++)
    {
        temp = newMesures.tabMesure[i].arcApplicables.pdebut;
        while(temp != NULL)
        {
            newMesures.nbMesuresTotales ++;
            temp = temp->psuivant;
        }
    }

    return newMesures;
}

/* Affichage */

void afficherMesure(Mesure mesure)
{
    printf("Mesure numero: %d, cout: %d",mesure.id, mesure.cout);
    printf("\nListe arc applicables:");
    afficherListeArc(mesure.arcApplicables);
    printf("\nListe efficacite:");
    afficherListeArc(mesure.efficacite);
    printf("\n");
}

void afficherMesures(Mesures mesures)
{
    int i;

    if(mesures.nbMesure == 0)
    {
        printf("Aucune mesure\n");
    }
    else
    {
        for(i = 0; i < mesures.nbMesure; i++)
        {
            afficherMesure(mesures.tabMesure[i]);
        }
    }
}

/* Outils */

void supprimerMesure(Mesure* mesure)
{
    mesure->cout = -1;
    mesure->id = -1;
    if(mesure->arcApplicables.pdebut != NULL)
    {
        supprimerListe(&(mesure->arcApplicables));
    }

    if(mesure->efficacite.pdebut != NULL)
    {
        supprimerListe(&(mesure->efficacite));
    }

    mesure->arcApplicables = consListeVide();
    mesure->efficacite = consListeVide();
}

void supprimerMesures(Mesures* mesures)
{
    int i;
    if(mesures->tabMesure != NULL)
    {
        for(i = 0; i < mesures->nbMesure; i++)
        {
            supprimerMesure(&(mesures->tabMesure[i]));
        }
        free(mesures->tabMesure);
        mesures->tabMesure = NULL;
        mesures->nbMesure = 0;
        mesures->nbMesuresTotales = 0;
    }
}
