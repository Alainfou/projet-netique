#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Constructeurs */

ElementListeArc* consElementListeArc(int numeroArc)
{
    ElementListeArc* newElement = (ElementListeArc*)malloc(sizeof(ElementListeArc));
    if(newElement == NULL)
    {
        perror("Allocation du maillon de chaine(consElementListeArc) impossible");
        exit(-1);
    }

    newElement->numeroArc = numeroArc;
    newElement->psuivant = NULL;
    return newElement;
}

ListeArc consListeVide()
{
    ListeArc newListe;
	newListe.pdebut = NULL;
	newListe.pfin = NULL;
	return newListe;
}


ListeArc ajoutListeFin(ListeArc liste, int numeroArc)
{
    if(estVideListe(liste))
    {
        liste.pfin = consElementListeArc(numeroArc);
        liste.pdebut = liste.pfin;
    }
    else
    {
        liste.pfin->psuivant = consElementListeArc(numeroArc);
        liste.pfin = liste.pfin->psuivant;
    }

    return liste;
}

/* Affichage */

void afficherListeArc(ListeArc liste)
{
    ElementListeArc* temp = liste.pdebut;

    if(estVideListe(liste))
    {
        printf("Liste vide");
    }

    while(temp != NULL)
    {
        printf("-> %d ", temp->numeroArc);
        temp = temp -> psuivant;
    }
}

/* Utilitaires */

bool estVideListe(ListeArc liste)
{
    return liste.pdebut == NULL;
}

void supprimerListe(ListeArc* liste)
{
    ElementListeArc* temp;

    if(!estVideListe(*liste))
    {
        while(liste->pdebut != NULL)
        {
            temp = liste->pdebut;
            liste->pdebut = liste->pdebut->psuivant;
            free(temp);
        }
    }
    liste->pdebut = liste->pfin = NULL;
}

ListeArc copieListeArc(ListeArc liste)
{
    ListeArc copie = consListeVide();
    ElementListeArc* temp = liste.pdebut;
    ElementListeArc* tempcopie = liste.pdebut;
    if(estVideListe(liste))
    {
        return copie;
    }
    else
    {
        copie.pdebut = copie.pfin = consElementListeArc(temp->numeroArc);
        temp = temp->psuivant;
        while(temp != NULL)
        {
            tempcopie = consElementListeArc(temp->numeroArc);
            copie.pfin->psuivant = tempcopie;
            copie.pfin = tempcopie;
            temp = temp->psuivant;
        }
    }
    return copie;
}
