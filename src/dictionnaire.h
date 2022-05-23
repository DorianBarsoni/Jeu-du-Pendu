#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <stdio.h>

typedef struct
{
    char** dictionnaire;
    int taille;
}dictionnaire;

dictionnaire initDic();
char* selectWord();
void freeDic(dictionnaire dic);

#endif