#ifndef part1_H
#define part1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

int le_arquivo(FILE* arq, char* texto);
int shiftand (const char *p, const char *t);
void* aux_func(void* param);
static int distance (const char * word1, int len1, const char * word2, int len2);
void separa_palavras(char *texto, char *padrao);
void dist_main();
void sa_main();
#endif