#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct BITMAP_header;

struct DIB_header;

struct RGB;

struct Image;

struct Image readImage(FILE *fp, int height, int width);

int min(int a, int b);
//fonction qui retourne un entier, le minimum des entiers a et b

int max(int a, int b);
//fonction qui retourne un entier, le maximum des entiers a et b

void freeImage(struct Image pic);
//procédure qui libère l'espace alloué pour chaque pixel

unsigned char gray(struct RGB rgb);
//retourne un char, une moyenne de pixel qui donne une couleur grise

void grayscale(struct Image pic);
//procédure qui modifie l'image "pic" avec des échelles de gris grâce à la fonction gray

void negatif(struct Image pic);
//procédure qui modifie chaque pixel de l'image "pic" en leurs négatif 

void morelumi(struct Image pic);
//procédure qui demande à l'utillisateur un nombre pour augmenter la luminosité de l'image, pixel par pixel

void lesslumi(struct Image pic);
//procédure qui demande à l'utillisateur un nombre pour diminuer la luminosité de l'image, pixel par pixel

void lesscontrast(struct Image pic);
//procédure qui demande à l'utillisateur un nombre pour diminuer le contraste de l'image, pixel par pixel

void morecontrast(struct Image pic);
//procédure qui demande à l'utillisateur un nombre pour augmenter le contraste de l'image, pixel par pixel

void binary(struct Image pic);
//procédure qui modifie l'image "pic" en noir et blanc (2 couleurs unique)

void symhori(struct Image pic);
//procédure qui effectue la symétrie horizontale de l'image "pic"

void symvert(struct Image pic);
//procédure qui effectue la symétrie verticale de l'image "pic"

void cent80(struct Image pic);
//procédure qui effectue une rotation de 180°

void mirror(struct Image pic);
//procédure qui fait l'image mirroir de l'image

void quatre2010(struct Image pic);
//procédure qui effectue une rotation de 90°

void blur(struct Image pic);
//procédure qui modifie l'image "pic" avec un filtre flou

void SepiaFilter(struct Image pic);
//procédure qui applique un filtre rétro à l'image "pic"

int newImage(struct BITMAP_header header, struct DIB_header dibheader, struct Image pic);
//fonction qui modifie une nouvelle image en demandant à l'utilisateur quel fitre il veut appliquer

int openbmpfile(const char *fileName);
//fonction qui récupère les informations de l'image fourie

void menu();
//procédure qui affiche les choix d'images disponibles 




#endif
