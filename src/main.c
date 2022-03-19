//gcc src/main.c src/dictionnaire.c src/jeu.c -o bin/main -I include -L lib -lmingw32 -lSDL2main -lSDL2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "dictionnaire.h"
#include "jeu.h"

void emptyBufferKeyboard()
{
    int l;
    while((l=getchar()) != '\n' && l != EOF);
}

int main()
{
    srand((unsigned)time(NULL));

    launchGame();
    
    printf("\nPressez n'importe quelle touche pour finir le jeu ");
    getchar();
    
    return EXIT_SUCCESS;
}