#include "part1.h"


/*
le arquivo de entrada e salva o conteudo em texto
*/

int le_arquivo(FILE* arq, char* texto){

    int n = 0;  
    while((texto[n] = fgetc(arq)) != EOF){
        n++;
    }   
    return n;
    fclose(arq);
}
/*
funcao cria a tabela com valores baseados no padrao e procura o padrao no texto
caso o padrao seja encontrado faz se o calculo e printa a posicao inicial da palavra no texto
*/
int shiftand (const char *p, const char *t) {

  int r = -1;

  const int TABSIZE = 256; //tamanho maximo da tabela de acordo com a tabela ascii
  const unsigned long ONELEFT = 0x80000000; //valor usado para construir os valores da mascara
  int i = 0, j = 0, M = strlen(p), N = strlen(t);
  unsigned long tabela[TABSIZE];

  for (i = 0; i < TABSIZE; ++i){
    tabela[i] = 0; // preenche tabela com 0
  }

  unsigned long mascara = ONELEFT;

  for (j = 0; j < M; ++j) {
    tabela[p[j]] |= mascara; // posições onde ocorrem caracteres do padrao recebem mascara
    mascara >>= 1; // mascara recebe shift de 1
  }

  unsigned long R = 0; //r recebe 0, r auxilia na localizacao de ocorrencia de padrao no texto 
  mascara = ONELEFT >> (M - 1);

  for (i = 0 ; i < N; ++i) {
    R = ((R >> 1) | 0x80000000) & tabela[t[i]];
    if (R & mascara){
      printf("Casamento na posicao: %d\n",(i-M+1)+1);//sucesso, imprime a posicao inicial d padrao encontrado no texto
      r = 1; //altera o valor de r pois retornado -1 indica que o padrao nao foi encontrado no texto
    }
  }
  return r; // fracasso
}

static int distance (const char * word1, int len1, const char * word2, int len2){
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}
void separa_palavras(char *texto, char *padrao){
    int j = 0;
    int d;
    int posicao = 0;
    int len1 = strlen (padrao);
    char *palavra = (char*) malloc(50*sizeof(char));
    for(int i= 0; i < strlen(texto); i++){
        if(texto[i] == ' ' || texto[i] == ',' || texto[i] == '.'){
            //printf("Encontrei:'%c'\n", texto[i]);
            palavra[j] = '\0';
            //printf("%i-%s\n", j,palavra);
            d = distance (padrao, len1, palavra, j);
            if(d <= 1){
                printf(" %d ",posicao+1);
            }
            posicao = 0;
            j = 0;
        }
        else{
            if(posicao == 0){
                posicao = i;
            }
            palavra[j] = texto[i];
            j++;
        }
    }
    free(palavra);
    printf("\n");
} 
void dist_main(){
    
    printf("\n*****Distancia de Edicao******\n");
    char * palavra = (char*) malloc(500*sizeof(char));
    
    FILE *arq = fopen("entrada.txt", "r");
    FILE *padrao = fopen("padrao.txt", "r");
	char* texto = (char*) malloc(2*5001*sizeof(char));
	le_arquivo (arq, texto);
    le_arquivo(padrao, palavra);
    
    printf("%s", palavra);
    separa_palavras(texto, palavra);
    free(texto);
    free(palavra);
    printf("\n______________________________\n");
}
void sa_main() {
    
    printf("\n*****Shift And******\n");
	FILE *arq = fopen("entrada.txt", "r");

	char* texto = (char*) malloc(5001*sizeof(char));

	le_arquivo (arq, texto);

	char *p = (char*) malloc(sizeof(char) * 100);
  	printf("Insira o padrao a ser procurado no texto(tamanho max = 100):\n");
  	scanf("%s", p);

	int r = shiftand(p, texto); //chama a funcao shiftand passando o padrao e o texto e retorna r

	free(p);
	free(texto);
	if (r == -1){ // se o valor retornado for -1 nao possui o padrao no texto
  		printf("Nao possui no padrao\n");
	}
    printf("\n______________________________\n");
}
