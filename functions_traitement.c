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
	do{
		printf("How much do you want to increase the luminosity ? (between 0 and 255)\n");
		i = scanf("%d",&k);
		if (i != 1)
			exit(1);
	}while(k<0);
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			pic.rgb[i][j].blue = min((pic.rgb[i][j].blue + k), 255);
			pic.rgb[i][j].green = min((pic.rgb[i][j].green + k), 255);
			pic.rgb[i][j].red = min((pic.rgb[i][j].red + k), 255);
		}
	}
}

void lesslumi(struct Image pic){
	int i,j,k;
	do{
		printf("How much do you want to decrease the luminosity ? (between 0 and 255)\n");
		i = scanf("%d",&k);
		if (i != 1)
			exit(1);
	}while(k<0);
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width; j++){
			pic.rgb[i][j].blue = max((pic.rgb[i][j].blue - k), 0);
			pic.rgb[i][j].green = max((pic.rgb[i][j].green - k), 0);
			pic.rgb[i][j].red = max((pic.rgb[i][j].red - k), 0);
		}
	}
}

void lesscontrast(struct Image pic){
	int i,j,k,temp;
	float contrast = 0.6;
	
	for (i = 0; i < pic.height; i++) {
		for (j = 0; j < pic.width; j++) {

		    // Augmentation du contraste du pixel en fonction du facteur de contraste
		    pic.rgb[i][j].blue = ((pic.rgb[i][j].blue - 128) * contrast + 128);
		    pic.rgb[i][j].green = ((pic.rgb[i][j].green - 128) * contrast + 128);
		    pic.rgb[i][j].red = ((pic.rgb[i][j].red - 128) * contrast + 128);
        	}
	}
}

void morecontrast(struct Image pic){
	int i,j,k,temp;
	float contrast = 1.2;
	
	for (i = 0; i < pic.height; i++) {
		for (j = 0; j < pic.width; j++) {

		    // Augmentation du contraste du pixel en fonction du facteur de contraste
		    pic.rgb[i][j].blue = ((pic.rgb[i][j].blue - 128) * contrast + 128);
		    pic.rgb[i][j].green = ((pic.rgb[i][j].green - 128) * contrast + 128);
		    pic.rgb[i][j].red = ((pic.rgb[i][j].red - 128) * contrast + 128);
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

void horisym(struct Image pic){
	int i,j;
	for (i = 0; i<pic.height/2; i++){ // pas obliger de /2 mais fais moins d'opérations inutiles
		for (j=0; j<pic.width; j++){
			pic.rgb[i][j].red = pic.rgb[pic.height-i-1][j].red;
			pic.rgb[i][j].green = pic.rgb[pic.height-i-1][j].green;
			pic.rgb[i][j].blue = pic.rgb[pic.height-i-1][j].blue;
		}
	}
}

void vertsym(struct Image pic){
	int i,j;
	for (i = 0; i<pic.height; i++){
		for (j=0; j<pic.width/2; j++){
			pic.rgb[i][j].red = pic.rgb[i][pic.width-j-1].red;
			pic.rgb[i][j].green = pic.rgb[i][pic.width-j-1].green;
			pic.rgb[i][j].blue = pic.rgb[i][pic.width-j-1].blue;
		}
	}
}

void onehundred80(struct Image pic){
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

void SepiaFilter(struct Image pic) {
	int i, j;
	unsigned char tmpR, tmpG, tmpB;
    
	for (i = 0; i < pic.height; i++) {
		for (j = 0; j < pic.width; j++) {
			tmpR = pic.rgb[i][j].red;
			tmpG = pic.rgb[i][j].green;
			tmpB = pic.rgb[i][j].blue;        

			pic.rgb[i][j].red = fmin((tmpR * 0.393) + (tmpG * 0.769) + (tmpB * 0.189), 255);
			pic.rgb[i][j].green = fmin((tmpR * 0.349) + (tmpG * 0.686) + (tmpB * 0.168), 255);
			pic.rgb[i][j].blue = fmin((tmpR * 0.272) + (tmpG * 0.534) + (tmpB * 0.131), 255);

		}
	}
}

int newImage(struct BITMAP_header header, struct DIB_header dibheader, struct Image pic){
	int i,temp,choice;
	do {
		printf("Choose how your going to change your image between (please enter the number related to your choice): \n(1) Grayscale \n(2) Negatif \n(3) More luminosity \n(4) Less luminosity \n(5) Less contrast \n(6) More contrast \n(7) Binary \n(8) Horizontal symmetry \n(9) Vertical symmetry \n(10) 180 degres \n(11) Mirror \n(12) Blur\n(13) Sepia Filter\n Please enter the number related to your choice\n ");
		i = scanf("%d",&choice);
		if (i != 1)
			exit(1);
	}while ((choice<1)||(choice>13));
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
			horisym(pic);
			break;
		case(9):
			vertsym(pic);
			break;
		case(10):
			onehundred80(pic);
			break;
		case(11):
			mirror(pic);
			break;
		case(12):
			do{
				printf("How many time do you wanna blur your image ? (positive number only)\n");
				scanf("%d",&temp);
			}while(temp<0);
			for (i=0;i<temp;i++)
				blur(pic);
			break;
		case(13): 
			SepiaFilter(pic);
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
			printf("Problems with .bmp make sure that it really is a .bmp. Problem come from the header of the file.");
		}
		if (dibheader.bitsperpixel != 24){
			printf("Problems with .bmp make sure that it really is a .bmp. Problem come from the bit per pixel.");
		}
		else{
			printf("Problems with .bmp make sure that it really is a .bmp. Problem come from the compression.");
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
	int pic,test;
	do {
		printf("What image to you want to use between: \n(1) TIGER (but not Woods) \n(2) Landscape \n(3) A really cool painting \n(4) People (with a great sunset) \nPlease enter the number related to your choice\n");
		test = scanf("%d",&pic);
		if (test != 1)
			exit(1);
	}while ((pic<1)&&(pic>4));
	switch(pic){
		case(1):
			openbmpfile("imaget.bmp");
			break;
		case(2):
			openbmpfile("imagel.bmp");
			break;
		case(3):
			openbmpfile("imagec.bmp");
			break;
		case(4):
			openbmpfile("imagep.bmp");
			break;
	}
}





























