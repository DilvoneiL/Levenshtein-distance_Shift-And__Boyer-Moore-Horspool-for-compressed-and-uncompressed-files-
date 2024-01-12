#include "comp.h"

int main(int argc, char *argv[]){
    FILE *ArqTxt = NULL, *ArqAlf = NULL; FILE *ArqComprimido = NULL;
    TipoPalavra NomeArqTxt, NomeArqAlf, NomeArqComp, Opcao;
    printf("*****************************************");
    printf("*                       Opcoes           ");
    printf("*---------------------------------------*");
    printf("* (c) Compressao                        *");
    printf("* (d) Descompressao                     *");
    printf("* (p) Pesquisa no Texto Comprimido      *");
    printf("*****************************************");
    printf("* Opcao: ");
    fgets(Opcao, MaxAlfabeto + 1, stdin);
    
    strcpy(NomeArqAlf, "alfabeto.txt");
    ArqAlf = fopen(NomeArqAlf, "r");

    if(Opcao[0] == 'c'){
        printf("Arquivo texto a ser comprimido: ");
        fgets(NomeArqTxt, MaxAlfabeto + 1, stdin);
        NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';
        printf("Arquivo comprimido a ser gerado:");
        fgets(NomeArqComp, MaxAlfabeto + 1, stdin);
        NomeArqComp[strlen(NomeArqComp) -1] = '\0';
        ArqTxt = fopen(NomeArqTxt, "r" );
        ArqComprimido = fopen(NomeArqComp, "w+b");
        Compressao(ArqTxt, ArqAlf, ArqComprimido);
        fclose(ArqTxt);
        ArqTxt = NULL;
        fclose(ArqComprimido);
        ArqComprimido = NULL ;
    }
    // else if(Opcao[0] == 'd'){
    //     printf("Arquivo comprimido a ser descomprimido:");
    //     fgets(NomeArqComp, MaxAlfabeto + 1, stdin);
    //     NomeArqComp[strlen(NomeArqComp)-1] = '\0';
    //     printf("Arquivo texto a ser gerado:");
    //     fgets(NomeArqAlf, MaxAlfabeto + 1, stdin);
    //     NomeArqTxt[strlen(NomeArqTxt) -1] = '\0';
    //     ArqTxt = fopen(NomeArqTxt, "w");
    //     ArqComprimido = fopen(NomeArqComp, "r+b");
    //     Descompressao(ArqComprimido, ArqTxt, ArqAlf);
    //     fclose(ArqTxt);
    //     ArqTxt = NULL;
    //     fclose(ArqComprimido);
    //     ArqComprimido = NULL;
    // }
    // else if(Opcao[0] == 'p'){
    //     printf("Arquivo comprimido para ser pesquisado: ");
    //     fgets(NomeArqComp, MaxAlfabeto + 1, stdin);
    //     NomeArqComp[strlen(NomeArqComp)-1] = '\0';
    //     strcpy(NomeArqComp, NomeArqComp);
    //     ArqComprimido = fopen(NomeArqComp, "r+b");
    //     Busca(ArqComprimido);
    //     fclose(ArqComprimido);
    //     ArqComprimido = NULL;
    // }
    return 0;

}