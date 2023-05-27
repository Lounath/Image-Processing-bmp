#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>


struct BITMAP_header;

struct DIB_header;

struct RGB;

struct Image;

struct Image readImage(FILE *fp, int height, int width);

int min(int a, int b);

int max(int a, int b);

void freeImage(struct Image pic);

unsigned char gray(struct RGB rgb);

void grayscale(struct Image pic);

void negatif(struct Image pic);

void morelumi(struct Image pic);

void lesslumi(struct Image pic);

void lesscontrast(struct Image pic);

void morecontrast(struct Image pic);

void binary(struct Image pic);

void jaimebien(struct Image pic);

void symhori(struct Image pic);

void symvert(struct Image pic);

void cent80(struct Image pic);

void mirror(struct Image pic);

void quatre2010(struct Image pic);

void blur(struct Image pic);

int newImage(struct BITMAP_header header, struct DIB_header dibheader, struct Image pic);

int openbmpfile(const char *fileName);

void menu();




#endif








