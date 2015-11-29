/**
* @fichier main.c
* @titre Convolution 2D
* @description Convolution 2D avec la programmation concurrente
* @auteurs Kevin Estalella & Federico Lerda
* @date 21 Octobre 2015
* @version 1.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "time.h" //librarie utilisée pour calculer le temps total de la convolution
#include "convolution.h"
#include "filtre.h"


/**
* Point d'entrée du programmae
* @param argc nombre d'arguments
* @param argv tableau de string qui stock les arguments
* @return code de fin d'execution du programme
*/
int main(int argc, char **argv) {
  if (argc != 5) {
    fprintf(stderr, "usage: %s input output filter nb_threads\n"\
    "where input and output are PPM files\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *input = argv[1];
  char *output = argv[2];
  char *filtre = argv[3];
  int nb_threads = atoi(argv[4]);

  img_t *img = load_ppm(input); //charge l'image source

  if (img == NULL) {
    fprintf(stderr, "Failed loading %s!\n", input);
    return EXIT_FAILURE;
  }

  img_t *img2 = alloc_img(img->width, img->height); //alloue la mémoire pour l'image de destination

  //départ du temps d'exécution
  struct timespec start, finish;
  clock_gettime(CLOCK_MONOTONIC, &start);

  //déclaration des variables utilisées pour l'appel des différents threads
  pthread_t threads[nb_threads];
  convolution_params_t tab[nb_threads];

  //calcule une portion de l'image pour la convolution avec les threads
  int taille_portion_image = (img->height * img->width) / nb_threads;

  //on fait une boucle pour chaque thread
  for(int i = 0; i < nb_threads; i++) {

    //nous remplissons la structure que l'on passe au thread
    tab[i].source = img;
    tab[i].destination = img2;
    tab[i].filtre = filtre;
    tab[i].debut = taille_portion_image * i;  //calcul de la position initial
    if (i == (nb_threads-1)) {
      tab[i].fin = img->width * img->height; //calcul de la position final
    } else {
      //on prend la valeur maximal pour le dernier élement afin de ne pas perdre des pixels
      tab[i].fin = taille_portion_image * (i+1); //calcul de la position final
    }

    //on crée le thread et on test qu'il ne crash pas
    if (pthread_create(&threads[i], NULL, thread, &tab[i]) != 0) {
      fprintf(stderr, "pthread_create failed!\n");
      free_all_img(img,img2); //libère la mémoire de l'image source et destination
      return EXIT_FAILURE;
    }
  }

for(int i = 0; i < nb_threads; i++) {
  //permet d'attendre que chaque thread se termine
  if (pthread_join(threads[i], NULL) != 0) {
    fprintf(stderr, "pthread_join failed!\n");
    free_all_img(img,img2); //libère la mémoire de l'image source et destination
    return EXIT_FAILURE;
  }
}

  //nous affichons le temps après la convolution
  clock_gettime(CLOCK_MONOTONIC, &finish);
  double elapsed_ms = 1000 * (finish.tv_sec - start.tv_sec);
  elapsed_ms += (finish.tv_nsec - start.tv_nsec) / 1000000.0;

  printf("Temps d'execution pour calculer la convolution : %f \n", elapsed_ms);

  //enregistre l'image de fin modifiée grâce à la convolution 2d
  if (!write_ppm(argv[2], img2)) {
    fprintf(stderr, "Failed writing %s!\n", output);
    free_all_img(img,img2); //libère la mémoire de l'image source et destination
    return EXIT_FAILURE;
  }

  free_all_img(img,img2); //libère la mémoire de l'image source et destination

  return EXIT_SUCCESS;
}
