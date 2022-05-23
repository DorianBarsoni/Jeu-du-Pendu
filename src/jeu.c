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
    char *tmp = selectWord();
    jeu.word = (char*) malloc((strlen(tmp) + 1)*sizeof(char));
    jeu.hiddenWord = (char*) malloc((strlen(tmp) + 1)*sizeof(char));
    for(int i=0; i<strlen(tmp); i++)
    {
        jeu.word[i] = tmp[i];
        jeu.hiddenWord[i] = '_';
    }
    jeu.word[strlen(tmp)] = 0;
    jeu.hiddenWord[strlen(tmp)] = 0;

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

Jeu nextTurn(Jeu jeu)
{
    //Affichage du mot caché
    printf("%s\n", jeu.word);
    printf("%s\n", jeu.hiddenWord);

    //Nombre de lettres trouvé + vie
    char letter;

    //On affiche le nombre de vie
    printf("Vies : %d\n", jeu.lives);

    //Tant que la lettre entrée n'est pas entre 'a' et 'z' ou entre 'A' et 'Z'
    while( !(97 <= letter && letter <= 122) )
    {
        printf("Choisissez une lettre : ");
        scanf("%c", &letter); //On fait entrer un caractère à l'utilisateur
        if(65 <= letter && letter <= 90) letter += 32; //Si la lettre est une majuscule on la met en minuscule
        if(!(97 <= letter && letter <= 122)) while((letter=getchar()) != '\n' && letter != EOF);; //On vide le buffer clavier si la lettre entrée n'est pas entre 'a' et 'z'
    }
    
    //Si la lettre est déjà découverte
    if(jeu.lettres[letter-97])
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
    
    printf("\n\n\n");
    while((letter=getchar()) != '\n' && letter != EOF); //On vide le buffer clavier

    return jeu;
}

void freeJeu(Jeu jeu)
{
    free(jeu.word);
    free(jeu.hiddenWord);
}