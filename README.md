
Please enter those lines in your terminal: 

>>sudo apt install imagemagick

>>gcc -c structures.c -o fichier_o/structures.o 

>>make (makefile)

>>./prog (executable créée par make)

To use the program just answer the questions in the terminal, your new files will be name "new.bmp" (you can change this name in the code)

enter "display new.bmp" in the terminal to see your picture

to enter a new picture add:
>>case(the next number):

>>    openbmpfile(Filename);

>>    break;

in the functions_traitement.c file
You also need to change the line 

>>while ((pic<1)&&(pic>4));

switching 4 by the number you wrote in case. If you want you can add the description of your image to the text.

Have a good day :)
