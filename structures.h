#ifndef STRUCTURES_H
#define STRUCTURES_H



#include <stdio.h>
#include <stdlib.h>



struct BITMAP_header{
	char name[2]; //doit être ègale à BM car fichier bmp
	unsigned int size;
	int reserved; //pas important
	unsigned int image_offset;
};

struct DIB_header{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short int colorplanes;
	unsigned short int bitsperpixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int temp[4];
};

struct RGB{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct Image{
	int height;
	int width;
	struct RGB **rgb;
};






#endif
