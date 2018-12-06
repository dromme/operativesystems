gcc -Wall -I . -c parser.c udea_shell.c
gcc -Wall -I . -o shell.out *.o
rm *.o
gcc -Wall -o udea-pwd.out udea-pwd.c
