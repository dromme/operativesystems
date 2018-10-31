#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main () {
  int pid, status;
  int numHijos = 5;
  int numProceso;
  for(numProceso = 0; numProceso < numHijos; numProceso++) {
      pid = fork();
      if (pid == -1) {
          // Imprimir algún mensaje de error
      } else if(pid == 0) {
          break;
      }
  }
  if (pid == 0) {
      // Lógica del hijo
      printf("Soy el hijo #%d\n", numProceso);
  }
  else { // Se ejecuta el padre
      wait(&status); // Esperando por la terminacion de un primer hijo
      wait(&status); // Esperando por la terminacion de un segundo hijo
      wait(&status); // Esperando por la terminacion de un tercer hijo
      wait(&status); // Esperando por la terminacion de un cuarto hijo
      wait(&status); // Esperando por la terminacion del ultimo hijo
      printf("Soy un padre perezoso: Ya se han ejecutado todos mis hijos\n");
  }
}
