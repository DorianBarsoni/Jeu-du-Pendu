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
#define WINDOW_HEIGHT 1000

#define LETTER_SIZE 2.5
#define WORD_SIZE 1
#define FIGURE_SIZE 1
#define HEART_SIZE 1
#define FOUND_SIZE 0.45
#define NOTIF_SIZE 0.6

typedef struct {
    //Tableau contenant les pos et les tailles des lettres
    SDL_Rect lettres[28];
    //Tableau contenant les pos et les tailles des chiffres
    SDL_Rect chiffres[10];
    //Tableau contenant les pos et les taille des lettres du mot
    SDL_Rect *word;//
    //Tableau contenant les positions des lettres du mot sur le rendu
    SDL_Rect *pos;//
    //Tableau contenant les positions des notifications
    SDL_Rect *size_notif, *pos_notif;//

    //Lettres restantes
    SDL_Rect size_found[26]; SDL_Rect pos_found[26];

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
    SDL_Texture *tex_chiffres; SDL_Rect pos_chiffres[2];
    //Coeur
    SDL_Texture* tex_coeur; SDL_Rect size_coeur; SDL_Rect pos_coeur;
    //Bordures
    SDL_Texture* tex_bordures; SDL_Rect size_bordures; SDL_Rect pos_bordures; SDL_Rect size_word_bordures; SDL_Rect pos_word_bordures; SDL_Rect pos_notif_bordures; SDL_Rect size_notif_bordures;
    
    //Évènement
    SDL_Event event;
    //Booléen d'arrêt de la fenêtre
    bool running;
    //Dernière lettre sélectionnée
    int lettre;
}Window;


int myWindow();
void display();
void exitWithError(char* error);
void initLettresEtChiffres();
void initWindow();
SDL_Texture* loadSprite(char* sprite);
void setSpritePos(int x, int y, SDL_Rect* rec);
void setSpriteSize(int w, int h, SDL_Texture* tex, SDL_Rect* rec);
void initVariables();
void treatEvents(SDL_Event event);
void printRenderer(SDL_Texture* tex, SDL_Rect* sprite, SDL_Rect* pos, int size);
void changeLetter(int i);
void changeChiffres(int i);
void loadHiddenWord(char *loadHiddenWord);
void separeNum(int num, int *val);
void initFoundLetters();
void updateFoundLetters();
void loadNotif(char* txt);
void setWordBordure();
void setNotifBordure(char* txt);

#endif