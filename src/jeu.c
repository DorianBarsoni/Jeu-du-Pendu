#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "dictionnaire.h"
#include "jeu.h"

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

void launchGame()
{
    //Sélection du mot
    
    char* word = selectWord();
    //printWord(word);

    //Longueur du mot
    int wordLength = strlen(word);
    printf("Taille : %d\n", strlen(word));

    //Création du mot caché
    char hiddenWord[wordLength + 1];
    for(int i=0; i<wordLength; i++) hiddenWord[i] = '_';
    hiddenWord[wordLength] = 0;

    //Affichage du mot caché
    printWord(hiddenWord);

    //Nombre de lettres trouvé + vie
    int letterFound = 0;
    char letter;
    int lives = 10;

    //Tant que le nombre de lettres trouvées est différent de la taille du mot et que le nombre de vie est différent de 0
    while(letterFound != wordLength && lives != 0)
    {
        printf("Vies : %d\n", lives); //On affiche les vies
        while( !(97 <= letter && letter <= 122) ) //Tant que la lettre entrée n'est pas entre 'a' et 'z'
        {
            printf("Choisissez une lettre (minuscule) : ");
            scanf("%c", &letter); //On fait entrer un caractère à l'utilisateur
            if(!(97 <= letter && letter <= 122)) while((letter=getchar()) != '\n' && letter != EOF);; //On vide le buffer clavier si la lettre entrée n'est pas entre 'a' et 'z'
        }
        
        //Si la lettre est déjà découverte
        if(isIn(letter, hiddenWord))
        {
            printf("! Lettre deja entree !\n"); //On ne fait rien
        }
        //Sinon si elle est présent dans le mot à trouver
        else if(isIn(letter, word))
        {
            //On l'affiche et on incrémente le nombre de lettres trouvées
            for(int i=0; i<wordLength; i++)
            {
                if(letter == word[i])
                {
                    hiddenWord[i] = letter;
                    letterFound++;
                }
            }
        }
        //Sinon on retire une vie au joueur
        else lives--;
        
        printf("\n\n\n");
        printWord(hiddenWord);
        while((letter=getchar()) != '\n' && letter != EOF); //On vide le buffer clavier
    }

    if(lives == 0) printf("Dommage ! Le mot etait %s !\n", word);
    else printf("Bravo ! Le mot etait %s !\n", word);
}