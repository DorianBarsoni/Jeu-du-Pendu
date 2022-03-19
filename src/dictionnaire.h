#include <stdio.h>

typedef struct
{
    char** dictionnaire;
    int taille;
}dictionnaire;

dictionnaire initDic();
char* selectWord();
void freeDic(dictionnaire dic);
void printWord(char* word);