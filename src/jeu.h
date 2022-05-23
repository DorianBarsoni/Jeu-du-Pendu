#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char *word, *hiddenWord;
    int lives, lettersFound;
    int lettres[26];
}Jeu;

Jeu initJeu();
void affiche(Jeu jeu);
bool isIn(char c, char* word);
Jeu nextTurn(Jeu jeu, char letter);
void freeJeu(Jeu jeu);

#endif