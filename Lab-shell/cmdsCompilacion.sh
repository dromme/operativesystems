gcc -Wall -I . -c parser.c udea_shell.c
gcc -Wall -I . -o shell.out *.o
rm *.o
