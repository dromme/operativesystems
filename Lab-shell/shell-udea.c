#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"

#define TAM 100
// Limpiar la pantalla  
#define clear() printf("\033[H\033[J") 

// Prompt 
void printDir() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\nDir: %s", cwd); 
} 


void boldRed() {
  printf("\033[1;31m");
}

void reset () {
  printf("\033[0m");
}



int main(int argc, char *argv[]){

  char ** items;
  int i, num, background;
  char expresion[TAM];

 

     while(1) {
         //Prompt
        boldRed();
        printDir(); 
        reset();
        //Leer comandos
        fgets (expresion, TAM, stdin);
        //Parser
        num = separaItems (expresion, &items, &background);
        //probando
        printf ("Numero de parametros: %d\n", num);

          if (num>0)
          {
            for (i=0; i<num; i++)
              printf ("%d \"%s\"\n", i+1, items[i]);

            printf ("Background: %d\n", background);

            liberaItems (items);
            continue;
          }

     return 0;
     }
  }

