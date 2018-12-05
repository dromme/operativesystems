#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main () {
    int i, status;
    int numHijos = 3;
    pid_t pid;
    for (i = 0; i < numHijos; i++) {
        pid = fork();
        if (pid == -1) {
            /* Error */
            printf("No fue posible crear un hijo\n");
            return -1;
        }
        if (pid == 0) {
            printf("Soy el hijo #%d con PID: %d\n",i+1, getpid());
            exit(0);
        }
    }
    if(pid != 0){ // Se ejecuta el padre
        wait(&status); // Esperando por la terminacion de un primer hijo
        wait(&status); // Esperando por la terminacion de un segundo hijo
        wait(&status); // Esperando por la terminacion del ultimo hijo
        printf("Soy el padre: Ya se han ejecutado todos mis hijos\n");
    }
    return 0;
}
