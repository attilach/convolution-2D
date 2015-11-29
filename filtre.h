/**
* @fichier filter.h
* @description Contient structures et prototypes des fonctions
* @auteurs Kevin Estalella & Federico Lerda
* @date 21 Octobre 2015
* @version 1.0
*/

#ifndef __KERNEL_H_INCLUDE__
#define __KERNEL_H_INCLUDE__

#include <math.h> //librairie utilisée pour la commande sqrt
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Stock l'adresse d'un filtre et sa taille
typedef struct filtre_t {
  double *f;
  int size;
} filtre_t;

filtre_t getFiltre(char *filtre);

#endif //__KERNEL_H_INCLUDE__
