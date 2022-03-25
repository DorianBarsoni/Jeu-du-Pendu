//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

SDL_Rect lettres[26];

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
void printRenderer();

int main(int argc, char** argv)
{
    initLettres();
    initWindow();
    loadSprite("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\lettres.bmp");
    setSpritePos(WINDOW_WIDTH/2 - 100/2, WINDOW_HEIGHT/2 - 100/2);
    setSpriteSize(38, 58);
    initVariables();
    int i=0;

    while(running)
    {
        if(i%250 == 249) lettre = (lettre+1)%26;
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

void initLettres()
{
    lettre = 0;
    int larg = 58;
    lettres[0].x=0; lettres[0].y=0; lettres[0].w=38; lettres[0].h=larg; //a
    lettres[1].x=48; lettres[1].y=0; lettres[1].w=38; lettres[1].h=larg; //b
    lettres[2].x=96; lettres[2].y=0; lettres[2].w=38; lettres[2].h=larg; //c
    lettres[3].x=144; lettres[3].y=0; lettres[3].w=38; lettres[3].h=larg; //d
    lettres[4].x=192; lettres[4].y=0; lettres[4].w=38; lettres[4].h=larg; //e
    lettres[5].x=240; lettres[5].y=0; lettres[5].w=38; lettres[5].h=larg; //f
    lettres[6].x=288; lettres[6].y=0; lettres[6].w=38; lettres[6].h=larg; //g
    lettres[7].x=336; lettres[7].y=0; lettres[7].w=38; lettres[7].h=larg; //h
    lettres[8].x=384; lettres[8].y=0; lettres[8].w=9; lettres[8].h=larg; //i
    lettres[9].x=403; lettres[9].y=0; lettres[9].w=38; lettres[9].h=larg; //j
    lettres[10].x=451; lettres[10].y=0; lettres[10].w=38; lettres[10].h=larg; //k
    lettres[11].x=499; lettres[11].y=0; lettres[11].w=38; lettres[11].h=larg; //l
    lettres[12].x=547; lettres[12].y=0; lettres[12].w=47; lettres[12].h=larg; //m
    lettres[13].x=605; lettres[13].y=0; lettres[13].w=38; lettres[13].h=larg; //n
    lettres[14].x=653; lettres[14].y=0; lettres[14].w=38; lettres[14].h=larg; //o
    lettres[15].x=701; lettres[15].y=0; lettres[15].w=38; lettres[15].h=larg; //p
    lettres[16].x=749; lettres[16].y=0; lettres[16].w=47; lettres[16].h=larg; //q
    lettres[17].x=806; lettres[17].y=0; lettres[17].w=38; lettres[17].h=larg; //r
    lettres[18].x=854; lettres[18].y=0; lettres[18].w=38; lettres[18].h=larg; //s
    lettres[19].x=902; lettres[19].y=0; lettres[19].w=47; lettres[19].h=larg; //t
    lettres[20].x=960; lettres[20].y=0; lettres[20].w=38; lettres[20].h=larg; //u
    lettres[21].x=1008; lettres[21].y=0; lettres[21].w=47; lettres[21].h=larg; //v
    lettres[22].x=1066; lettres[22].y=0; lettres[22].w=47; lettres[22].h=larg; //w
    lettres[23].x=1123; lettres[23].y=0; lettres[23].w=47; lettres[23].h=larg; //x
    lettres[24].x=1181; lettres[24].y=0; lettres[24].w=47; lettres[24].h=larg; //y
    lettres[25].x=1238; lettres[25].y=0; lettres[25].w=38; lettres[25].h=larg; //z
    for(int i=0; i<26; i++) printf("%d %d %d %d\n", lettres[i].x, lettres[i].y, lettres[i].w, lettres[i].h);
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
                        case SDLK_UP :
                            dir[0] = true;
                            break;
                        case SDLK_DOWN :
                            dir[1] = true;
                            break;
                        case SDLK_LEFT :
                            dir[2] = true;
                            break;
                        case SDLK_RIGHT :
                            dir[3] = true;
                            break;
                        case SDLK_a :
                            lettre = 0;
                            setSpriteSize(38, 58);
                            printf("A\n");
                            break;
                        case SDLK_b :
                            lettre = 1;
                            setSpriteSize(38, 58);
                            printf("B\n");
                            break;
                        case SDLK_c :
                            lettre = 2;
                            setSpriteSize(38, 58);
                            printf("C\n");
                            break;
                        case SDLK_d :
                            lettre = 3;
                            setSpriteSize(38, 58);
                            printf("D\n");
                            break;
                        case SDLK_e :
                            lettre = 4;
                            setSpriteSize(38, 58);
                            printf("E\n");
                            break;
                        case SDLK_f :
                            lettre = 5;
                            setSpriteSize(38, 58);
                            printf("F\n");
                            break;
                        case SDLK_g :
                            lettre = 6;
                            setSpriteSize(38, 58);
                            printf("G\n");
                            break;
                        case SDLK_h :
                            lettre = 7;
                            setSpriteSize(38, 58);
                            printf("H\n");
                            break;
                        case SDLK_i :
                            lettre = 8;
                            setSpriteSize(9, 58);
                            printf("I\n");
                            break;
                        case SDLK_j :
                            lettre = 9;
                            setSpriteSize(38, 58);
                            printf("J\n");
                            break;
                        case SDLK_k :
                            lettre = 10;
                            setSpriteSize(38, 58);
                            printf("K\n");
                            break;
                        case SDLK_l :
                            lettre = 11;
                            setSpriteSize(38, 58);
                            printf("L\n");
                            break;
                        case SDLK_m :
                            lettre = 12;
                            setSpriteSize(47, 58);
                            printf("M\n");
                            break;
                        case SDLK_n :
                            lettre = 13;
                            setSpriteSize(38, 58);
                            printf("N\n");
                            break;
                        case SDLK_o :
                            lettre = 14;
                            setSpriteSize(38, 58);
                            printf("O\n");
                            break;
                        case SDLK_p :
                            lettre = 15;
                            setSpriteSize(38, 58);
                            printf("P\n");
                            break;
                        case SDLK_q :
                            lettre = 16;
                            setSpriteSize(47, 58);
                            printf("Q\n");
                            break;
                        case SDLK_r :
                            lettre = 17;
                            setSpriteSize(38, 58);
                            printf("R\n");
                            break;
                        case SDLK_s :
                            lettre = 18;
                            setSpriteSize(38, 58);
                            printf("S\n");
                            break;
                        case SDLK_t :
                            lettre = 19;
                            setSpriteSize(47, 58);
                            printf("T\n");
                            break;
                        case SDLK_u :
                            lettre = 20;
                            setSpriteSize(38, 58);
                            printf("U\n");
                            break;
                        case SDLK_v :
                            lettre = 21;
                            setSpriteSize(47, 58);
                            printf("V\n");
                            break;
                        case SDLK_w :
                            lettre = 22;
                            setSpriteSize(47, 58);
                            printf("W\n");
                            break;
                        case SDLK_x :
                            lettre = 23;
                            setSpriteSize(47, 58);
                            printf("X\n");
                            break;
                        case SDLK_y :
                            lettre = 24;
                            setSpriteSize(47, 58);
                            printf("Y\n");
                            break;
                        case SDLK_z :
                            lettre = 25;
                            setSpriteSize(38, 58);
                            printf("Z\n");
                            break;
                        default :
                            break;
                    }
                    break;
                case SDL_KEYUP :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP :
                            dir[0] = false;
                            break;
                        case SDLK_DOWN :
                            dir[1] = false;
                            break;
                        case SDLK_LEFT :
                            dir[2] = false;
                            break;
                        case SDLK_RIGHT :
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
    if(dir[1] && (rectangle.y+lettres[lettre].h)<WINDOW_HEIGHT) setSpritePos(rectangle.x, rectangle.y+1);
    if(dir[2] && rectangle.x>0) setSpritePos(rectangle.x-1, rectangle.y);
    if(dir[3] && (rectangle.x+lettres[lettre].w)<WINDOW_WIDTH) setSpritePos(rectangle.x+1, rectangle.y);
    if(dir[0] || dir[1] || dir[2] || dir[3]) printf("Coordonnees : %d %d\n", rectangle.x, rectangle.y);
}

void checkMouseOver(SDL_Rect rec)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(rec.x<x && x<rec.x+rec.w && rec.y<y && y<rec.y+rec.h && !over)
    {
        over = true;
        printf("Coloration\n");
    }
    if(!(rec.x<x && x<rec.x+rec.w && rec.y<y && y<rec.y+rec.h) && over)
    {
        over = false;
        printf("Decoloration\n");
    }
}

//Fonction affichant le rendu sur la fenêtre
void printRenderer()
{
    SDL_RenderClear(renderer);
    if(SDL_RenderCopy(renderer, texture, &lettres[lettre], &rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exitWithError("Chargement texture sur rendu");
    }
    SDL_RenderPresent(renderer);
}