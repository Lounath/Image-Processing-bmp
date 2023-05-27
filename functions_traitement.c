#include "functions_traitement.h"
#include "structures.h"


struct Image readImage(FILE *fp, int height, int width){
	struct Image pic;
	int i, bytestoread, nbrgb;
	pic.rgb = (struct RGB**) malloc(height*sizeof(void*));
	pic.height = height;
	pic.width = width;
	bytestoread = ((24 * width + 31)/32)*4; //formule du wiki pour le padding
	nbrgb = bytestoread/sizeof(struct RGB) + 1;
	
	for (i= height-1; i>=0; i--){
		pic.rgb[i] = (struct RGB*) malloc(nbrgb*sizeof(struct RGB));
		fread(pic.rgb[i], 1, bytestoread, fp);
	}
	
	return pic;
}


int min(int a, int b){
	if (a>b) return b;
	return a;
}

int max(int a, int b){
	if (a>b) return a;
	return b;
}

void freeImage(struct Image pic){
	int i;
	for (i= pic.height-1; i>=0; i--){
		free(pic.rgb[i]);
	}
	free(pic.rgb);
}
	
unsigned char gray(struct RGB rgb){
	return ((0.3*rgb.red) + (0.6*rgb.green) + (0.1*rgb.blue));
}

void grayscale(struct Image pic){
	int i,j,temp;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			temp=gray(pic.rgb[i][j]);
			pic.rgb[i][j].blue = temp;
			pic.rgb[i][j].green = temp;
			pic.rgb[i][j].red = temp;
		}
	}
}

void negatif(struct Image pic){
	int i,j;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			pic.rgb[i][j].blue = 255 - pic.rgb[i][j].blue;
			pic.rgb[i][j].green = 255 - pic.rgb[i][j].green;
			pic.rgb[i][j].red = 255 - pic.rgb[i][j].red;
		}
	}
}

void morelumi(struct Image pic){
	int i,j,k;
	printf("De combien voulez vous augmenter la luminosité ? (entre 0 et 255)");
	scanf("%d",&k);
	if (k<0) printf("La prochaine écrivez un nombre positif");
	else{
		for (i = 0; i<pic.height; i++){
			for (j=0; j<pic.width; j++){
				pic.rgb[i][j].blue = min((pic.rgb[i][j].blue + k), 255);
				pic.rgb[i][j].green = min((pic.rgb[i][j].green + k), 255);
				pic.rgb[i][j].red = min((pic.rgb[i][j].red + k), 255);
			}
		}
	}
}

void lesslumi(struct Image pic){
	int i,j,k;
	printf("De combien voulez vous diminuer la luminosité ? (entre 0 et 255)");
	scanf("%d",&k);
	if (k<0) printf("La prochaine écrivez un nombre positif");
	else{
		for (i = 0; i<pic.height; i++){
			for (j=0; j<pic.width; j++){
				pic.rgb[i][j].blue = max((pic.rgb[i][j].blue - k), 0);
				pic.rgb[i][j].green = max((pic.rgb[i][j].green - k), 0);
				pic.rgb[i][j].red = max((pic.rgb[i][j].red - k), 0);
			}
		}
	}
}

void lesscontrast(struct Image pic){
	//Entre 0 et 100
	int i,j,k,temp;
	float contrast;
	printf("De combien voulez vous diminuer le contraste ? (entre 0 et 100)");
	scanf("%d",&k);
	contrast = ((100.0 - k) / 100.0) * ((100.0 - k) / 100.0);
	printf("%f",contrast);
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			temp = max((((((pic.rgb[i][j].blue / 255.0) - 0.5) * contrast) + 0.5) * 255.0),0);
			pic.rgb[i][j].blue = temp;
            		temp = max((((((pic.rgb[i][j].green / 255.0) - 0.5) * contrast) + 0.5) * 255.0),0);
			pic.rgb[i][j].green = temp;
			temp = max((((((pic.rgb[i][j].red / 255.0) - 0.5) * contrast) + 0.5) * 255.0),0);
			pic.rgb[i][j].red = temp;
			
		}
	}
}

void morecontrast(struct Image pic){
	//Entre 0 et 100
	//AAAAAAAHAHAHAHAHAHA CA MARCHE SUPER BIEN =]
	int i,j,k,temp;
	float contrast;
	printf("De combien voulez vous diminuer le contraste ? (entre 0 et 100)");
	scanf("%d",&k);
	contrast = ((100.0 + k) / 100.0) * ((100.0 + k) / 100.0);
	printf("%f",contrast);
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			temp = min((((((pic.rgb[i][j].blue / 255.0) - 0.5) * contrast) + 0.5) * 255.0),255);
			pic.rgb[i][j].blue = temp;
            		temp = min((((((pic.rgb[i][j].green / 255.0) - 0.5) * contrast) + 0.5) * 255.0),255);
			pic.rgb[i][j].green = temp;
			temp = min((((((pic.rgb[i][j].red / 255.0) - 0.5) * contrast) + 0.5) * 255.0),255);
			pic.rgb[i][j].red = temp;
			
		}
	}
}

void binary(struct Image pic){
	int i,j;
	grayscale(pic);
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			if (pic.rgb[i][j].blue > (255/2) )
				pic.rgb[i][j].blue=255;
			else
				pic.rgb[i][j].blue=0;
			pic.rgb[i][j].green = pic.rgb[i][j].blue;
			pic.rgb[i][j].red = pic.rgb[i][j].blue;
		}
	}
}

void jaimebien(struct Image pic){
	//probablement ce à quoi 100% de contraste devrais resembler
	int i,j;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			if (pic.rgb[i][j].blue > (255/2) )
				pic.rgb[i][j].blue=255;
			else
				pic.rgb[i][j].blue=0;
			if (pic.rgb[i][j].green > (255/2))
				pic.rgb[i][j].green=255;
			else
				pic.rgb[i][j].green=0;
			if (pic.rgb[i][j].red > (255/2))
				pic.rgb[i][j].red=255;
			else
				pic.rgb[i][j].red=0;
		}
	}
}

void symhori(struct Image pic){
	int i,j;
	for (i = 0; i<pic.height/2; i++){ // pas obliger de /2 mais fais moins d'opérations inutiles
		for (j=0; j<pic.width; j++){
			pic.rgb[i][j].red = pic.rgb[pic.height-i-1][j].red;
			pic.rgb[i][j].green = pic.rgb[pic.height-i-1][j].green;
			pic.rgb[i][j].blue = pic.rgb[pic.height-i-1][j].blue;
		}
	}
}

void symvert(struct Image pic){
	int i,j;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width/2; j++){
			pic.rgb[i][j].red = pic.rgb[i][pic.width-j-1].red;
			pic.rgb[i][j].green = pic.rgb[i][pic.width-j-1].green;
			pic.rgb[i][j].blue = pic.rgb[i][pic.width-j-1].blue;
		}
	}
}

void cent80(struct Image pic){
	int i,j,temp;
	for (i = 0; i<pic.height/2; i++){ //si on divise pas par 2 on annule toutes nos actions
		for (j=0; j<pic.width; j++){
			temp = pic.rgb[i][j].blue;
			pic.rgb[i][j].blue = pic.rgb[pic.height-i-1][j].blue;
			pic.rgb[pic.height-i-1][j].blue = temp;
			
			temp = pic.rgb[i][j].green;
			pic.rgb[i][j].green = pic.rgb[pic.height-i-1][j].green;
			pic.rgb[pic.height-i-1][j].green = temp;
			
			temp = pic.rgb[i][j].red;
			pic.rgb[i][j].red = pic.rgb[pic.height-i-1][j].red;
			pic.rgb[pic.height-i-1][j].red = temp;
		}
	}
}

void mirror(struct Image pic){
	int i,j,temp;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width/2; j++){
			temp = pic.rgb[i][j].blue;
			pic.rgb[i][j].blue = pic.rgb[i][pic.width-j-1].blue;
			pic.rgb[i][pic.width-j-1].blue = temp;
			
			temp = pic.rgb[i][j].green;
			pic.rgb[i][j].green = pic.rgb[i][pic.width-j-1].green;
			pic.rgb[i][pic.width-j-1].green = temp;
			
			temp = pic.rgb[i][j].red;
			pic.rgb[i][j].red = pic.rgb[i][pic.width-j-1].red;
			pic.rgb[i][pic.width-j-1].red = temp;
		}
	}
}

void quatre2010(struct Image pic){
}

void blur(struct Image pic){
	int i,j,k;
	for (i = 1; i<pic.height-1; i++){
		for (j=1; j<pic.width-1; j++){
			pic.rgb[i][j].blue = (pic.rgb[i-1][j-1].blue+pic.rgb[i-1][j].blue+pic.rgb[i][j-1].blue+pic.rgb[i-1][j+1].blue+pic.rgb[i+1][j-1].blue+pic.rgb[i][j].blue+pic.rgb[i+1][j].blue+pic.rgb[i][j+1].blue+pic.rgb[i+1][j+1].blue)/9;
			pic.rgb[i][j].green = (pic.rgb[i-1][j-1].green+pic.rgb[i-1][j].green+pic.rgb[i][j-1].green+pic.rgb[i-1][j+1].green+pic.rgb[i+1][j-1].green+pic.rgb[i][j].green+pic.rgb[i+1][j].green+pic.rgb[i][j+1].green+pic.rgb[i+1][j+1].green)/9;
			pic.rgb[i][j].red = (pic.rgb[i-1][j-1].red+pic.rgb[i-1][j].red+pic.rgb[i][j-1].red+pic.rgb[i-1][j+1].red+pic.rgb[i+1][j-1].red+pic.rgb[i][j].red+pic.rgb[i+1][j].red+pic.rgb[i][j+1].red+pic.rgb[i+1][j+1].red)/9;
		}
	}
}

int newImage(struct BITMAP_header header, struct DIB_header dibheader, struct Image pic){
	int i,temp,choice;
	do {
		printf("Choose how your going to change your image between (please enter the number related to your choice): \n(1) Grayscale \n(2) Negatif \n(3) More luminosity \n(4) Less luminosity \n(5) Less contrast \n(6) More contrast \n(7) Binary \n(8) Horizontal symmetry \n(9) Vertical symmetry \n(10) 180 degres \n(11) Mirror \n(12) Blur\nPlease enter the number related to your choixe\n ");
	scanf("%d",&choice);
	}while ((choice<1)||(choice>12));
	FILE *fpw= fopen("new.bmp","w"); //writer
	if (fpw == NULL) return 1;
	
	switch(choice){
		case(1):
			grayscale(pic);
			break;
		case(2):
			negatif(pic);
			break;
		case(3):
			morelumi(pic);
			break;
		case(4):
			lesslumi(pic);
			break;
		case(5):
			lesscontrast(pic);
			break;
		case(6):
			morecontrast(pic);
			break;
		case(7):
			binary(pic);
			break;
		case(8):
			symhori(pic);
			break;
		case(9):
			symvert(pic);
			break;
		case(10):
			cent80(pic);
			break;
		case(11):
			mirror(pic);
			break;
		case(12):
			printf("How many time do you wanna blur your image ?");
			scanf("%d",&temp);
			for (i=0;i<temp;i++)
				blur(pic);
			break;
		default:
			printf("The modification you are asking for doesn't exist. By default we just copy the photo given. \nPlease try again\n");
	}
	
	fwrite(header.name, 2, 1, fpw);
	fwrite(&header.size, 3*sizeof(int),1,fpw);
	
	fwrite(&dibheader, sizeof(struct DIB_header), 1, fpw);
	
	for (i= pic.height -1; i>=0; i--)
		fwrite(pic.rgb[i],((24 * pic.width + 31)/32)*4,1,fpw);
	fclose(fpw);
	return 0;
}

int openbmpfile(const char *fileName){
	FILE *fp = fopen(fileName,"rb"); // read binary
	if (fp == NULL) return 1;
	
	struct BITMAP_header header;
	struct DIB_header dibheader;
	
	fread(header.name,2,1,fp);
	fread(&header.size, 3*sizeof(int),1,fp);
	if ((header.name[0] != 'B') || (header.name[1] != 'M')){
		fclose(fp);
		return 1;
	}
	fread(&dibheader,sizeof(struct DIB_header),1,fp);
	if ((dibheader.compression != 0) || (dibheader.bitsperpixel != 24)||(dibheader.header_size != 40)){
		if (dibheader.header_size != 40){
			printf("size");
		}
		if (dibheader.bitsperpixel != 24){
			printf("bpp");
		}
		else{
			printf("comp");
		}
		fclose(fp);
		return 1;
	}
	fseek(fp,header.image_offset , SEEK_SET);
	struct Image image = readImage(fp,dibheader.height,dibheader.width);
	newImage(header, dibheader, image);
	
	fclose(fp);
	freeImage(image);
	return 0;
}
	

void menu(){
	int pic;
	do {
		printf("What image to you want to use between: \n(1) TIGER (but not Woods) \n(2) Landscape \nPlease enter the number related to your choice\n");
		scanf("%d",&pic);
	}while ((pic!=1)&&(pic!=2));
	switch(pic){
		case(1):
			openbmpfile("imaget.bmp");
			break;
		case(2):
			openbmpfile("imagef.bmp");
			break;
	}
}





























