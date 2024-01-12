# Instrução para compilar o programa

all: programa clean

programa: main.o part1.o
	gcc main.o part1.o -o tp3_part1 -lm

main.o: main.c part1.h
	gcc -c main.c -o main.o

funcoes.o: part1.c part1.h
	gcc -c part1.c -o part1.o

clean:
	rm -rf *.o *~ printy
