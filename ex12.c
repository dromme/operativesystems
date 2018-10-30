#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

//lea de la entrada estándar el nombre de un programa y cree un proceso hijo para ejecutar dicho programa.
int main(int argc, char *argv[]){
	pid_t pid = fork();
	if (pid < 0) {   //Error
		perror("Fork error\n");
        exit(1);
	} 
    else if (pid == 0) { //Hijo
    	printf("Ejecutando... \n");
    	execlp(argv[1],argv[1], NULL);

    }else{
    	wait(NULL);
    }
    return(0);
}