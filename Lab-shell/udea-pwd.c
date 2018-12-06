#include <stdio.h>
#include <unistd.h>

// Variables globales
char cwd[256];

int main(){
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return(0);
}
