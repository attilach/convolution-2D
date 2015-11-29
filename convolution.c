/**
* @fichier convolution.c
* @titre Convolution 2D
* @description Convolution 2D avec la programmation concurrente
* @auteurs Kevin Estalella & Federico Lerda
* @date 21 Octobre 2015
* @version 1.0
*/

#include "convolution.h"

/**
* Applique la convolution 2d sur l'image passée en paramètre
* @param thread_id contient les paramètres à fournir pour la convolution 2d
* @return ne retourne rien
*/
void *thread(void *thread_id) {
  //on recupère les paramètres fourni au thread
  convolution_params_t *tab = (convolution_params_t *) thread_id;
  //On appel la fonction convolution avec les paramètres fournis
  convolution(tab->source, tab->destination, tab->filtre, tab->debut, tab->fin);
  return NULL;
}


 /**
 * Applique la convolution 2d sur l'image passée en paramètre
 * @param source image source
 * @param destination image de destination
 * @param filtre filtre à appliquer à l'image
 * @param debut premier pixel que l'on traite
 * @param debut dernier pixel que l'on traite
 * @return ne retourne rien
 */
void convolution(img_t* source, img_t* destination, char* filtre, int debut, int fin) {

  //récupère le filtre passé en paramètre
  filtre_t K = getFiltre(filtre);

  int h, i, j;  //indices des boucles for
  int N = K.size; //ordre de la matrice K (Kernel)
  int M = N/2;  //marge par rapport au centre du Kernel
  int ligne = source->width; //largeur de ligne (en pixel [si on fait 2 * ligne on se retrouve à la deuxieme ligne])
  int nbrLigne = source->height; //hauteur de l'image (en pixel)
  //variables nous permettant le calcul des trois composantes r, g et b de l'image
  double calcul_r, calcul_g, calcul_b;

  //parcours toute l'image. h est la position du pixel actuel.
  for (h = debut; h < fin; h++) {

    calcul_r = 0;
    calcul_g = 0;
    calcul_b = 0;

    //test que la position actuelle (h) soit en dehors de la marge M des bords de l'image
    if ((h > (M*ligne)) && (h < ((ligne*nbrLigne) - (M*ligne))) && ((h % ligne) > M) && ((h % ligne) < ligne-M)) {
      for (j=-M; j<=M; j++) { //ligne du Kernel
        for (i=-M; i<=M; i++) { //colonne du Kernel

          pixel_t *p1 = &source->data[h+(ligne*j)+i]; //récupère pixel de l'image de base
          double z = *(K.f+((j+M)*N)+(i+M)); //récupère la valeur du Kernel (filtre)

          calcul_r += z * p1->r;  //calcul de la valeur pour le rouge
          calcul_g += z * p1->g;  //calcul de la valeur pour le vert
          calcul_b += z * p1->b;  //calcul de la valeur pour le bleu
        }
      }
    }

    //récupère pixel de l'image de destination
    pixel_t *p2 = &destination->data[h];

    //écrit pixel de l'image de destination avec les valeurs calculées
    p2->r = test_limite(calcul_r);
    p2->g = test_limite(calcul_g);
    p2->b = test_limite(calcul_b);
  }
}

/**
* Test que la valeur pour une couleur soit contenue entre 0 et 255 (code rgb)
* @param valeur valeur calculée grâce à la convolution 2d pour une couleur
* @return valeur comprise entre 0 et 255
*/
int test_limite(double valeur){
  if(valeur > 255){
    return 255;
  } else if(valeur < 0){
    return 0;
  } else{
    return valeur;
  }
}
