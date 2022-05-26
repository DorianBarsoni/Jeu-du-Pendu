#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "dictionnaire.h"
#include "jeu.h"

Jeu initJeu()
{
    //Création de l'objet
    Jeu jeu;

    //Initialisation du mot et du mot caché
    jeu.word = selectWord();
    jeu.hiddenWord = (char*) malloc((strlen(jeu.word) + 1)*sizeof(char));
    for(int i=0; i<strlen(jeu.word); i++)
    {
        jeu.hiddenWord[i] = '_';
    }
    jeu.hiddenWord[strlen(jeu.word)] = 0;

    //Initialisation du nombre de vie et du nombre de lettres trouvées
    jeu.lives = 10;
    jeu.lettersFound = 0;

    //Initialisation des lettres déjà trouvées
    for(int i=0; i<26; i++) jeu.lettres[i] = 0;

    return jeu;
}

void affiche(Jeu jeu)
{
    printf("%s\n", jeu.word);
    printf("%s\n", jeu.hiddenWord);
    printf("%d %d\n", jeu.lives, jeu.lettersFound);
    for(int i=0; i<26; i++) printf("%d ", jeu.lettres[i]);
    printf("\n");
}

bool isIn(char c, char* word)
{
    int i = 0;
    while(*(word + i) != 0)
    {
        if(c == *(word + i)) return true;
        i++;
    }
    return false;
}

Jeu nextTurn(Jeu jeu, char letter)
{
    //Si la lettre n'est pas comprise entre 'a' et 'z' on arrête ici
    if((letter < 97) || (letter > 122))
    {
        printf("mauvais caractere\n");
        return jeu;
    }
    
    //Si la lettre est déjà découverte
    if(alreadyEnter(jeu, letter))
    {
        printf("! Lettre deja entree !\n"); //On ne fait rien
    }
    //Sinon si elle est présent dans le mot à trouver
    else if(isIn(letter, jeu.word))
    {
        //On l'affiche, on incrémente le nombre de lettres trouvées et on met à jour le tableau des lettres entrées
        for(int i=0; i<strlen(jeu.word); i++)
        {
            if(letter == jeu.word[i])
            {
                jeu.hiddenWord[i] = letter;
                jeu.lettersFound++;;
            }
        }
        jeu.lettres[letter-97] = 1;
    }
    //Sinon on retire une vie au joueur et on met à jour le tableau des lettres entrées
    else
    {
        jeu.lives--;
        jeu.lettres[letter-97] = 1;
    } 

    //Affichage du mot caché
    //printf("%s\n", jeu.word);
    printf("%s\n", jeu.hiddenWord);

    //On affiche le nombre de vie
    printf("Vies : %d\n", jeu.lives);
    
    printf("\n\n\n");

    return jeu;
}

int alreadyEnter(Jeu jeu, int lettre)
{
    if(jeu.lettres[lettre-97]) return 1;
    else return 0;
}

void freeJeu(Jeu jeu)
{
    free(jeu.word);
    free(jeu.hiddenWord);
}