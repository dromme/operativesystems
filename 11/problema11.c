#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

// Prototipos
void calcularFactoriales(int numeroHijo);
int factorial(int numero);

	// Funcion main
int main(){
	pid_t hijo1, hijo2, hijo3;
	int status;
	hijo1 = fork();
	if(hijo1 == 0){ // Se ejecuta el hijo 1
		calcularFactoriales(1);
		exit(0);
	}else{
		hijo2 = fork();
		if(hijo2 == 0){ // Se ejecuta el hijo 2
			calcularFactoriales(2);
			exit(0);
		}else{
			hijo3 = fork();
			if(hijo3 == 0){ // Se ejecuta el hijo 3
				calcularFactoriales(3);
				exit(0);
			}else{ // Se ejecuta el padre
				wait(&status); // Esperando a que termine un primer hijo
				wait(&status); // Esperando a que termine un segundo hijo
				wait(&status); // Esperando a que termine el ultimo hijo
				printf("PADRE: Todos mis hijos ya han terminado de ejecutarse.\n");
			}
		}
	}
	return(0);
}

/*
	Se calculan e imprimen los valores del factorial de los enteros
	entre 1 y 10 para un hijo especifico. El numero del hijo que invoca la
	funcion es pasado en el argumento numeroHijo.
*/
void calcularFactoriales(int numeroHijo){
	for(int i=1; i < 11; i++)
		printf("HIJO%d: fact(%d) = %d\n", numeroHijo, i, factorial(i));
}

// Factorial recursivo
int factorial(int numero){
	if(numero == 1) return(1);
	return(numero * factorial(numero - 1));
}
