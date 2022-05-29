//gcc src/main.c src/dictionnaire.c src/jeu.c src/window.c -o bin/main -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "dictionnaire.h"
#include "jeu.h"
#include "window.h"

void emptyBufferKeyboard()
{
    int l;
    while((l=getchar()) != '\n' && l != EOF);
}

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));

    myWindow();
    
    return EXIT_SUCCESS;
}