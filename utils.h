#ifndef utilsH_
#define utilsH_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LENGHT 7

/* Définition du type bool */

typedef enum {false, true} bool;

/* Fonctions */

void clean (char *buffer);
void purger();
int secure_INT();
int secure_INTMin(int min);
int secure_INTMax(int max);
int secure_INTMinMax(int min, int max);
int random_number(int a, int b);

#endif
