echo "STATIC LIB APPROACH"

gcc -c add.c -o add.o
gcc -c sub.c -o sub.o
gcc -c mul.c -o mul.o

ar r lib_arithmetics.a add.o sub.o mul.o

gcc -c -Wno-implicit-function-declaration main.c -o main.o
gcc main.o lib_arithmetics.a -o app1.out

./app1.out