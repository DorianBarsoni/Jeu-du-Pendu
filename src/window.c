//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Rect rectangle;
SDL_Event event;
bool running;
bool dir[4];
bool over = false;

void exitWithError(char* error);
void initWindow();
void loadSprite(char* sprite);
void setSpritePos(int x, int y);
void setSpriteSize(int w, int h);
void initVariables();
void treatEvents(SDL_Event event);
void updateSpritePos();
void checkMouseOver(SDL_Rect rec);
void printRenderer();

int main(int argc, char** argv)
{
    initWindow();
    loadSprite("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\bleu.bmp");
    setSpritePos(WINDOW_WIDTH/2 - 100/2, WINDOW_HEIGHT/2 - 100/2);
    setSpriteSize(-1, -1);
    initVariables();
    int i=0;

    while(running)
    {
        treatEvents(event);
        updateSpritePos();
        checkMouseOver(rectangle);
        
        printRenderer();
        if(i%4 == 0) SDL_Delay(1);
        i++;
    }

    //Libération de la mémoire allouée
    SDL_DestroyTexture(texture);
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

//Fonction initialisant la fenêtre
void initWindow()
{
    //Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) exitWithError("Initialisation Video");

    //Création de la fenêtre
    window = NULL;
    window = SDL_CreateWindow("Fenêtre test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(window == NULL) exitWithError("Creation fenetre");
    
    //Création d'un rendu
    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        SDL_DestroyWindow(window);
        exitWithError("Creation rendu");
    }

    //Création d'une surface et d'une texture
    surface = NULL;
    texture = NULL;
}

//Fonction chargeant les sprites
void loadSprite(char* sprite)
{
    surface = SDL_LoadBMP(sprite);
    if(surface == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Creation surface");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Creation texture");
    }
}

void setSpriteSize(int w, int h)
{
    //Dimensions rectangle texture
    if(w==-1 && h==-1)
    {
        if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            exitWithError("Chargement texture en memoire");
        }
    }
    else
    {
        rectangle.w = w;
        rectangle.h = h;
    }
}

void setSpritePos(int x, int y)
{
    rectangle.x = x;
    rectangle.y = y;
}

void initVariables()
{
    running = true;
    for(int i=0; i<4; i++) dir[i] = false;
    over = false;
}

//Fonction gérant les évènements
void treatEvents(SDL_Event event)
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
}

void updateSpritePos()
{
    if(dir[0] && rectangle.y>0) setSpritePos(rectangle.x, rectangle.y-1);
    if(dir[1] && (rectangle.y+100)<WINDOW_HEIGHT) setSpritePos(rectangle.x, rectangle.y+1);
    if(dir[2] && rectangle.x>0) setSpritePos(rectangle.x-1, rectangle.y);
    if(dir[3] && (rectangle.x+100)<WINDOW_WIDTH) setSpritePos(rectangle.x+1, rectangle.y);
    if(dir[0] || dir[1] || dir[2] || dir[3]) printf("Coordonnees : %d %d\n", rectangle.x, rectangle.y);
}

void checkMouseOver(SDL_Rect rec)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(rec.x<x && x<rec.x+rec.w && rec.y<y && y<rec.y+rec.h && !over)
    {
        loadSprite("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\rouge.bmp");
        over = true;
        printf("Coloration\n");
    }
    if(!(rec.x<x && x<rec.x+rec.w && rec.y<y && y<rec.y+rec.h) && over)
    {
        loadSprite("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\bleu.bmp");
        over = false;
        printf("Decoloration\n");
    }
}

//Fonction affichant le rendu sur la fenêtre
void printRenderer()
{
    SDL_RenderClear(renderer);
    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Chargement texture sur rendu");
    }
    SDL_RenderPresent(renderer);
}