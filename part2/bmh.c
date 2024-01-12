#include "bhm.h"


/*
le arquivo de entrada e salva o conteudo em texto
*/

void le_arquivo(FILE* arq, char* texto){

  int n = 0;

  while((texto[n] = fgetc(arq)) != EOF){
      n++;
  }

  fclose(arq);
}

void bmh(int tamanhoPadrao, int tamanhoTexto, char *texto,char *padrao) {

  if (tamanhoPadrao > tamanhoTexto)     // se padrao > texto retorna pra main sem casamentos
    return;

  int i, j, k, d[MAXCHAR + 1];
  for (i = 0; i <= MAXCHAR; i++)            // pré - processamento
    d[i] = tamanhoPadrao;
  for (i = 1; i < tamanhoPadrao; i++)
    d[padrao[i-1]] = tamanhoPadrao - i;


  j = tamanhoPadrao;
  while (j <= tamanhoTexto) {               // buscando o padrão no texto
    k = j;
    i = tamanhoPadrao;
    while (texto[k-1] == padrao[i-1] && i > 0) {
      k--;
      i--;
    }
    if (i == 0)      // encontrou
      printf("casamento na posicao: %d\n", k+1);

    j += d[texto[j-1]];
  }
}