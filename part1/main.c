#include "part1.h"

int main(){
	struct timeval tv0,tv1;
	double tempo_final, tempo_inicial, time;
    gettimeofday(&tv0, NULL);

	dist_main();
	sa_main();
	
	gettimeofday(&tv1, NULL);
	tempo_final = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
	tempo_inicial = (double)(tv0.tv_sec) + (double)(tv0.tv_usec)/ 1000000.00;
	time = (tempo_final - tempo_inicial);
	printf("Gettimeofday: (%f)\n",time);
	int minutos, segundos;
	minutos = time/60;
	segundos = (int) time%60; 
	//convertendo o tempo que e doouble para inteiro
	printf(" %d min %d seg\n",minutos,segundos);

	return 0;
}
