/**
* @fichier filter.c
* @description Contient les filtres et les fonctions associées
* @auteurs Kevin Estalella & Federico Lerda
* @date 21 Octobre 2015
* @version 1.0
*/

#include "filtre.h"

//déclaration des différents filtres
double identity[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
double sharpen[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
double edge[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
double test[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
double blur[3][3] = {{1./9, 1./9, 1./9}, {1./9, 1./9, 1./9}, {1./9, 1./9, 1./9}};
double gauss[5][5] = {
  {1./256, 4./256, 6./256, 4./256, 1./256},
  {4./256, 16./256, 24./256, 16./256, 4./256},
  {6./256, 24./256, 36./256, 24./256, 6./256},
  {4./256, 16./256, 24./256, 16./256, 4./256},
  {1./256, 4./256, 6./256, 4./256, 1./256}
};
double unsharp[5][5] = {
  {-1./256, -4./256, -6./256, -4./256, -1./256},
  {-4./256, -16./256, -24./256, -16./256, -4./256},
  {-6./256, -24./256, 476./256, -24./256, -6./256},
  {-4./256, -16./256, -24./256, -16./256, -4./256},
  {-1./256, -4./256, -6./256, -4./256, -1./256}
};

/**
* Récupère le filtre du nom passé en argument
* @param *filtre filtre que l'on souhaite récupérer
* @return le filtre et sa taille dans une structure filtre_t
*/
filtre_t getFiltre(char *filtre) {
  filtre_t K;

  if (strcmp(filtre,"identity")==0) {
    K.f = (double*)identity;
    K.size = (int)sqrt(sizeof(identity)/sizeof(double));
  } else if (strcmp(filtre,"sharpen")==0) {
    K.f = (double*)sharpen;
    K.size = (int)sqrt(sizeof(sharpen)/sizeof(double));
  } else if (strcmp(filtre,"edge")==0) {
    K.f = (double*)edge;
    K.size = (int)sqrt(sizeof(edge)/sizeof(double));
  } else if (strcmp(filtre,"blur")==0) {
    K.f = (double*)blur;
    K.size = (int)sqrt(sizeof(blur)/sizeof(double));
  } else if (strcmp(filtre,"identity")==0) {
    K.f = (double*)identity;
    K.size = (int)sqrt(sizeof(identity)/sizeof(double));
  } else if (strcmp(filtre,"gauss")==0) {
    K.f = (double*)gauss;
    K.size = (int)sqrt(sizeof(gauss)/sizeof(double));
  } else if (strcmp(filtre,"unsharp")==0) {
    K.f = (double*)unsharp;
    K.size = (int)sqrt(sizeof(unsharp)/sizeof(double));
  } else {
    printf("Le filtre %s n'existe pas!\n", filtre);
    exit(1);
  }

  return K;
}
