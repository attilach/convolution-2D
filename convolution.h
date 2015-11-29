#ifndef __CONVOLUTION_H_INCLUDE__
#define __CONVOLUTION_H_INCLUDE__

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "filtre.h"

//stock différents éléments que l'on passe aux threads
typedef struct convolution_params_t {
  img_t* source;
  img_t* destination;
  char* filtre;
  int debut;  //position de debut pour la convolution
  int fin;  //position de fin
} convolution_params_t;

void *thread(void *thread_id);
void convolution(img_t* source, img_t* destination, char* filtre, int debut, int fin);
int test_limite(double valeur);

#endif
