//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

void exitWithError(char* error);

int main(int argc, char** argv)
{
    int step = 0;

    //Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) exitWithError("Initialisation Video");

    //Création de la fenêtre
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Fenêtre test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(window == NULL) exitWithError("Creation fenetre");
    
    //Création d'un rendu
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        SDL_DestroyWindow(window);
        exitWithError("Creation rendu");
    }

    //Création d'une surface et d'une texture
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    //SDL_Surface* surface2 = NULL;
    //SDL_Texture* texture2 = NULL;


    surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\bleu.bmp");
    //surface2 = SDL_LoadBMP("images/rouge.bmp");
    if(surface == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Creation surface");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    //texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface);
    //SDL_FreeSurface(surface2);
    if(texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Creation texture");
    }

    //Charger la texture en mémoire
    SDL_Rect rectangle;
    //SDL_Rect rectangle2;
    //SDL_QueryTexture(texture2, NULL, NULL, &rectangle2.w, &rectangle2.h);
    //rectangle2.x = WINDOW_WIDTH - 100;
    //rectangle2.y = 0;
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Chargement texture en memoire");
    }
    rectangle.x = WINDOW_WIDTH/2 - 100/2;
    rectangle.y = WINDOW_HEIGHT/2 - 100/2;

    //Afficher la surface
    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Chargement texture sur rendu");
    }
    //SDL_RenderCopy(renderer, texture2, NULL, &rectangle2);

    
    bool running = true;
    SDL_Event event;
    bool dir[4];
    for(int i=0; i<4; i++) dir[i] = false;
    bool over = false;


    int x=0, y=0;
    int i=0;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    running = false;
                    break;
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_z :
                            dir[0] = true;
                            break;
                        case SDLK_s :
                            dir[1] = true;
                            break;
                        case SDLK_q :
                            dir[2] = true;
                            break;
                        case SDLK_d :
                            dir[3] = true;
                            break;
                        case SDLK_a :
                            SDL_Surface *surface = NULL;
                            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\a.bmp");
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            SDL_FreeSurface(surface);
                            printf("A\n");
                            break;
                        case SDLK_b :
                            surface = NULL;
                            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\b.bmp");
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            SDL_FreeSurface(surface);
                            printf("B\n");
                            break;
                        case SDLK_c :
                            surface = NULL;
                            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\c.bmp");
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            SDL_FreeSurface(surface);
                            printf("C\n");
                            break;
                        case SDLK_e :
                            surface = NULL;
                            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\e.bmp");
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            SDL_FreeSurface(surface);
                            printf("E\n");
                            break;
                        default :
                            break;
                    }
                    break;
                case SDL_KEYUP :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_z :
                            dir[0] = false;
                            break;
                        case SDLK_s :
                            dir[1] = false;
                            break;
                        case SDLK_q :
                            dir[2] = false;
                            break;
                        case SDLK_d :
                            dir[3] = false;
                            break;
                        default :
                            break;
                    }
                    break;
                default :
                    break;
            }
        }

        if(dir[0] && rectangle.y>0) rectangle.y--;
        if(dir[1] && (rectangle.y+100)<WINDOW_HEIGHT) rectangle.y++;
        if(dir[2] && rectangle.x>0) rectangle.x--;
        if(dir[3] && (rectangle.x+100)<WINDOW_WIDTH) rectangle.x++;
        if(dir[0] || dir[1] || dir[2] || dir[3]) printf("Coordonnees : %d %d\n", rectangle.x, rectangle.y);

        SDL_GetMouseState(&x, &y);
        if(rectangle.x<x && x<rectangle.x+100 && rectangle.y<y && y<rectangle.y+100 && !over)
        {
            SDL_Surface *surface = NULL;
            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\rouge.bmp");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            over = true;
            printf("Coloration\n");
        }
        if(!(rectangle.x<x && x<rectangle.x+100 && rectangle.y<y && y<rectangle.y+100) && over)
        {
            SDL_Surface *surface = NULL;
            surface = SDL_LoadBMP("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\bleu.bmp");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            over = false;
            printf("Decoloration\n");
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
        //SDL_RenderCopy(renderer, texture2, NULL, &rectangle2);
        SDL_RenderPresent(renderer);
        if(i%2 == 0) SDL_Delay(1);
        i++;
    }

    //Libération de la mémoire allouée
    SDL_DestroyTexture(texture);
    //SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void exitWithError(char* error)
{
    SDL_Log("|!| ERREUR |!| %s : %s", error, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}