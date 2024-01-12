#ifndef comp_H
#define comp_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include <sys/time.h>

/* Programa H.33 Programa para teste dos algoritmos de compressão descompressão e busca exata em arquivo comprimido*/

#define BaseNum 128/* Base numerica que o algoritmo trabalha*/
#define MaxAlfabeto 255 /*Const. Usada em ExtraiProximaPalavra*/
#define MaxTamVetoresBO 10
#define TRUE 1
#define FALSE 0

/*--Entram aqui os tipos dos programa E.26--*/
/*e 26*/
#define Vazio       "!!!!!!!!!!"
#define Retirado    "**********"
#define M  7
#define t 11
/* tamanho da chave*/

typedef unsigned int Apontador;
typedef unsigned char TipoChave[t];
typedef unsigned TipoPesos[t];
typedef struct TipoItem {
    /* outros componentes*/
    int Freq;
    int Ordem;
    TipoChave Chave;
} TipoItem;
typedef unsigned int Indice;
typedef TipoItem TipoDicionario[M];
/*--Entram aqui os tipos dos programa H.1 --*/
/*h1*/
#define MaxTamTexto    1000
#define MaxTamPadrao   10
#define Maxchar        256
#define NumMaxErros    10

typedef char TipoTexto[MaxTamTexto];
typedef char TipoPadrao[MaxTamPadrao];

typedef short TipoAlfabeto[MaxAlfabeto + 1];
typedef struct TipoBaseOffset{
    int Base, Offset;
} TipoBaseOffset;
typedef TipoBaseOffset TipoVetoresBO[MaxTamVetoresBO + 1];
typedef char TipoPalavra[256];
typedef TipoPalavra TipoVetorPalavra[M+1];

/* Entra aqui a função GeraPeso do Programa E.22 */
/* Entra aqui a função de transformação do programa E.23*/
/*Entram aqui os operadores apresentados no programa E.27*/
/*Entram aqui as funções Particao e */
/* Quicksort dos programas D.6 e D.7*/


void CalculaCompCodigo(TipoDicionario A, int n);
int Codifica(TipoVetoresBO VetoresBaseOffset, int Ordem, int* c, int MaxCompCod);
int Decodifica(TipoVetoresBO VetoresBaseOffset, FILE* ArqComprimido, int MaxCompCod);
int ConstroiVetores( TipoVetoresBO VetoresBaseOffset, TipoDicionario Vocabulario, int n, FILE *ArqComprimido);
int LeNumInt(FILE *ArqComprimido);
void GravaNumInt(FILE *ArqComprimido, int Num);
void DefineAlfabeto(TipoAlfabeto, FILE *ArqAlf);
void ExtraiProximaPalavra (TipoPalavra Result, int *Indice, char *Linha, FILE *ArqTXt, TipoAlfabeto Alfabeto);
void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido);
void PrimeiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *Indice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p);
int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p, FILE* ArqComprimido);
Indice OrdenaPorFrequencia(TipoDicionario Vocabulario);
void TerceiraEtapa(FILE *ArqTxT, TipoAlfabeto Alfabeto, int *Indice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p, TipoVetoresBO VetoresBaseOffset,FILE* ArqComprimido, int MaxCompCod);
void Escreve(FILE* ArqComprimido, int* Codigo, int* c);
int LeVetores(FILE *ArqComprimido, TipoBaseOffset * VetoresBaseOffset);
int LeVocabulario(FILE *ArqComprimido, TipoVetorPalavra Vocabulario);
void Busca(FILE *ArqComprimido, FILE *ArqAlf);
void Atribui(TipoPadrao P, int Codigo, int c);
void Particao(Indice Esq, Indice Dir, Indice *i, Indice *j, TipoItem *A);
void Ordena(Indice Esq, Indice Dir, TipoItem *A);
void QuickSort(TipoItem *A, Indice *x);
Indice h(TipoChave Chave, TipoPesos p);
void Descompressao(FILE* ArqComprimido, FILE* ArqTxt, FILE* ArqAlf);
void Inicializa(TipoDicionario T);
Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);
void GeraPesos(TipoPesos p);
void Retira(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Insere(TipoItem x, TipoPesos p, TipoDicionario T);
char *Trim(char *str);

#endif