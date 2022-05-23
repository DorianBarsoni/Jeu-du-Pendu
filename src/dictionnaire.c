#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dictionnaire.h"

dictionnaire initDic()
{
    dictionnaire dic;
    dic.taille = 42;
    dic.dictionnaire = (char**) malloc(dic.taille*sizeof(char*));
    dic.dictionnaire[0] = "arbre";
    dic.dictionnaire[1] = "chaussure";
    dic.dictionnaire[2] = "lion";
    dic.dictionnaire[3] = "eclair";
    dic.dictionnaire[4] = "soupirer";
    dic.dictionnaire[5] = "developpement";
    dic.dictionnaire[6] = "angle";
    dic.dictionnaire[7] = "armoir";
    dic.dictionnaire[8] = "banc";
    dic.dictionnaire[9] = "bureau";
    dic.dictionnaire[10] = "cabinet";
    dic.dictionnaire[11] = "carreau";
    dic.dictionnaire[12] = "chaise";
    dic.dictionnaire[13] = "classe";
    dic.dictionnaire[14] = "clef";
    dic.dictionnaire[15] = "coin";
    dic.dictionnaire[16] = "couloir";
    dic.dictionnaire[17] = "dossier";
    dic.dictionnaire[18] = "eau";
    dic.dictionnaire[19] = "ecole";
    dic.dictionnaire[20] = "entrer";
    dic.dictionnaire[21] = "escalier";
    dic.dictionnaire[22] = "etagere";
    dic.dictionnaire[23] = "exterieur";
    dic.dictionnaire[24] = "fenetre";
    dic.dictionnaire[25] = "interieur";
    dic.dictionnaire[26] = "lavabo";
    dic.dictionnaire[27] = "lit";
    dic.dictionnaire[28] = "marche";
    dic.dictionnaire[29] = "matelas";
    dic.dictionnaire[30] = "meuble";
    dic.dictionnaire[31] = "mur";
    dic.dictionnaire[32] = "mousse";
    dic.dictionnaire[33] = "plafond";
    dic.dictionnaire[34] = "porte";
    dic.dictionnaire[35] = "radiateur";
    dic.dictionnaire[36] = "robinet";
    dic.dictionnaire[37] = "lampe";
    dic.dictionnaire[38] = "serrure";
    dic.dictionnaire[39] = "serviette";
    dic.dictionnaire[40] = "tableau";
    dic.dictionnaire[41] = "tapis";

    return dic;
}

char* selectWord()
{
    dictionnaire dic = initDic();
    char* word = *(dic.dictionnaire + rand()%dic.taille);
    freeDic(dic); //On libère la mémoire prise par le dictionnaire
    return word;
}

void freeDic(dictionnaire dic)
{
    free(dic.dictionnaire);
}