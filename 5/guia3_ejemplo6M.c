#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  pid_t pid_h1, pid_h2, pid_h3;
  pid_t pid_n;
  int i = 0;
  int status;
  pid_h1 = fork();
  if(pid_h1 == 0) {
    i++;
    pid_n = fork();
    if(pid_n==0) {
      i++;
      printf("NIETO: i = %d\n",i);
    }else {
      wait(&status); // HIJO 1: Esperando por la terminacion de mi hijo (NIETO)
      printf("HIJO 1: i = %d, Ya se ejecuto mi hijo, es decir, NIETO\n",i);
    }
  }else {
    pid_h2 = fork();
    if(pid_h2 == 0) {
      i++;
      printf("HIJO 2: i = %d\n",i);
    }else {
      pid_h3 = fork();
      if(pid_h3 == 0) {
        i++;
        printf("HIJO 3: i = %d\n",i);
      }else { // Se ejecuta el padre
        wait(&status); // Esperando por la terminacion de un primer hijo
        wait(&status); // Esperando por la terminacion de un segundo hijo
        wait(&status); // Esperando por la terminacion del ultimo hijo
        printf("PAPA: i = %d, Ya se han ejecutado todos mis hijos\n",i);
      }
    }
  }
  return 0;
}
