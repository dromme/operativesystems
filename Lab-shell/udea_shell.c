#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include "parser.h"

// Macros
#define INPUT_SIZE 100

// Prototipos
void mostrarPrompt();
int identificarOrden(char *);
void ejecutarOrdenInterna(int numeroElementos, char *items[]);
void ejecutarOrdenExterna(int numeroElementos, char *items[]);
void ejecutarEcho(int numeroElementos, char *items[]);

// Variables globales
char input[INPUT_SIZE], **items;
int numeroElementos, background, status;
pid_t pid;

	// Función main
int main(){
	printf("\tUdeA Shell\n");
	mostrarPrompt();
	return(0);
}

/**/
void mostrarPrompt(){
	int orden; // 1: Orden interna, 0: Orden externa
	while(1){
		printf("udea-shell> "); fgets(input, INPUT_SIZE, stdin);
		numeroElementos = separaItems(input, &items, &background);
		if(numeroElementos > 0){
			orden = identificarOrden(items[0]);
			if(orden == 1)
				ejecutarOrdenInterna(numeroElementos, items);
			else
				ejecutarOrdenExterna(numeroElementos, items);
			if(background == 0) // Ejecución en primer plano
				wait(&status);
		}
	}
}

/*
	Función que evalúa si una orden ingresada por el usuario es interna o externa.
	Se retorna 1 para el primer caso y 0 para el segundo.
	La evaluación se realiza verificando la palabra clave 'udea' en la entrada.
*/
int identificarOrden(char *entrada){
	if(strlen(entrada) < 4)
		return(0);
	if(entrada[0]=='u' && entrada[1]=='d' && entrada[2]=='e' && entrada[3]=='a')
		return(1);
	return(0);
}

/*
	Función que permite ejecutar una orden interna de udea-shell.
	Estas ordenes son implementadas como programas independientes y por lo tanto
	son accedidaas mediante una función exec.
*/
void ejecutarOrdenInterna(int numeroElementos, char *items[]){
	if(strcmp(items[0], "udea-pwd") == 0){
		if((pid = fork()) == 0)
			execl("./udea-pwd.out", "./udea-pwd.out", NULL);
	}
	else if(strcmp(items[0], "udea-cd") == 0)
		printf("udea-cd - En construccion\n");

	else if(strcmp(items[0], "udea-echo") == 0)
		ejecutarEcho(numeroElementos, items);

	else if(strcmp(items[0], "udea-clr") == 0)
		printf("udea-clr - En construccion\n");

	else if(strcmp(items[0], "udea-time") == 0)
		printf("udea-time - En construccion\n");

	else if(strcmp(items[0], "udea-exit") == 0)
		exit(0);	
}

/*
	Función que permite ejecutar un programa almacenado en el disco.
	Se realiza un llamado a fork para crear un nuevo proceso y posteriormente
	se sobreescribe su imagen de memoria con la del programa solicitado utilizando
	la familia de funciones exec.
*/
void ejecutarOrdenExterna(int numeroElementos, char *items[]){
	char *itemsMasNULL[numeroElementos + 1];
	int i;
	for(i=0; i < numeroElementos; i++)
		*(itemsMasNULL + i) = *(items + i);
	*(itemsMasNULL + i) = NULL;
	if((pid = fork()) == 0)
		execvp(items[0], itemsMasNULL);
}

void ejecutarEcho(int numeroElementos, char *items[]){
	for(int i=1; i < numeroElementos; i++)
		printf("%s ", *(items + i));
	printf("\n");
}
