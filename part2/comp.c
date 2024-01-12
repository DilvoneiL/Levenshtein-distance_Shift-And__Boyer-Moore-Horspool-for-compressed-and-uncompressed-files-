#include "comp.h"

/*Programa H.23 Codigo para fazer a compressão*/
void compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido){
    TipoAlfabeto Alfabeto;
    TipoPalavra Palavra, Linha;
    int Ind = 1; int MaxCompCod;
    TipoDicionario Vocabulario;
    TipoPesos p; TipoVetoresBO VetoresBaseOffset;

    /*Inicialização do alfabeto*/  
    DefineAlfabeto(Alfabeto, ArqAlf); /* le alfabeto definido em arquivo*/
    *Linha = '\0';
    /*Inicialização do Vocabulario*/
    Inicializa(Vocabulario);
    GeraPesos(p);
    /*inicio da Compressao*/
    PrimeiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p);
    MaxCompCod = SegundaEtapa(Vocabulario, VetoresBaseOffset, p, ArqComprimido);
    fseek(ArqTxt, 0, SEEK_SET); /*move cursor para inicio do arquivo */
    Ind = 1;
    *Linha = '\0';
    TerceiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p, VetoresBaseOffset, ArqComprimido, MaxCompCod);
}
/*Programa H.24 Primeira Etapa da Compressão*/
void PrimeiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *Indice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p){
    TipoItem Elemento;
    int i;
    do{
        ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);
        memcpy(Elemento.Chave, p, sizeof(TipoChave));
        Elemento.Freq = 1;
        if(*Palavra != '\0'){
            i = Pesquisa(Elemento.Chave, p, Vocabulario);
            if( i < M)
            Vocabulario[i].Freq++;
            else Insere(Elemento, p, Vocabulario);
            do{
                ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);
                memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));
                /*O primeiro espaco depois da palavra não e codificado*/
                if( strcmp( Trim(Palavra), "") && (*Trim(Palavra)) != (char)0 ){
                    i = Pesquisa(Elemento.Chave, p, Vocabulario);
                    if( i < M)
                    Vocabulario[i].Freq++;
                    else Insere(Elemento, p, Vocabulario);
                }
            }while(strcmp(Palavra, ""));
        }
    }while (Palavra[0] != '\0');
}
/*h 25*/
int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p, FILE* ArqComprimido)
{
    int Result, i, j , NumNodosFolhas, PosArq;
    TipoItem Elemento;
    char Ch;
    TipoPalavra Palavra;
    NumNodosFolhas = OrdenaPorFrequencia(Vocabulario);
    CalculaCompCodigo(Vocabulario, NumNodosFolhas);
    Result = ConstroiVetores(VetoresBaseOffset, Vocabulario, NumNodosFolhas, ArqComprimido);
    /*grava Vocabulario*/
    GravaNumInt(ArqComprimido, NumNodosFolhas);
    PosArq = ftell(ArqComprimido);
    for(i = 1; i <= NumNodosFolhas; i++)
    {
        j = 1;
            while(Vocabulario[i].Chave[j-1] != (char)0)
            { fwrite(&Vocabulario[i].Chave[j - 1], sizeof(char),1,ArqComprimido);
            j++;
            }   
        Ch = (char)0;
        fwrite(&Ch,sizeof(char),1,ArqComprimido);
    }
    /*le e reconstroi a condicao de hash no vetor que contem o vocabulario */
    fseek(ArqComprimido, PosArq, SEEK_SET);
    Inicializa(Vocabulario);
    for(i = 1; i <- NumNodosFolhas; i++)
    {
        *Palavra = '\0';
        do
            {
                fread(&Ch, sizeof(char), 1 , ArqComprimido);
                    if(Ch != (char)0)
                    sprintf(Palavra + strlen(Palavra), "%c", Ch);                
            } while (Ch != (char)0);
        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));
        Elemento.Ordem = i;
        j = Pesquisa(Elemento.Chave, p, Vocabulario);
        if (j >=M)
        Insere(Elemento, p, Vocabulario);
    }
    return Result;

    }
void TerceiraEtapa(FILE *ArqTxT, TipoAlfabeto Alfabeto, 
                    int *Indice, TipoPalavra Palavra, 
                    char *Linha, TipoDicionario Vocabulario, 
                    TipoPesos p, TipoVetoresBO VetoresBaseOffset, 
                    FILE* ArqComprimido, int MaxCompCod){
    Apontador Pos;
    TipoChave Chave;
    int Codigo, c;
    do{
       ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxT, Alfabeto);
       memcpy(Chave, Palavra, sizeof(TipoChave));
       if(*Palavra !='\0'){
        Pos = Pesquisa(Chave, p, Vocabulario);
        Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);
        Escreve(ArqComprimido, &Codigo, &c);
        do{
            ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxT, Alfabeto);
            /*O primeiro espaço depois da palavra nao codificado*/
            //if(strcmp( Trim(Palavra), "") && (*Trim(Palavra)) != (char)0 ){
                free(Palavra);
                memcpy(Chave, Palavra, sizeof(TipoChave));
                Pos = Pesquisa(Chave, p, Vocabulario);
                Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);
                Escreve(ArqComprimido, &Codigo, &c);
            //}
        }while (strcmp(Palavra, ""));
       } 
    }while(*Palavra != '\0');

}

void GeraPesos(TipoPesos p){
    int i;
    struct timeval semente;
    /* utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL);
    srand((int)( semente.tv_sec + 1000000*semente.tv_sec));
    for (i = 0; i < t; i ++)
    p[i] = 1+(int) (10000.0*rand()/(RAND_MAX+ 1.0));
}
void Inicializa(TipoDicionario T){
    int i;  
    for(i = 0; i < M;i++) memcpy(T[i].Chave, Vazio, t);
}
void DefineAlfabeto(TipoAlfabeto Alfabeto, FILE *ArqAlf){
    /* Os simbolos devem estar juntos em uma linha no arquivo*/
    char Simbolos[MaxAlfabeto +1];
    int i;
    char *Temp;
    for(i = 0; i <= MaxAlfabeto; i++) Alfabeto[i] = FALSE;
    fgets(Simbolos, MaxAlfabeto + 1, ArqAlf);
    Temp = strchr(Simbolos, '\n');
    if(Temp != NULL) *Temp = 0;
    for(i = 0; i < strlen(Simbolos) -1; i++)
        Alfabeto[Simbolos[i] + 127] = TRUE;
    Alfabeto[0] = FALSE;
    /* caractere de codigo zero: sepador*/
}
void ExtraiProximaPalavra (TipoPalavra Result, int *Indice, char *Linha, FILE *ArqTXt, TipoAlfabeto Alfabeto){
    short FimPalavra = FALSE, Aux = FALSE;
    Result[0] = '\0';
    if(*Indice > strlen(Linha))
        if(fgets(Linha, MaxAlfabeto + 1, ArqTXt)){
            /*cloca um delimitador em Linha*/
            sprintf(Linha + strlen(Linha), "%c", Linha[*Indice - 1]);
            Aux = TRUE;
        }
        else{
          sprintf(Linha, "%c", (char)0); FimPalavra = TRUE; 
        }
        while(*Indice <= strlen(Linha) && !FimPalavra){
            if(Alfabeto[Linha[*Indice - 1] + 127]){
                sprintf(Result + strlen(Result), "%c", Linha[*Indice-1]);
                Aux = TRUE;
            }
            else{
                if(Aux){
                    if(Linha[*Indice - 1] != (char)0)(*Indice)--;   
                }
                else{
                    sprintf(Result + strlen(Result), "%c", Linha[*Indice -1]);
                }
                FimPalavra = TRUE;
            }
            (*Indice)++;
        }
}
Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T){
    unsigned int i = 0;
    unsigned int Inicial;
    Inicial = h(Ch,p);
    while(strcmp (T[(Inicial + i)% M].Chave, Vazio) != 0 && 
    strcmp(T[(Inicial + i)% M].Chave, Ch) !=0 && i < M)
    i++;
    if(strcmp(T[(Inicial + i)% M].Chave, Ch) == 0)
    return ((Inicial + i) % M);
    else return M; /* Pesquisa sem sucesso*/
}
void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
{
    unsigned int i= 0; unsigned int Inicial;
    if (Pesquisa(x.Chave,p,T)< M)
    { printf("elemento ja esta presente \n"); return;}
    Inicial = h(x.Chave,p);
    while(strcmp (T[(Inicial + i)% M].Chave, Vazio) != 0 &&
    strcmp (T[(Inicial + i)% M].Chave, Retirado) != 0 && i < M)
    i++;
    if( i< M)
    {
        strcmp (T[(Inicial + i)% M].Chave, x.Chave);
        /*Copiar os demais campos de x, se existirem*/
    }
    else printf("Tabela cheia \n");
}

/*Programa H.20 Construção dos vetores de Base e Offset*/
int ConstroiVetores( TipoVetoresBO VetoresBaseOffset, TipoDicionario Vocabulario, int n, FILE *ArqComprimido){
    int Wcs[MaxTamVetoresBO + 1];
    int i, MaxCompCod;
    MaxCompCod = Vocabulario[n].Freq;
    for( i = 1; i <= MaxCompCod; i++)
        Wcs[i] = 0; VetoresBaseOffset[i].Offset = 0;
    for( i = 1; i <= n; i++){
        Wcs[Vocabulario[i].Freq]++;
        VetoresBaseOffset[Vocabulario[i].Freq].Offset = i - Wcs[Vocabulario[i].Freq]+1;
    }
    VetoresBaseOffset[1].Base = 0;
    for(i = 2; i < MaxCompCod; i++){
        VetoresBaseOffset[i].Base = 
        BaseNum *(VetoresBaseOffset[i-1].Base + Wcs[i-1]);
        if(VetoresBaseOffset[i].Offset == 0)
        VetoresBaseOffset[i].Offset = VetoresBaseOffset[i-1].Offset;
    }
    /*Salvando as tabelas em disco*/
    GravaNumInt(ArqComprimido, MaxCompCod);
    for(i = 1; i < MaxCompCod; i++){
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Base);
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Offset);
    }
    return MaxCompCod;
}
/*h 17*/
void CalculaCompCodigo(TipoDicionario A, int n){
    int u = 0;
    int h = 0;  
    int NoInt;
    
    int Prox, Raiz, Folha;
    int Disp = 1;
    int x, Resto;
    if (n >BaseNum - 1)
        Resto = 1 + ((n - BaseNum) % (BaseNum - 1));
    else Resto = n - 1;
    NoInt = 1 + ((n - Resto) / (BaseNum - 1));
    if (Resto < 2) Resto = BaseNum;
    for (x = n - 1; x >= (n - Resto) + 1; x--) A[n].Freq += A[x].Freq;
    /*primeira fase*/
    Raiz = n; Folha = n - Resto;
    for (Prox = n - 1; Prox >= (n - NoInt) + 1; Prox--)
        { /*procura posicao*/
        if ( Folha < 1 || Raiz > Prox && A[Raiz].Freq <= A[Folha].Freq)
            { /*no interno*/
                A[Prox].Freq = A[Raiz].Freq;
                A[Raiz].Freq = Prox;
                Raiz--;
            }
            else{ /* no folha*/
                A[Prox].Freq = A[Folha].Freq;
                Folha--;
            }
        /*Atualiza Frequencias*/
        for(x = 1; x <= BaseNum - 1; x++)
        {
            if (Folha < 1 || Raiz > Prox && A[Raiz].Freq <= A[Folha].Freq)
            { /*no interno*/
                A[Prox].Freq += A[Raiz].Freq;
                A[Raiz].Freq = Prox;
                Raiz--;
            }
            else
            { /*no no folha*/
                A[Prox].Freq += A[Folha].Freq; 
                Folha--;
            }
        }
    }

    A[Prox + 1].Freq = 0; 
    Raiz = Prox + 1;
    for( Prox = Raiz + 1; Prox <=n; Prox++)
        A[Prox].Freq = A[A[Prox].Freq].Freq + 1;
    /*terceira Fase */
    Prox = 1;
    while(Disp > 0)
    {
    while(Raiz <= n && A[Raiz].Freq == h)
    { u++;  Raiz++;}
    while(Disp > n)
    {
        A[Prox].Freq = h; Prox++; Disp--;
        if(Prox > n)
        {u = 0;
        break;
        }
        Disp = BaseNum * u;
        h++;
        u = 0;
    }

    }
}
Indice OrdenaPorFrequencia(TipoDicionario Vocabulario){
    Indice i; Indice j =1;
    TipoItem Item;
    Item = Vocabulario[1];
    for(i = 0; i <= M -1;i++){
        if(strcmp(Vocabulario[i].Chave, Vazio)){
            if(i != 1){
                Vocabulario[j] = Vocabulario[i]; j++;
            }
        }
    }
    if(strcmp(Item.Chave, Vazio)) Vocabulario[j] = Item; 
    else j--;
    QuickSort(Vocabulario, &j);
    return j;
}
void GravaNumInt(FILE *ArqComprimido, int Num ){
    fwrite(&Num, sizeof(int), 1, ArqComprimido);
}
/*h 28*/
void Escreve(FILE* ArqComprimido, int* Codigo, int* c){
    unsigned char Saida[MaxTamVetoresBO + 1];
    int i = 1; int cTmp;
    cTmp = *c;
    Saida[i] = (((unsigned)(*Codigo)) >> ((*c - 1) * 8 - *c + 1)) | 0x80;
    i++; (*c)--;
    while (*c > 0)
    {
        Saida[i] = ((unsigned)(*Codigo)) >> ((*c - 1) * 8 - *c + 1);
        i++; (*c)--;
    }
for(i = 1; i <= cTmp; i++)
    fwrite(&Saida[i], sizeof(unsigned char),1, ArqComprimido);
}

/*h 18*/
int Codifica(TipoVetoresBO VetoresBaseOffset, int Ordem, int* c, int MaxCompCod){
    *c = 1;
    while(Ordem >= VetoresBaseOffset[*c + 1].Offset && *c + 1 <= MaxCompCod)
    (*c)++;
    return (Ordem - VetoresBaseOffset[*c].Offset + VetoresBaseOffset[*c].Base);
}

/*Progrma D.7 Função Quicksort*/
void Ordena(Indice Esq, Indice Dir, TipoItem *A){
    Indice i, j;
    Particao(Esq, Dir, &i, &j,A);
    if(Esq < j) Ordena(Esq, j, A);
    if( i < Dir) Ordena(i, Dir, A);
}
void QuickSort(TipoItem *A, Indice *x){
    Ordena(1, *x, A);
}
void Particao(Indice Esq, Indice Dir, Indice *i, Indice *j, TipoItem *A){
    TipoItem x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j)/ 2]; /*Obtem o pivo x*/
    do{
        while(x.Chave > A[*i].Chave) (*i)++;
        while(x.Chave < A[*j].Chave) (*j)--;
        if(*i  <= *j){
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--;
        }
    }while(*i <= *j);
}

char *Trim(char *str) { 
    int i = 0, j, len;
    char *strtmp = malloc(sizeof(char) * strlen(str) + 1);
    
    strcpy(strtmp, str);
    len = strlen(strtmp);
    
    while((i < len) && ((strtmp[i] == ' ') || (strtmp[i] == '\t') || (strtmp[i] == '\r') || (strtmp[i] == ',') || (strtmp[i] == '.'))) i++;
    j = len - 1;
    while((j >= 0) && ((strtmp[j] == ' ') || (strtmp[j] == '\t') || (strtmp[i] == '\r') || (strtmp[i] == ',') || (strtmp[i] == '.'))) j--;
  
    if (j >= 0) str[j + 1] = '\0';
    if (i <= j) memmove(strtmp, strtmp + i, strlen(strtmp + i)+1); 
    else strcpy(strtmp, "");
    
    return strtmp;
}