//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#include "window.h"

Jeu mjeu;

int main(int argc, char** argv)
{
    initLettres();
    initWindow();
    loadSprite("C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu\\images\\lettres.bmp");
    setSpritePos(WINDOW_WIDTH/2 - lettres[lettre].w/2, WINDOW_HEIGHT/2 - lettres[lettre].h/2);
    setSpriteSize(lettres[lettre].w, lettres[lettre].h);
    initVariables();
    int i=0;

    //Chargement du mot
    mjeu = initJeu();
    loadHiddenWord(mjeu);
    currentLetter = 'a';

    while(running)
    {
        treatEvents(event);
        updateSpritePos();
        checkMouseOver(rectangle);
        
        SDL_RenderClear(renderer);
        printRenderer(texture, &lettres[lettre], &rectangle, 1);
        printRenderer(texture, word, pos, strlen(hiddenWord));
        SDL_RenderPresent(renderer);
        if(i%4 == 0) SDL_Delay(1);
        i++;

        if(mjeu.lives == 0 || mjeu.lettersFound == strlen(mjeu.word))
        {
            /*jeu = initJeu();
            loadHiddenWord(jeu);
            SDL_RenderClear(renderer);
            printRenderer(texture, &lettres[lettre], &rectangle, 1);
            printRenderer(texture, word, pos, strlen(hiddenWord));
            SDL_RenderPresent(renderer);*/
            running = false;
        }
    }

    printf("Le mot etait : %s\n", mjeu.word);

    //Libération de la mémoire allouée
    freeJeu(mjeu);
    free(word);
    free(pos);
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
    lettres[26].x=1286; lettres[26].y=0; lettres[26].w=38; lettres[26].h=larg; //_
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
                            changeLetter(0);
                            currentLetter = 'a';
                            printf("A\n");
                            break;
                        case SDLK_b :
                            changeLetter(1);
                            currentLetter = 'b';
                            printf("B\n");
                            break;
                        case SDLK_c :
                            changeLetter(2);
                            currentLetter = 'c';
                            printf("C\n");
                            break;
                        case SDLK_d :
                            changeLetter(3);
                            currentLetter = 'd';
                            printf("D\n");
                            break;
                        case SDLK_e :
                            changeLetter(4);
                            currentLetter = 'e';
                            printf("E\n");
                            break;
                        case SDLK_f :
                            changeLetter(5);
                            currentLetter = 'f';
                            printf("F\n");
                            break;
                        case SDLK_g :
                            changeLetter(6);
                            currentLetter = 'g';
                            printf("G\n");
                            break;
                        case SDLK_h :
                            changeLetter(7);
                            currentLetter = 'h';
                            printf("H\n");
                            break;
                        case SDLK_i :
                            changeLetter(8);
                            currentLetter = 'i';
                            printf("I\n");
                            break;
                        case SDLK_j :
                            changeLetter(9);
                            currentLetter = 'j';
                            printf("J\n");
                            break;
                        case SDLK_k :
                            changeLetter(10);
                            currentLetter = 'k';
                            printf("K\n");
                            break;
                        case SDLK_l :
                            changeLetter(11);
                            currentLetter = 'l';
                            printf("L\n");
                            break;
                        case SDLK_m :
                            changeLetter(12);
                            currentLetter = 'm';
                            printf("M\n");
                            break;
                        case SDLK_n :
                            changeLetter(13);
                            currentLetter = 'n';
                            printf("N\n");
                            break;
                        case SDLK_o :
                            changeLetter(14);
                            currentLetter = 'o';
                            printf("O\n");
                            break;
                        case SDLK_p :
                            changeLetter(15);
                            currentLetter = 'p';
                            printf("P\n");
                            break;
                        case SDLK_q :
                            changeLetter(16);
                            currentLetter = 'q';
                            printf("Q\n");
                            break;
                        case SDLK_r :
                            changeLetter(17);
                            currentLetter = 'r';
                            printf("R\n");
                            break;
                        case SDLK_s :
                            changeLetter(18);
                            currentLetter = 's';
                            printf("S\n");
                            break;
                        case SDLK_t :
                            changeLetter(19);
                            currentLetter = 't';
                            printf("T\n");
                            break;
                        case SDLK_u :
                            changeLetter(20);
                            currentLetter = 'u';
                            printf("U\n");
                            break;
                        case SDLK_v :
                            changeLetter(21);
                            currentLetter = 'v';
                            printf("V\n");
                            break;
                        case SDLK_w :
                            changeLetter(22);
                            currentLetter = 'w';
                            printf("W\n");
                            break;
                        case SDLK_x :
                            changeLetter(23);
                            currentLetter = 'x';
                            printf("X\n");
                            break;
                        case SDLK_y :
                            changeLetter(24);
                            currentLetter = 'y';
                            printf("Y\n");
                            break;
                        case SDLK_z :
                            changeLetter(25);
                            currentLetter = 'z';
                            printf("Z\n");
                            break;
                        case SDLK_8 :
                            changeLetter(26);
                            printf("_\n");
                            break;
                        case SDLK_RETURN :
                            mjeu = nextTurn(mjeu, currentLetter);
                            loadHiddenWord(mjeu);
                            printf("ENTRER\n");
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
    //if(dir[0] || dir[1] || dir[2] || dir[3]) printf("Coordonnees : %d %d\n", rectangle.x, rectangle.y);
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
void printRenderer(SDL_Texture* tex, SDL_Rect* sprite, SDL_Rect* pos, int size)
{
    for(int i=0; i<size; i++)
    {
        if(SDL_RenderCopy(renderer, tex, &(sprite[i]), &(pos[i])) != 0)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            exitWithError("Chargement texture sur rendu");
        }
    }
}

void changeLetter(int i)
{
    lettre = i;
    setSpriteSize(lettres[lettre].w, lettres[lettre].h);
}

void loadHiddenWord(Jeu jeu)
{
    //Chargement du mot
    hiddenWord = jeu.hiddenWord;
    //Initialisation des variables des lettres et de leur pos
    word = (SDL_Rect*) malloc(strlen(hiddenWord)*sizeof(SDL_Rect));
    pos = (SDL_Rect*) malloc(strlen(hiddenWord)*sizeof(SDL_Rect));
    //Pour chaque lettre on définit sa position dans texture et sa position sur le render
    int spriteLenght = 0;
    for(int i=0; i<strlen(hiddenWord); i++)
    {
        int num;
        if(hiddenWord[i] == '_') num = 26;
        else num = hiddenWord[i] - 97;
        word[i].x = lettres[num].x;
        word[i].y = lettres[num].y;
        word[i].w = lettres[num].w;
        word[i].h = lettres[num].h;
        spriteLenght += word[i].w + 5;
    }
    for(int i=0; i<strlen(hiddenWord); i++)
    {
        if(i != 0)
        {
            pos[i].x = pos[i-1].x + pos[i-1].w + 5;
        }
        else
        {
            pos[i].x = WINDOW_WIDTH/2 - spriteLenght/2;
        }
        pos[i].y = 30;
        pos[i].w = word[i].w;
        pos[i].h = word[i].h;
    }
}