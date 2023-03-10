//Sud au cul.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
 //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>

//on initialise les variables globales
int rows, cols, mines, goofy = 0;
int** grid;
int** revealed;
int** flags;
int width = 500;
int height = 500;
int statut = EXIT_FAILURE;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Rect rd = { 0, 0, 500, 500 };
SDL_Event event;
//permet au joueur de choisir la difficulté à laquelle il souhaite jouer et adapte la taille de la grille en conséquence
void setDifficulty() {
    int dif = 0;
    SDL_Surface* difficulty = NULL;
    SDL_Texture* textureDIF = NULL;
    difficulty = SDL_LoadBMP("difficulty.bmp");
    textureDIF = SDL_CreateTextureFromSurface(renderer, difficulty);
    SDL_FreeSurface(difficulty);
    SDL_RenderCopy(renderer, textureDIF, NULL, &rd);
    SDL_RenderPresent(renderer);
    while (dif == 0) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_1 || event.key.keysym.scancode == SDL_SCANCODE_KP_1) {
                dif = 1;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_2 || event.key.keysym.scancode == SDL_SCANCODE_KP_2) {
                dif = 2;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_3 || event.key.keysym.scancode == SDL_SCANCODE_KP_3) {
                dif = 3;
            }
            else {
                SDL_Surface* aha = NULL;
                SDL_Texture* texturegoofy = NULL;
                aha = SDL_LoadBMP("nightmare.bmp");
                texturegoofy = SDL_CreateTextureFromSurface(renderer, aha);
                SDL_FreeSurface(aha);
                SDL_RenderCopy(renderer, texturegoofy, NULL, &rd);
                SDL_RenderPresent(renderer);
                SDL_Delay(3000);
                goofy = 1;
                dif = 69;
            }
        }
    }
    if (dif == 1) {
        rows = 9;
        cols = 11;
        mines = 10;
        width = cols * 50;
        height = rows * 50;
        grid = malloc(sizeof(int*) * rows);
        for (int k = 0; k < rows; k++) {
            grid[k] = malloc(sizeof(int) * cols);
        }
        revealed = malloc(sizeof(int*) * rows);
        for (int i = 0; i < rows; i++) {
            revealed[i] = malloc(sizeof(int) * cols);
        }
        flags = malloc(sizeof(int*) * rows);
        for (int j = 0; j < rows; j++) {
            flags[j] = malloc(sizeof(int) * cols);
        }
    }
    else if (dif == 2) {
        rows = 15;
        cols = 19;
        mines = 40;
        width = cols * 50;
        height = rows * 50;
        grid = malloc(sizeof(int*) * rows);
        for (int k = 0; k < rows; k++) {
            grid[k] = malloc(sizeof(int) * cols);
        }
        revealed = malloc(sizeof(int*) * rows);
        for (int i = 0; i < rows; i++) {
            revealed[i] = malloc(sizeof(int) * cols);
        }
        flags = malloc(sizeof(int*) * rows);
        for (int j = 0; j < rows; j++) {
            flags[j] = malloc(sizeof(int) * cols);
        }
    }
    else if(dif == 3){
        rows = 21;
        cols = 25;
        mines = 99;
        width = cols * 45;
        height = rows * 45;
        grid = malloc(sizeof(int*) * rows);
        for (int k = 0; k < rows; k++) {
            grid[k] = malloc(sizeof(int) * cols);
        }
        revealed = malloc(sizeof(int*) * rows);
        for (int i = 0; i < rows; i++) {
            revealed[i] = malloc(sizeof(int) * cols);
        }
        flags = malloc(sizeof(int*) * rows);
        for (int j = 0; j < rows; j++) {
            flags[j] = malloc(sizeof(int) * cols);
        }
    }
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
//permet de générer aléatoirement des bombes
void generateMines() {
    int i, j, count = 0;
    while (count < mines) {
        i = rand() % rows;
        j = rand() % cols;
        if (grid[i][j] != -1) {
            grid[i][j] = -1;
            if (i > 0) {
                if (grid[i - 1][j] != -1) {
                    grid[i - 1][j] ++;
                }
                if (j > 0) {
                    if (grid[i - 1][j - 1] != -1) {
                        grid[i - 1][j - 1] ++;
                    }
                }
                if (j < cols - 1) {
                    if (grid[i - 1][j + 1] != -1) {
                        grid[i - 1][j + 1]++;
                    }
                }
            }

            if (j > 0) {
                if (grid[i][j - 1] != -1) {
                    grid[i][j - 1]++;
                }
                if (i < rows - 1) {
                    if (grid[i + 1][j - 1] != -1) {
                        grid[i + 1][j - 1]++;
                    }
                }
            }

            if (i < rows - 1) {
                if (grid[i + 1][j] != -1) {
                    grid[i + 1][j]++;
                }
                if (j < cols - 1) {
                    if (grid[i + 1][j + 1] != -1) {
                        grid[i + 1][j + 1]++;
                    }
                }
            }

            if (j < cols - 1) {
                if (grid[i][j + 1] != -1) {
                    grid[i][j + 1]++;
                }
            }
            count++;
        }
    }
}

//permet de révéler les cases choisis par le joueur
void reveal(int i, int j) {
    if (revealed[i][j] == 1) {
        return;
    }

    revealed[i][j] = 1;

    if (grid[i][j] == -1) {
        return;
    }

    if (grid[i][j] > 0) {
        return;
    }

    if (i > 0) {
        reveal(i - 1, j);
        if (j > 0) {
            reveal(i - 1, j - 1);
        }
        if (j < cols - 1) {
            reveal(i - 1, j + 1);
        }
    }

    if (j > 0) {
        reveal(i, j - 1);
        if (i < rows - 1) {
            reveal(i + 1, j - 1);
        }
    }

    if (i < rows - 1) {
        reveal(i + 1, j);
        if (j < cols - 1) {
            reveal(i + 1, j + 1);
        }
    }

    if (j < cols - 1) {
        reveal(i, j + 1);
    }
}

void printGrid() {
    int w_case = width / cols;
    int h_case = height / rows;
    SDL_Surface* herbe = NULL;
    SDL_Surface* terre = NULL;
    SDL_Surface* flag = NULL;
    SDL_Surface* bomb = NULL;
    SDL_Surface* one = NULL;
    SDL_Surface* two = NULL;
    SDL_Surface* three = NULL;
    SDL_Surface* four = NULL;
    SDL_Surface* five = NULL;
    SDL_Surface* six = NULL;
    SDL_Surface* seven = NULL;
    SDL_Surface* eight = NULL;
    SDL_Texture* texture1 = NULL;
    SDL_Texture* texture2 = NULL;
    SDL_Texture* texture3 = NULL;
    SDL_Texture* texture4 = NULL;
    SDL_Texture* texture5 = NULL;
    SDL_Texture* texture6 = NULL;
    SDL_Texture* texture7 = NULL;
    SDL_Texture* texture8 = NULL;
    SDL_Texture* texture0 = NULL;
    SDL_Texture* textureT = NULL;
    SDL_Texture* textureF = NULL;
    SDL_Texture* textureB = NULL;
    herbe = SDL_LoadBMP("herbe.bmp");
    terre = SDL_LoadBMP("Terre.bmp");
    flag = SDL_LoadBMP("flag.bmp");
    bomb = SDL_LoadBMP("kaboom.bmp");
    one = SDL_LoadBMP("1.bmp");
    two = SDL_LoadBMP("2.bmp");
    three = SDL_LoadBMP("3.bmp");
    four = SDL_LoadBMP("4.bmp");
    five = SDL_LoadBMP("5.bmp");
    six = SDL_LoadBMP("6.bmp");
    seven = SDL_LoadBMP("7.bmp");
    eight = SDL_LoadBMP("8.bmp");
    textureT = SDL_CreateTextureFromSurface(renderer, herbe);
    texture0 = SDL_CreateTextureFromSurface(renderer, terre);
    textureF = SDL_CreateTextureFromSurface(renderer, flag);
    textureB = SDL_CreateTextureFromSurface(renderer, bomb);
    texture1 = SDL_CreateTextureFromSurface(renderer, one);
    texture2 = SDL_CreateTextureFromSurface(renderer, two);
    texture3 = SDL_CreateTextureFromSurface(renderer, three);
    texture4 = SDL_CreateTextureFromSurface(renderer, four);
    texture5 = SDL_CreateTextureFromSurface(renderer, five);
    texture6 = SDL_CreateTextureFromSurface(renderer, six);
    texture7 = SDL_CreateTextureFromSurface(renderer, seven);
    texture8 = SDL_CreateTextureFromSurface(renderer, eight);
    //On libère la surface, on n’en a plus besoin //
    SDL_FreeSurface(herbe);
    SDL_FreeSurface(terre);
    SDL_FreeSurface(flag);
    SDL_FreeSurface(bomb);
    SDL_FreeSurface(one);
    SDL_FreeSurface(two);
    SDL_FreeSurface(three);
    SDL_FreeSurface(four);
    SDL_FreeSurface(five);
    SDL_FreeSurface(six);
    SDL_FreeSurface(seven);
    SDL_FreeSurface(eight);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int casex = j * w_case;
            int casey = i * h_case;
            SDL_Rect rect = { casex, casey, w_case, h_case };
            if (flags[i][j] == 1 && revealed[i][j] == 0) {
                SDL_RenderCopy(renderer, textureF, NULL, &rect);
            }
            else if (revealed[i][j] == 0) {
                SDL_RenderCopy(renderer, textureT, NULL, &rect);
            }
            else if (grid[i][j] == -1) {
                SDL_RenderCopy(renderer, textureB, NULL, &rect);
            }
            else if (grid[i][j] == 0) {
                SDL_RenderCopy(renderer, texture0, NULL, &rect);
            }
            else if (grid[i][j] == 1) {
                SDL_RenderCopy(renderer, texture1, NULL, &rect);
            }
            else if (grid[i][j] == 2) {
                SDL_RenderCopy(renderer, texture2, NULL, &rect);
            }
            else if (grid[i][j] == 3) {
                SDL_RenderCopy(renderer, texture3, NULL, &rect);
            }
            else if (grid[i][j] == 4) {
                SDL_RenderCopy(renderer, texture4, NULL, &rect);
            }
            else if (grid[i][j] == 5) {
                SDL_RenderCopy(renderer, texture5, NULL, &rect);
            }
            else if (grid[i][j] == 6) {
                SDL_RenderCopy(renderer, texture6, NULL, &rect);
            }
            else if (grid[i][j] == 7) {
                SDL_RenderCopy(renderer, texture7, NULL, &rect);
            }
            else if (grid[i][j] == 8) {
                SDL_RenderCopy(renderer, texture8, NULL, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

#ifdef __EMSCRIPTEN__
#include<emscripten/emscripten.h>
#endif

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
int done;


SDL_bool test(SDL_Point point, SDL_Rect rect)
{
    if (point.x >= rect.x && point.x <= (rect.x + rect.w) &&
        point.y >= rect.y && point.y <= (rect.y + rect.h))
        return SDL_TRUE;
    else
        return SDL_FALSE;
}


int main2() {
    SDL_Window* window = NULL;

    // Initialisation, création de la fenêtre et du renderer. //
    if (0 != SDL_Init(SDL_INIT_AUDIO, SDL_INIT_VIDEO)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN);
    if (NULL == window){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer){
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
    srand(time(NULL));
    setDifficulty();
    //reset les variables
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
            revealed[i][j] = 0;
            flags[i][j] = 0;
        }
    }
    generateMines();
    int w_case = width / cols;
    int h_case = height / rows;
    int x, y, arret = 0;
    int help = 0;
    char action;
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN);
    if (NULL == window){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer){
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
    // C’est à partir de maintenant que ça se passe. //
    SDL_Surface* defaite = NULL;
    SDL_Surface* victoire = NULL;
    SDL_Texture* textureD = NULL;
    SDL_Texture* textureV = NULL;
    SDL_Rect dv = { 0, 0, width, height };
    if (goofy == 0) {
        while (1) {
            int victory = 1;
            if (arret == 0) {
                printGrid();
                action = "z";
                //permet de choisir la case
                SDL_WaitEvent(&event);
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        x = event.button.x;
                        y = event.button.y;
                        y = y / h_case;
                        x = x / w_case;
                        action = 'r';
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        x = event.button.x;
                        y = event.button.y;
                        y = y / h_case;
                        x = x / w_case;
                        action = 'f';
                    }
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_H) {
                        SDL_Surface* helper = NULL;
                        SDL_Texture* textureH = NULL;
                        helper = SDL_LoadBMP("help.bmp");
                        textureH = SDL_CreateTextureFromSurface(renderer, helper);
                        SDL_FreeSurface(helper);
                        SDL_RenderCopy(renderer, textureH, NULL, &dv);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(3000);
                        help = 1;
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < cols; j++) {
                                if (revealed[i][j] == 0 && grid[i][j] != -1) {
                                    revealed[i][j] = 1;
                                    x = j;
                                    y = i;
                                    action = 'r';
                                }
                            }
                        }
                    }
                }
            }
            //permet de choisir l'action
            if (action == 'r' && flags[y][x] != 1) {
                //en cas de défaite (une bombe est révélé)
                if (grid[y][x] == -1) {
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            if (grid[i][j] == -1) {
                                revealed[i][j] = 1;
                            }
                        }
                    }
                    if (arret == 0) {
                        defaite = SDL_LoadBMP("defaite.bmp");
                        textureD = SDL_CreateTextureFromSurface(renderer, defaite);
                        SDL_FreeSurface(defaite);
                        printGrid();
                        SDL_Delay(1000);
                        SDL_RenderCopy(renderer, textureD, NULL, &dv);
                        SDL_RenderPresent(renderer);
                    }
                    arret = 1;
                    SDL_WaitEvent(&event);
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                            for (int k = 0; k < rows; k++) {
                                free(grid[k]);
                            }
                            free(grid);
                            for (int i = 0; i < rows; i++) {
                                free(revealed[i]);
                            }
                            free(revealed);
                            for (int j = 0; j < rows; j++) {
                                free(flags[j]);
                            }
                            free(flags);
                            if (NULL != renderer)
                                SDL_DestroyRenderer(renderer);
                            if (NULL != window)
                                SDL_DestroyWindow(window);
                            SDL_Quit();
                            main2();
                        }
                        else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                            SDL_Surface* demoman = NULL;
                            SDL_Texture* texturedemoman = NULL;
                            demoman = SDL_LoadBMP("demoman.bmp");
                            texturedemoman = SDL_CreateTextureFromSurface(renderer, demoman);
                            SDL_FreeSurface(demoman);
                            SDL_RenderCopy(renderer, texturedemoman, NULL, &dv);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(5000);
                            break;
                        }
                    }
                }
                if (help == 0) {
                    reveal(y, x);
                    //permet de vérifier si le joueur a gagné
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            if (victory == 1) {
                                if (revealed[i][j] == 0 && grid[i][j] != -1) {
                                    victory = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                //en cas de victoire (toutes les bombes sont trouvés)
                if (victory == 1) {
                    if (arret == 0) {
                        victoire = SDL_LoadBMP("victoire.bmp");
                        textureV = SDL_CreateTextureFromSurface(renderer, victoire);
                        SDL_FreeSurface(victoire);
                        printGrid();
                        SDL_Delay(500);
                        SDL_RenderCopy(renderer, textureV, NULL, &dv);
                        SDL_RenderPresent(renderer);
                    }
                    arret = 1;
                    event.type = SDL_MOUSEBUTTONDOWN;
                    SDL_WaitEvent(&event);
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                            for (int k = 0; k < rows; k++) {
                                free(grid[k]);
                            }
                            free(grid);
                            for (int i = 0; i < rows; i++) {
                                free(revealed[i]);
                            }
                            free(revealed);
                            for (int j = 0; j < rows; j++) {
                                free(flags[j]);
                            }
                            free(flags);
                            if (NULL != renderer)
                                SDL_DestroyRenderer(renderer);
                            if (NULL != window)
                                SDL_DestroyWindow(window);
                            SDL_Quit();
                            main2();
                        }
                        else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                            break;
                        }
                    }
                }
            }
            //permet de poser ou d'enlever un drapeau
            if (action == 'f') {
                if (flags[y][x] == 0) {
                    flags[y][x] = 1;
                    if (NULL != renderer) {
                        SDL_DestroyRenderer(renderer);
                    }
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                }
                else {
                    flags[y][x] = 0;
                }
            }
        }
        statut = EXIT_SUCCESS;
    }
Quit:
    for (int k = 0; k < rows; k++) {
        free(grid[k]);
    }
    free(grid);
    for (int i = 0; i < rows; i++) {
        free(revealed[i]);
    }
    free(revealed);
    for (int j = 0; j < rows; j++) {
        free(flags[j]);
    }
    free(flags);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}

int main(int argc, char* argv[]) {
    main2();
}