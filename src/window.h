//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "jeu.h"
#include "dictionnaire.h"

#define WINDOW_WIDTH 1220
#define WINDOW_HEIGHT 840

typedef struct {
    //Tableau contenant les pos et les tailles des lettres
    SDL_Rect lettres[27];
    //Tableau contenant les pos et les tailles des chiffres
    SDL_Rect chiffres[10];
    //Tableau contenant les pos et les taille des lettres du mot
    SDL_Rect *word;//
    //Tableau contenant les positions des lettres du mot sur le rendu
    SDL_Rect *pos;//
    //Dernier caractère
    char currentLetter;
    //Fenêtre
    SDL_Window *window;
    //Rendu
    SDL_Renderer *renderer;
    //Surface
    SDL_Surface *surface;

    //Lettres
    SDL_Texture *texture; SDL_Rect rectangle;
    //Chiffres
    SDL_Texture *tex_chiffres; SDL_Rect size_chiffres; SDL_Rect pos_chiffres[2];
    //Coeur
    SDL_Texture* tex_coeur; SDL_Rect size_coeur; SDL_Rect pos_coeur;
    
    //Évènement
    SDL_Event event;
    //Booléen d'arrêt de la fenêtre
    bool running;
    //Tableau de booléen pour les 4 directions
    bool dir[4];
    //Booléen de passage de souris sur la lettre sélectionnée
    bool over;
    //Dernière lettre sélectionnée
    int lettre;
}Window;


int myWindow();
void display();
void exitWithError(char* error);
void initLettresEtChiffres();
void initWindow();
SDL_Texture* loadSprite(char* sprite);
void setSpritePos(int x, int y);
void setSpriteSize(int w, int h, SDL_Texture* tex, SDL_Rect* rec);
void initVariables();
void treatEvents(SDL_Event event);
void updateSpritePos();
void checkMouseOver(SDL_Rect rec);
void printRenderer(SDL_Texture* tex, SDL_Rect* sprite, SDL_Rect* pos, int size);
void changeLetter(int i);
void changeChiffres(int i);
void loadHiddenWord(char *loadHiddenWord);
void separeNum(int num, int *val);

#endif