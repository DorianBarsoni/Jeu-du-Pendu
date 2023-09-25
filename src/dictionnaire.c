#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dictionnaire.h"

dictionnaire initDic()
{
    dictionnaire dic;

    //C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu
    FILE* fichier = fopen("..\\mots.txt", "r");
    if(fichier == NULL)
    {
        printf("No such file\n");
        FILE* err = fopen("error.txt", "w");
        if(err == NULL)
        {
            printf("Unable to create file\n");
            exit(0);
        }
        fputs("Aucun fichier mots.txt dans le répertoire Jeu-du-Pendu", err);
        fclose(err);
        exit(0);
    }

    char buf[100];
    int i = 0;
    while (fscanf(fichier,"%s", buf) == 1)
    {
        i++;
    }
    
    dic.taille = i;
    dic.dictionnaire = (char**) malloc(dic.taille*sizeof(char*));

    fclose(fichier);
    fichier = fopen("..\\mots.txt", "r");
    if(fichier == NULL) 
    {
        printf("No such file\n");
        FILE* err = fopen("error.txt", "w");
        if(err == NULL)
        {
            printf("Unable to create file\n");
            exit(0);
        }
        fputs("Aucun fichier mots.txt dans le répertoire Jeu-du-Pendu", err);
        fclose(err);
        exit(0);
    }

    i=0;
    while (fscanf(fichier,"%s", buf) == 1)
    {
        dic.dictionnaire[i] = (char*) malloc((strlen(buf)+1)*sizeof(char));
        strcpy(dic.dictionnaire[i], buf);
        i++;
    }
    fclose(fichier);

    return dic;
}

char* selectWord()
{
    dictionnaire dic = initDic();
    char* word = (char*) malloc(30*sizeof(char));
    strcpy(word, *(dic.dictionnaire + rand()%dic.taille));
    freeDic(dic); //On libère la mémoire prise par le dictionnaire
    return word;
}

void freeDic(dictionnaire dic)
{
    for(int i=0; i<dic.taille; i++)
    {
        free(dic.dictionnaire[i]);
    }
    free(dic.dictionnaire);
}