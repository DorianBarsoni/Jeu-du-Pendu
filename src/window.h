//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "dictionnaire.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

//Tableau contenant les pos et les tailles des lettres
SDL_Rect lettres[26];
//Tableau contenant les pos et les taille des lettres du mot
SDL_Rect *word;//
//Tableau contenant les positions des lettres du mot sur le rendu
SDL_Rect *pos;//
char *hiddenWord;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Rect rectangle;
SDL_Event event;
bool running;
bool dir[4];
bool over = false;
int lettre;

void exitWithError(char* error);
void initLettres();
void initWindow();
void loadSprite(char* sprite);
void setSpritePos(int x, int y);
void setSpriteSize(int w, int h);
void initVariables();
void treatEvents(SDL_Event event);
void updateSpritePos();
void checkMouseOver(SDL_Rect rec);
void printRenderer(SDL_Texture* tex, SDL_Rect* sprite, SDL_Rect* pos, int size);
void changeLetter(int i);

#endif