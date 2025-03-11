echo "DYNAMIC LIB APPROACH"

gcc -c -Wall -fPIC -D_GNU_SOURCE add.c
gcc -c -Wall -fPIC -D_GNU_SOURCE sub.c
gcc -c -Wall -fPIC -D_GNU_SOURCE mul.c

gcc add.o sub.o mul.o -shared -o lib_arithmetics_dyn.so

gcc -c -Wno-implicit-function-declaration main.c -o main.o
gcc main.o  -L. -l_arithmetics_dyn -o app2.out

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."

./app2.out