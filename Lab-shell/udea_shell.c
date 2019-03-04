#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

#include "parser.h"

// Macros
#define INPUT_SIZE 100

// Prototipos
void mostrarPrompt();
int identificarOrden(char *);
void ejecutarOrdenInterna(int numeroElementos, char *items[]);
	// Ordenes Internas
void ejecutarEcho(int numeroElementos, char *items[]);
void ejecutarPWD();
void ejecutarCD(char *);
void ejecutarTime();

void ejecutarOrdenExterna(int numeroElementos, char *items[]);

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

/* 
	Función que muestra el prompt al usuario en pantalla y recibe los comandos introducidos.
*/
void mostrarPrompt(){
	int orden; // 1: Orden interna, 0: Orden externa
	int segundoPlanoActivo; // Activo = 1, No activo = 0
	while(1){
	printf("\E[1;3;4;32m"); //Permite cambiar de formato la salida por medio de codigo ANSI
    printf("udea-shell> ");
    printf("\E[00m ");
	fgets(input, INPUT_SIZE, stdin);
		segundoPlanoActivo = background;
		numeroElementos = separaItems(input, &items, &background); // background = 1 -> Segundo plano
		if(numeroElementos > 0){
			orden = identificarOrden(items[0]);
			if(orden == 1)
				ejecutarOrdenInterna(numeroElementos, items);
			else
				ejecutarOrdenExterna(numeroElementos, items);
		}
		if(background == 0 && segundoPlanoActivo == 0) // Ejecución en primer plano
			wait(&status);
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
*/
void ejecutarOrdenInterna(int numeroElementos, char *items[]){
	if(strcmp(items[0], "udea-pwd") == 0)
		ejecutarPWD();

	else if(strcmp(items[0], "udea-cd") == 0){
		if(numeroElementos == 2)
			ejecutarCD(items[1]);
	}

	else if(strcmp(items[0], "udea-echo") == 0)
		ejecutarEcho(numeroElementos, items);

	else if(strcmp(items[0], "udea-clr") == 0)
		system("clear"); // stdlib function

	else if(strcmp(items[0], "udea-time") == 0)
		ejecutarTime();

	else if(strcmp(items[0], "udea-exit") == 0)
		exit(0);

	else if(strcmp(items[0], "udea-help") == 0){
		printf("Comandos udea\n udea-pwd\n udea-cd\n udea-echo\n udea-clr \n udea-time \n udea-exit \n");
	}

	else {
		printf("Comando no reconocido. Utilice udea-help para ver los comandos udea. \n");
	}
}

void ejecutarEcho(int numeroElementos, char *items[]){
	for(int i=1; i < numeroElementos; i++)
		printf("%s ", *(items + i));
	printf("\n");
}

void ejecutarPWD(){ // Llamado al sistema getcwd()
	char cwd[256];
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void ejecutarCD(char *ruta){ // Llamado al sistema chdir
	chdir(ruta);
}

void ejecutarTime(){ // Llamado al sistema time()
	time_t currentTime = time(NULL);
	char *timeString = ctime(&currentTime); // Convirtiendo a formato de tiempo local
	printf("%s", timeString);
}

/*
	Función que permite ejecutar un programa almacenado en el disco (/bin).
	Se realiza un llamado a fork para crear un nuevo proceso y posteriormente
	se sobreescribe su imagen de memoria con la del programa solicitado utilizando
	la familia de funciones exec.
*/
void ejecutarOrdenExterna(int numeroElementos, char *items[]){
	char rutaPrograma[strlen(items[0]) + 6];
	strcpy(rutaPrograma, "/bin/");
	strcat(rutaPrograma, items[0]);
	char *arg[numeroElementos + 1];
	int i;
	for(i=0; i<numeroElementos; i++)
		arg[i] = items[i];
	arg[i] = NULL;
	int result;
	if(fork() == 0){
		result = execv(rutaPrograma, arg);
		if (result == -1) exit(0);
	}
}
