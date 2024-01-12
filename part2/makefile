# Instrução para compilar o programa

all: programa clean

programa: main_bmh.o bmh.o
	gcc main_bmh.o bmh.o -o tp3_bmh -lm

main.o: main_bmh.c bmh.h
	gcc -c main_bmh.c -o main_bmh.o

funcoes.o: bmh.c bmh.h
	gcc -c bmh.c -o bmh.o

clean:
	rm -rf *.o *~ printy
