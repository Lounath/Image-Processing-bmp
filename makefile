OBJ_DIR := fichier_o

all : prog

$(OBJ_DIR)/main.o : main.c main.h 
	gcc -c main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/functions_traitement.o : functions_traitement.c functions_traitement.h
	gcc -c functions_traitement.c -o $(OBJ_DIR)/functions_traitement.o

$(OBJ_DIR)/structures.o : structures.c structures.h
	gcc -c structures.c -o $(OBJ_DIR)/structures.o
	
prog : $(OBJ_DIR)/main.o $(OBJ_DIR)/functions_traitement.o 
	gcc  $(OBJ_DIR)/structures.o $(OBJ_DIR)/main.o  $(OBJ_DIR)/functions_traitement.o -o prog -lm
