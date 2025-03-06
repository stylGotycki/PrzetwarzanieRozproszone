echo "DYNAMIC LIB APPROACH"

gcc -c -Wall -fPIC -D_GNU_SOURCE add.c
gcc -c -Wall -fPIC -D_GNU_SOURCE sub.c
gcc -c -Wall -fPIC -D_GNU_SOURCE mul.c

gcc add.o sub.o mul.o -shared -o lib_arithmetics_dyn.so

gcc -c main.c -o main.o
gcc main.o -L. -l_arithmetics_dyn -o app2.out

./app2.out