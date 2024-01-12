#include "bhm.h"

void main(){
  struct timeval tv0,tv1;
	double tempo_final, tempo_inicial, time;
    gettimeofday(&tv0, NULL);
  char *p = (char*) malloc(sizeof(char) * 100);
  printf("Insira o padrao a ser procurado no texto(tamanho max = 100):\n");
  scanf("%s", p);

  char *txt = (char*) malloc(sizeof(char)*5001);
  char c;
  int tam_p = strlen(p);

  FILE *arq = fopen("entrada.txt", "r");
  if(arq == NULL){
    printf("Erro ao abrir arquivo\n");
  exit(1);
  }

  for(int i = 0; (c = fgetc(arq)) != EOF; i++){
    txt[i] = c;
  }

  bmh(tam_p, strlen(txt), txt, p);

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
}
