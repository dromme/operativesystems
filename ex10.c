
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    printf("Id principal: %d, Padre: %d \n", (int)getpid(), (int)getppid());
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid > 0) {   /* Padre */
            sleep(1);  //Para que el hijo viva mas que el padre y tenga el mismo id padre inicial.
            continue;
        } else if (pid == 0) { /* Hijo */

            printf(" Mi id es %d  y mi padre es %d \n", (int)getpid(), (int)getppid());
            if (i == 1) { 
                for (int i = 0; i < 2; ++i) {
                    pid_t pid = fork();
                    if (pid > 0) {   /* Padre */
                        sleep(1);  //Para que el hijo viva mas que el padre y tenga el mismo id padre inicial.
                    
                    } else if (pid == 0) { /* Hijo */
                        printf(" Mi id es %d  y mi padre es %d \n", (int)getpid(), (int)getppid());
                        break;
                    } else {
                        printf("fork error\n");
                        exit(1);
                    }
                }
            }
            break;
        } else {
            printf("fork error\n");
            exit(1);
        }
    }
return 0;
}