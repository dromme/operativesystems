
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

    pid_t pid = fork();
        if (pid > 0) {   //Padre
            printf("Hola ");
            fflush(stdout);        
        } 
        else if (pid == 0) { //Hijo
            printf("Mundo");
            fflush(stdout);
            pid_t pid = fork();
                if (pid == 0) { //Nieto
                  printf("!");
                  fflush(stdout);  
              }
          } 
          return 0;
      }