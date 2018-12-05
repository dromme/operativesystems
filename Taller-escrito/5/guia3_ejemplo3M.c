#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main () {
    pid_t pid_hijo1;
    pid_t pid_hijo2;
    pid_t pid_hijo3;
    int status;
    pid_hijo1 = fork(); // Creo el primer hijo
    if (pid_hijo1 == 0) { // Hijo 1
      printf("Soy el hijo 1\n");
      //sleep (5);
    } else {  // Padre
        pid_hijo2 = fork(); // Creo al segundo hijo
        if (pid_hijo2 == 0) { // Hijo 2
          printf("Soy el hijo 2\n");
          //sleep (5);
        } else {  // Padre
            pid_hijo3 = fork();  // Creo al tercer hijo
            if (pid_hijo3 == 0) { // Hijo 3
              printf("Soy el hijo 3\n");
              //sleep (5);
            } else {  // Padre
              wait(&status); // Esperando por la terminacion de un primer hijo
              wait(&status); // Esperando por la terminacion de un segundo hijo
              wait(&status); // Esperando por la terminacion del ultimo hijo
              printf("Soy el padre: Ya se han ejecutado todos mis hijos\n");
              //sleep (5);
            }
        }
    }
    return 0;
}
