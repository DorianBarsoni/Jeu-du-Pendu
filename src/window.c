//gcc src/window.c -o bin/window -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
#include "window.h"

Jeu jeu;
Window mwindow;
bool notif_vie = false;

int myWindow()
{
    //C:\\Users\\dbars\\Documents\\GitHub\\Jeu-du-Pendu
    initLettresEtChiffres();
    initFoundLetters();
    initWindow();
    mwindow.texture = loadSprite("..\\images\\lettres.bmp");
    mwindow.tex_chiffres = loadSprite("..\\images\\chiffres.bmp");
    mwindow.tex_coeur = loadSprite("..\\images\\coeur.bmp");
    mwindow.tex_bordures = loadSprite("..\\images\\bordures.bmp");
    mwindow.tex_potence = loadSprite("..\\images\\potences.bmp");
    mwindow.tex_pendu = loadSprite("..\\images\\pendus.bmp");
    setSpritePos((WINDOW_WIDTH-mwindow.lettres[mwindow.lettre].w*LETTER_SIZE)*0.85, WINDOW_HEIGHT/2 - mwindow.lettres[mwindow.lettre].h*LETTER_SIZE/2, &mwindow.rectangle);
    setSpriteSize(mwindow.lettres[mwindow.lettre].w*LETTER_SIZE, mwindow.lettres[mwindow.lettre].h*LETTER_SIZE, mwindow.texture, &mwindow.rectangle);
    setSpriteSize(167, 83, mwindow.tex_bordures, &mwindow.size_bordures);
    setSpriteSize(mwindow.lettres[19].w*LETTER_SIZE + 30, mwindow.lettres[19].h*LETTER_SIZE + 30, mwindow.tex_bordures, &mwindow.pos_bordures);
    setSpritePos(0, 0, &mwindow.size_word_bordures);
    setSpriteSize(167, 83, mwindow.tex_bordures, &mwindow.size_word_bordures);
    setSpritePos(mwindow.rectangle.x - (mwindow.pos_bordures.w-mwindow.lettres[mwindow.lettre].w*LETTER_SIZE)/2, mwindow.rectangle.y - (mwindow.pos_bordures.h-mwindow.lettres[mwindow.lettre].h*LETTER_SIZE)/2, &mwindow.pos_bordures);
    setSpriteSize(-1, -1, mwindow.tex_coeur, &mwindow.size_coeur);
    //Potence
    setSpriteSize(1000, 1000, mwindow.tex_potence, &mwindow.size_potence);
    setSpritePos(0, 150, &mwindow.pos_potence);
    setSpriteSize(700, 700, mwindow.tex_potence, &mwindow.pos_potence);
    //Pendu
    setSpritePos(546-26, 150+244, &mwindow.pos_pendu);
    setSpriteSize(144, 275, mwindow.tex_pendu, &mwindow.size_pendu);
    setSpriteSize(mwindow.size_pendu.w*0.7, mwindow.size_pendu.h*0.7, mwindow.tex_pendu, &mwindow.pos_pendu);
    initVariables();

    mwindow.soundEffect[0] = Mix_LoadWAV("..\\audio\\correct.wav");
    mwindow.soundEffect[1] = Mix_LoadWAV("..\\audio\\wrong.wav");
    Mix_VolumeChunk(mwindow.soundEffect[0], 25);
    Mix_VolumeChunk(mwindow.soundEffect[1], 25);

    //Chargement du mot
    jeu = initJeu();
    loadHiddenWord(jeu.hiddenWord);
    mwindow.currentLetter = 'a';
    //printf("%s\n", jeu.word);

    while(mwindow.running)
    {
        treatEvents(mwindow.event);
        updateFoundLetters();
        setSpritePos(mwindow.pos_bordures.x + (mwindow.pos_bordures.w-mwindow.lettres[mwindow.lettre].w*LETTER_SIZE)/2 + 2, WINDOW_HEIGHT/2 - mwindow.lettres[mwindow.lettre].h*LETTER_SIZE/2, &mwindow.rectangle);
        setWordBordure();
        display();

        if(jeu.lives == 0 || jeu.lettersFound == strlen(jeu.word))
        {
            printf("mot : %s %d\n", jeu.word, strlen(jeu.word));
            loadHiddenWord(jeu.word);
            if(jeu.lives == 0)
            {
                setSpritePos(0,84,&mwindow.size_word_bordures);
                for(int i=0; i<strlen(jeu.hiddenWord); i++) mwindow.word[i].y=58;
                Mix_PlayChannel(-1, mwindow.soundEffect[1], 0);
            }
            else
            {
                setSpritePos(0,168,&mwindow.size_word_bordures);
                for(int i=0; i<strlen(jeu.hiddenWord); i++) mwindow.word[i].y=116;
                Mix_PlayChannel(-1, mwindow.soundEffect[0], 0);
            }
            for(int i=0; i<2; i++)
            {
                SDL_RenderClear(mwindow.renderer);
                SDL_RenderPresent(mwindow.renderer);
                SDL_Delay(300);
                display();
                SDL_Delay(300);
            }
            printf("%s\n", jeu.word);
            SDL_Delay(200);
            jeu = initJeu();
            initFoundLetters();
            loadHiddenWord(jeu.hiddenWord);
            notif_vie = false;
        }
        SDL_Delay(1);
    }

    printf("Le mot etait : %s\n", jeu.word);

    //Libération de la mémoire allouée
    freeJeu(jeu);
    free(mwindow.word);
    free(mwindow.pos);
    SDL_DestroyTexture(mwindow.texture);
    SDL_DestroyTexture(mwindow.tex_chiffres);
    SDL_DestroyTexture(mwindow.tex_coeur);
    SDL_DestroyTexture(mwindow.tex_bordures);
    SDL_DestroyRenderer(mwindow.renderer);
    SDL_DestroyWindow(mwindow.window);
    for (int i=0; i<2; i++) Mix_FreeChunk(mwindow.soundEffect[i]);
    Mix_Quit();
    SDL_Quit();

    return 1;
}

void display()
{
    int chiffresVies[2];
    SDL_RenderClear(mwindow.renderer);
    printRenderer(mwindow.tex_bordures, &mwindow.size_word_bordures, &mwindow.pos_word_bordures, 1);
    printRenderer(mwindow.tex_bordures, &mwindow.size_bordures, &mwindow.pos_bordures, 1);
    printRenderer(mwindow.texture, mwindow.word, mwindow.pos, strlen(jeu.hiddenWord));
    printRenderer(mwindow.tex_coeur, &mwindow.size_coeur, &mwindow.pos_coeur, 1);
    separeNum(jeu.lives, chiffresVies);
    changeChiffres(jeu.lives);
    printRenderer(mwindow.tex_chiffres, &mwindow.chiffres[chiffresVies[1]], &mwindow.pos_chiffres[0], 1);
    printRenderer(mwindow.tex_chiffres, &mwindow.chiffres[chiffresVies[0]], &mwindow.pos_chiffres[1], 1);
    printRenderer(mwindow.texture, &mwindow.lettres[mwindow.lettre], &mwindow.rectangle, 1);
    printRenderer(mwindow.texture, mwindow.size_found, mwindow.pos_found, 26);
    
    int affichePendu = 10-jeu.lives;
    switch(affichePendu)
    {
        case(1):
            setSpritePos(1000*(affichePendu-1), 0, &mwindow.size_potence);
            if(jeu.lettersFound == strlen(jeu.word)) mwindow.size_potence.y=1000*2;
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            break;
        case(2):
            setSpritePos(1000*(affichePendu-1), 0, &mwindow.size_potence);
            if(jeu.lettersFound == strlen(jeu.word)) mwindow.size_potence.y=1000*2;
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            break;
        case(3):
            setSpritePos(1000*(affichePendu-1), 0, &mwindow.size_potence);
            if(jeu.lettersFound == strlen(jeu.word)) mwindow.size_potence.y=1000*2;
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            break;
        case(4):
            setSpritePos(1000*(affichePendu-1), 0, &mwindow.size_potence);
            if(jeu.lettersFound == strlen(jeu.word)) mwindow.size_potence.y=1000*2;
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            break;
        case(5):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lettersFound == strlen(jeu.word))
            {
                mwindow.size_potence.y=1000*2;
                mwindow.size_pendu.y=275*2;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        case(6):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lettersFound == strlen(jeu.word))
            {
                mwindow.size_potence.y=1000*2;
                mwindow.size_pendu.y=275*2;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        case(7):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lettersFound == strlen(jeu.word))
            {
                mwindow.size_potence.y=1000*2;
                mwindow.size_pendu.y=275*2;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        case(8):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lettersFound == strlen(jeu.word))
            {
                mwindow.size_potence.y=1000*2;
                mwindow.size_pendu.y=275*2;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        case(9):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lettersFound == strlen(jeu.word))
            {
                mwindow.size_potence.y=1000*2;
                mwindow.size_pendu.y=275*2;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        case(10):
            setSpritePos(144*(affichePendu-5), 0, &mwindow.size_pendu);
            if(jeu.lives == 0)
            {
                mwindow.size_potence.y=1000*1;
                mwindow.size_pendu.y=275*1;
            }
            printRenderer(mwindow.tex_potence, &mwindow.size_potence, &mwindow.pos_potence, 1);
            printRenderer(mwindow.tex_pendu, &mwindow.size_pendu, &mwindow.pos_pendu, 1);
            break;
        default:
            break;
    }
    SDL_RenderPresent(mwindow.renderer);
}

void exitWithError(char* error)
{
    SDL_Log("|!| ERREUR |!| %s : %s", error, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void initLettresEtChiffres()
{
    mwindow.lettre = 0;
    int larg = 58;
    mwindow.lettres[0].x=0; mwindow.lettres[0].y=0; mwindow.lettres[0].w=38; mwindow.lettres[0].h=larg; //a
    mwindow.lettres[1].x=48; mwindow.lettres[1].y=0; mwindow.lettres[1].w=38; mwindow.lettres[1].h=larg; //b
    mwindow.lettres[2].x=96; mwindow.lettres[2].y=0; mwindow.lettres[2].w=38; mwindow.lettres[2].h=larg; //c
    mwindow.lettres[3].x=144; mwindow.lettres[3].y=0; mwindow.lettres[3].w=38; mwindow.lettres[3].h=larg; //d
    mwindow.lettres[4].x=192; mwindow.lettres[4].y=0; mwindow.lettres[4].w=38; mwindow.lettres[4].h=larg; //e
    mwindow.lettres[5].x=240; mwindow.lettres[5].y=0; mwindow.lettres[5].w=38; mwindow.lettres[5].h=larg; //f
    mwindow.lettres[6].x=288; mwindow.lettres[6].y=0; mwindow.lettres[6].w=38; mwindow.lettres[6].h=larg; //g
    mwindow.lettres[7].x=336; mwindow.lettres[7].y=0; mwindow.lettres[7].w=38; mwindow.lettres[7].h=larg; //h
    mwindow.lettres[8].x=384; mwindow.lettres[8].y=0; mwindow.lettres[8].w=9; mwindow.lettres[8].h=larg; //i
    mwindow.lettres[9].x=403; mwindow.lettres[9].y=0; mwindow.lettres[9].w=38; mwindow.lettres[9].h=larg; //j
    mwindow.lettres[10].x=451; mwindow.lettres[10].y=0; mwindow.lettres[10].w=38; mwindow.lettres[10].h=larg; //k
    mwindow.lettres[11].x=499; mwindow.lettres[11].y=0; mwindow.lettres[11].w=38; mwindow.lettres[11].h=larg; //l
    mwindow.lettres[12].x=547; mwindow.lettres[12].y=0; mwindow.lettres[12].w=47; mwindow.lettres[12].h=larg; //m
    mwindow.lettres[13].x=605; mwindow.lettres[13].y=0; mwindow.lettres[13].w=38; mwindow.lettres[13].h=larg; //n
    mwindow.lettres[14].x=653; mwindow.lettres[14].y=0; mwindow.lettres[14].w=38; mwindow.lettres[14].h=larg; //o
    mwindow.lettres[15].x=701; mwindow.lettres[15].y=0; mwindow.lettres[15].w=38; mwindow.lettres[15].h=larg; //p
    mwindow.lettres[16].x=749; mwindow.lettres[16].y=0; mwindow.lettres[16].w=47; mwindow.lettres[16].h=larg; //q
    mwindow.lettres[17].x=806; mwindow.lettres[17].y=0; mwindow.lettres[17].w=38; mwindow.lettres[17].h=larg; //r
    mwindow.lettres[18].x=854; mwindow.lettres[18].y=0; mwindow.lettres[18].w=38; mwindow.lettres[18].h=larg; //s
    mwindow.lettres[19].x=902; mwindow.lettres[19].y=0; mwindow.lettres[19].w=47; mwindow.lettres[19].h=larg; //t
    mwindow.lettres[20].x=960; mwindow.lettres[20].y=0; mwindow.lettres[20].w=38; mwindow.lettres[20].h=larg; //u
    mwindow.lettres[21].x=1008; mwindow.lettres[21].y=0; mwindow.lettres[21].w=47; mwindow.lettres[21].h=larg; //v
    mwindow.lettres[22].x=1066; mwindow.lettres[22].y=0; mwindow.lettres[22].w=47; mwindow.lettres[22].h=larg; //w
    mwindow.lettres[23].x=1123; mwindow.lettres[23].y=0; mwindow.lettres[23].w=47; mwindow.lettres[23].h=larg; //x
    mwindow.lettres[24].x=1181; mwindow.lettres[24].y=0; mwindow.lettres[24].w=47; mwindow.lettres[24].h=larg; //y
    mwindow.lettres[25].x=1238; mwindow.lettres[25].y=0; mwindow.lettres[25].w=38; mwindow.lettres[25].h=larg; //z
    mwindow.lettres[26].x=1286; mwindow.lettres[26].y=0; mwindow.lettres[26].w=38; mwindow.lettres[26].h=larg; //_
    mwindow.lettres[27].x=1334; mwindow.lettres[27].y=0; mwindow.lettres[27].w=38; mwindow.lettres[27].h=larg; //" "
    mwindow.chiffres[0].x=0; mwindow.chiffres[0].y=0; mwindow.chiffres[0].w=38; mwindow.chiffres[0].h=larg; //0
    mwindow.chiffres[1].x=48; mwindow.chiffres[1].y=0; mwindow.chiffres[1].w=9; mwindow.chiffres[1].h=larg; //1
    mwindow.chiffres[2].x=67; mwindow.chiffres[2].y=0; mwindow.chiffres[2].w=38; mwindow.chiffres[2].h=larg; //2
    mwindow.chiffres[3].x=115; mwindow.chiffres[3].y=0; mwindow.chiffres[3].w=38; mwindow.chiffres[3].h=larg; //3
    mwindow.chiffres[4].x=163; mwindow.chiffres[4].y=0; mwindow.chiffres[4].w=38; mwindow.chiffres[4].h=larg; //4
    mwindow.chiffres[5].x=211; mwindow.chiffres[5].y=0; mwindow.chiffres[5].w=38; mwindow.chiffres[5].h=larg; //5
    mwindow.chiffres[6].x=259; mwindow.chiffres[6].y=0; mwindow.chiffres[6].w=38; mwindow.chiffres[6].h=larg; //6
    mwindow.chiffres[7].x=307; mwindow.chiffres[7].y=0; mwindow.chiffres[7].w=38; mwindow.chiffres[7].h=larg; //7
    mwindow.chiffres[8].x=355; mwindow.chiffres[8].y=0; mwindow.chiffres[8].w=38; mwindow.chiffres[8].h=larg; //8
    mwindow.chiffres[9].x=403; mwindow.chiffres[9].y=0; mwindow.chiffres[9].w=38; mwindow.chiffres[9].h=larg; //9
}

//Fonction initialisant la fenêtre
void initWindow()
{
    //Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) exitWithError("Initialisation Video");

    //Initialisation audio
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048)) exitWithError("Initialisation Audio");

    //Création de la fenêtre
    mwindow.window = NULL;
    mwindow.window = SDL_CreateWindow("Pendu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(mwindow.window == NULL) exitWithError("Creation fenetre");
    
    //Création d'un rendu
    mwindow.renderer = NULL;
    mwindow.renderer = SDL_CreateRenderer(mwindow.window, -1, SDL_RENDERER_ACCELERATED);
    if(mwindow.renderer == NULL)
    {
        SDL_DestroyWindow(mwindow.window);
        exitWithError("Creation rendu");
    }

    //Création d'une surface et d'une texture
    mwindow.surface = NULL;
    mwindow.texture = NULL;
}

//Fonction chargeant les sprites
SDL_Texture* loadSprite(char* sprite)
{
    SDL_Texture* tex;
    mwindow.surface = SDL_LoadBMP(sprite);
    if(mwindow.surface == NULL)
    {
        SDL_DestroyRenderer(mwindow.renderer);
        SDL_DestroyWindow(mwindow.window);
        exitWithError("Creation surface");
    }

    tex = SDL_CreateTextureFromSurface(mwindow.renderer, mwindow.surface);
    SDL_FreeSurface(mwindow.surface);
    if(tex == NULL)
    {
        SDL_DestroyRenderer(mwindow.renderer);
        SDL_DestroyWindow(mwindow.window);
        exitWithError("Creation texture");
    }

    return tex;
}

void setSpriteSize(int w, int h, SDL_Texture* tex, SDL_Rect* rec)
{
    //Dimensions rectangle texture
    if(w==-1 && h==-1)
    {
        if(SDL_QueryTexture(tex, NULL, NULL, &(rec->w), &(rec->h)) != 0)
        {
            SDL_DestroyTexture(mwindow.texture);
            SDL_DestroyTexture(mwindow.tex_chiffres);
            SDL_DestroyTexture(mwindow.tex_coeur);
            SDL_DestroyRenderer(mwindow.renderer);
            SDL_DestroyWindow(mwindow.window);
            exitWithError("Chargement texture en memoire");
        }
    }
    else
    {
        rec->w = w;
        rec->h = h;
    }
}

void setSpritePos(int x, int y, SDL_Rect* rec)
{
    rec->x = x;
    rec->y = y;
}

void initVariables()
{
    mwindow.running = true;
    mwindow.lettre = 0;

    mwindow.pos_coeur.w=mwindow.chiffres[0].h*HEART_SIZE; mwindow.pos_coeur.h=mwindow.chiffres[0].h*HEART_SIZE;
    mwindow.pos_coeur.x=(WINDOW_WIDTH-mwindow.pos_coeur.w)*0.02; mwindow.pos_coeur.y=WINDOW_HEIGHT-mwindow.chiffres[0].h*HEART_SIZE-10;
    mwindow.size_coeur.x=0; mwindow.size_coeur.y=0;

    mwindow.pos_chiffres[0].x=mwindow.pos_coeur.x+mwindow.pos_coeur.w+15; mwindow.pos_chiffres[0].y=WINDOW_HEIGHT-mwindow.chiffres[0].h*FIGURE_SIZE-10;
    mwindow.pos_chiffres[1].y = mwindow.pos_chiffres[0].y;
}

//Fonction gérant les évènements
void treatEvents(SDL_Event event)
{
    while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    mwindow.running = false;
                    break;
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_a :
                            changeLetter(0);
                            mwindow.currentLetter = 'a';
                            printf("A\n");
                            break;
                        case SDLK_b :
                            changeLetter(1);
                            mwindow.currentLetter = 'b';
                            printf("B\n");
                            break;
                        case SDLK_c :
                            changeLetter(2);
                            mwindow.currentLetter = 'c';
                            printf("C\n");
                            break;
                        case SDLK_d :
                            changeLetter(3);
                            mwindow.currentLetter = 'd';
                            printf("D\n");
                            break;
                        case SDLK_e :
                            changeLetter(4);
                            mwindow.currentLetter = 'e';
                            printf("E\n");
                            break;
                        case SDLK_f :
                            changeLetter(5);
                            mwindow.currentLetter = 'f';
                            printf("F\n");
                            break;
                        case SDLK_g :
                            changeLetter(6);
                            mwindow.currentLetter = 'g';
                            printf("G\n");
                            break;
                        case SDLK_h :
                            changeLetter(7);
                            mwindow.currentLetter = 'h';
                            printf("H\n");
                            break;
                        case SDLK_i :
                            changeLetter(8);
                            mwindow.currentLetter = 'i';
                            printf("I\n");
                            break;
                        case SDLK_j :
                            changeLetter(9);
                            mwindow.currentLetter = 'j';
                            printf("J\n");
                            break;
                        case SDLK_k :
                            changeLetter(10);
                            mwindow.currentLetter = 'k';
                            printf("K\n");
                            break;
                        case SDLK_l :
                            changeLetter(11);
                            mwindow.currentLetter = 'l';
                            printf("L\n");
                            break;
                        case SDLK_m :
                            changeLetter(12);
                            mwindow.currentLetter = 'm';
                            printf("M\n");
                            break;
                        case SDLK_n :
                            changeLetter(13);
                            mwindow.currentLetter = 'n';
                            printf("N\n");
                            break;
                        case SDLK_o :
                            changeLetter(14);
                            mwindow.currentLetter = 'o';
                            printf("O\n");
                            break;
                        case SDLK_p :
                            changeLetter(15);
                            mwindow.currentLetter = 'p';
                            printf("P\n");
                            break;
                        case SDLK_q :
                            changeLetter(16);
                            mwindow.currentLetter = 'q';
                            printf("Q\n");
                            break;
                        case SDLK_r :
                            changeLetter(17);
                            mwindow.currentLetter = 'r';
                            printf("R\n");
                            break;
                        case SDLK_s :
                            changeLetter(18);
                            mwindow.currentLetter = 's';
                            printf("S\n");
                            break;
                        case SDLK_t :
                            changeLetter(19);
                            mwindow.currentLetter = 't';
                            printf("T\n");
                            break;
                        case SDLK_u :
                            changeLetter(20);
                            mwindow.currentLetter = 'u';
                            printf("U\n");
                            break;
                        case SDLK_v :
                            changeLetter(21);
                            mwindow.currentLetter = 'v';
                            printf("V\n");
                            break;
                        case SDLK_w :
                            changeLetter(22);
                            mwindow.currentLetter = 'w';
                            printf("W\n");
                            break;
                        case SDLK_x :
                            changeLetter(23);
                            mwindow.currentLetter = 'x';
                            printf("X\n");
                            break;
                        case SDLK_y :
                            changeLetter(24);
                            mwindow.currentLetter = 'y';
                            printf("Y\n");
                            break;
                        case SDLK_z :
                            changeLetter(25);
                            mwindow.currentLetter = 'z';
                            printf("Z\n");
                            break;
                        case SDLK_8 :
                            changeLetter(26);
                            printf("_\n");
                            break;
                        case SDLK_RETURN :
                            if(alreadyEnter(jeu, mwindow.currentLetter)) loadNotif("lettre deja entree");
                            jeu = nextTurn(jeu, mwindow.currentLetter);
                            loadHiddenWord(jeu.hiddenWord);
                            if(jeu.lives==1 && !notif_vie)
                            {
                                display();
                                //SDL_RenderClear(mwindow.renderer);
                                loadNotif("une seule vie");
                                notif_vie = true;
                            }
                        default :
                            break;
                    }
                    break;

                default :
                    break;
            }
        }
}

//Fonction affichant le rendu sur la fenêtre
void printRenderer(SDL_Texture* tex, SDL_Rect* sprite, SDL_Rect* pos, int size)
{
    for(int i=0; i<size; i++)
    {
        if(SDL_RenderCopy(mwindow.renderer, tex, &(sprite[i]), &(pos[i])) != 0)
        {
            SDL_DestroyTexture(mwindow.texture);
            SDL_DestroyTexture(mwindow.tex_chiffres);
            SDL_DestroyTexture(mwindow.tex_coeur);
            SDL_DestroyRenderer(mwindow.renderer);
            SDL_DestroyWindow(mwindow.window);
            exitWithError("Chargement texture sur rendu");
        }
    }
}

void changeLetter(int i)
{
    mwindow.lettre = i;
    setSpriteSize(mwindow.lettres[mwindow.lettre].w*LETTER_SIZE, mwindow.lettres[mwindow.lettre].h*LETTER_SIZE, mwindow.texture, &mwindow.rectangle);
}

void changeChiffres(int i)
{
    int val[2];
    separeNum(jeu.lives, val);
    setSpriteSize(mwindow.chiffres[val[1]].w*FIGURE_SIZE, mwindow.chiffres[val[1]].h*FIGURE_SIZE, mwindow.tex_chiffres, &mwindow.pos_chiffres[0]);
    mwindow.pos_chiffres[1].x = mwindow.pos_chiffres[0].x + mwindow.chiffres[val[1]].w*FIGURE_SIZE + 10;
    setSpriteSize(mwindow.chiffres[val[0]].w*FIGURE_SIZE, mwindow.chiffres[val[0]].h*FIGURE_SIZE, mwindow.tex_chiffres, &mwindow.pos_chiffres[1]);
}

void loadHiddenWord(char *hiddenWord)
{
    //Initialisation des variables des lettres et de leur pos
    mwindow.word = (SDL_Rect*) malloc(strlen(hiddenWord)*sizeof(SDL_Rect));
    mwindow.pos = (SDL_Rect*) malloc(strlen(hiddenWord)*sizeof(SDL_Rect));
    //Pour chaque lettre on définit sa position dans texture et sa position sur le render
    int spriteLenght = 0;
    for(int i=0; i<strlen(hiddenWord); i++)
    {
        int num;
        if(hiddenWord[i] == '_') num = 26;
        else num = hiddenWord[i] - 97;
        mwindow.word[i].x = mwindow.lettres[num].x;
        mwindow.word[i].y = 0;
        mwindow.word[i].w = mwindow.lettres[num].w;
        mwindow.word[i].h = mwindow.lettres[num].h;
        spriteLenght += mwindow.word[i].w*WORD_SIZE + 5;
    }
    for(int i=0; i<strlen(hiddenWord); i++)
    {
        if(i != 0)
        {
            mwindow.pos[i].x = mwindow.pos[i-1].x + mwindow.pos[i-1].w + 5;
        }
        else
        {
            mwindow.pos[i].x = WINDOW_WIDTH/2 - spriteLenght/2;
        }
        mwindow.pos[i].y = 30;
        mwindow.pos[i].w = mwindow.word[i].w*WORD_SIZE;
        mwindow.pos[i].h = mwindow.word[i].h*WORD_SIZE;
    }
}

void separeNum(int num, int *val)
{
    for(int i=0; i<2; i++)
    {
        val[i] = num%10;
        num /= 10;
    }
}

void initFoundLetters()
{
    for(int i=0; i<26; i++)
    {
        mwindow.size_found[i].x=mwindow.lettres[i].x; mwindow.size_found[i].y=0; mwindow.size_found[i].w=mwindow.lettres[i].w; mwindow.size_found[i].h=mwindow.lettres[i].h;
        if(i==0) mwindow.pos_found[0].x=WINDOW_WIDTH*0.24;
        else mwindow.pos_found[i].x=mwindow.pos_found[i-1].x+mwindow.size_found[i-1].w*FOUND_SIZE+5;
        mwindow.pos_found[i].y=WINDOW_HEIGHT-mwindow.size_found[i].h*FOUND_SIZE-10;
        mwindow.pos_found[i].w=mwindow.size_found[i].w*FOUND_SIZE;
        mwindow.pos_found[i].h=mwindow.size_found[i].h*FOUND_SIZE;
    }
}

void updateFoundLetters()
{
    for(int i=0; i<26; i++)
    {
        if(jeu.lettres[i])
        {
            mwindow.size_found[i].x=mwindow.lettres[27].x;
            mwindow.size_found[i].w=mwindow.lettres[i].w;
            mwindow.size_found[i].h=mwindow.lettres[27].h;
        }
    }
}

void loadNotif(char* txt)
{
    mwindow.size_notif = (SDL_Rect*) malloc(strlen(txt)*sizeof(SDL_Rect));
    mwindow.pos_notif = (SDL_Rect*) malloc(strlen(txt)*sizeof(SDL_Rect));
    int lg = 0;
    int y=58, larg=58;
    for(int i=0; i<strlen(txt); i++)
    {
        int num;
        if(txt[i]==' ') num=27;
        else num=txt[i]-97;
        mwindow.size_notif[i].x=mwindow.lettres[num].x;
        mwindow.size_notif[i].y=y;
        mwindow.size_notif[i].w=mwindow.lettres[num].w;
        mwindow.size_notif[i].h=larg;

        lg += mwindow.size_notif[i].w*NOTIF_SIZE + 3;
    }

    for(int i=0; i<strlen(txt); i++)
    {
        if(i==0) mwindow.pos_notif[i].x=WINDOW_WIDTH/2 - lg/2;
        else mwindow.pos_notif[i].x = mwindow.pos_notif[i-1].x + mwindow.size_notif[i-1].w*NOTIF_SIZE + 3;

        mwindow.pos_notif[i].y=WINDOW_HEIGHT/2 - larg/2;
        mwindow.pos_notif[i].w=mwindow.size_notif[i].w*NOTIF_SIZE;
        mwindow.pos_notif[i].h=mwindow.size_notif[i].h*NOTIF_SIZE;
    }

    setNotifBordure(txt);

    printRenderer(mwindow.tex_bordures, &mwindow.size_notif_bordures, &mwindow.pos_notif_bordures, 1);
    printRenderer(mwindow.texture, mwindow.size_notif, mwindow.pos_notif, strlen(txt));
    SDL_RenderPresent(mwindow.renderer);
    SDL_Delay(500);
    free(mwindow.size_notif);
    free(mwindow.pos_notif);
}

void setWordBordure()
{
    setSpritePos(0, 0, &mwindow.size_word_bordures);
    int lg = 0;
    for(int i=0; i<strlen(jeu.hiddenWord); i++)
    {
        lg += mwindow.word[i].w*WORD_SIZE + 5;
    }

    setSpriteSize(lg+30, mwindow.lettres[mwindow.lettre].h+30, mwindow.tex_bordures, &mwindow.pos_word_bordures);
    setSpritePos(mwindow.pos[0].x-15-3, mwindow.pos[0].y-15,&mwindow.pos_word_bordures);
}

void setNotifBordure(char* txt)
{
    int lg = 0;
    for(int i=0; i<strlen(txt); i++)
    {
        lg += mwindow.size_notif[i].w*NOTIF_SIZE + 3;
    }
    setSpritePos(0, 84, &mwindow.size_notif_bordures);
    setSpriteSize(167, 83, mwindow.tex_bordures, &mwindow.size_notif_bordures);
    setSpriteSize(lg+30, mwindow.lettres[mwindow.lettre].h+30, mwindow.tex_bordures, &mwindow.pos_notif_bordures);
    setSpritePos(mwindow.pos_notif[0].x - (mwindow.pos_notif_bordures.w-lg)/2 - 4, mwindow.pos_notif[0].y - (mwindow.pos_notif_bordures.h-mwindow.size_notif[0].h*NOTIF_SIZE)/2, &mwindow.pos_notif_bordures);
}