 //Sud au cul.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
 //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>

//on initialise les variables globales
int rows, cols, mines;
int** grid;
int** revealed;
int** flags;
//permet au joueur de choisir la difficulté à laquelle il souhaite jouer et adapte la taille de la grille en conséquence
void setDifficulty() {
    int dif;
    printf("Choose a difficulty level(1, 2, 3) : ");
    scanf_s("%d", &dif);
    while (getchar() != '\n');
    if (dif == 1) {
        rows = 9;
        cols = 11;
        mines = 10;
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
    else {
        rows = 21;
        cols = 25;
        mines = 99;
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


//int main2() {
//    while (1) {
//        int victory = 1;
//        system("CLS");
//        printGrid();
//        //permet de choisir la case
//        printf("Enter x and y coordinates (separated by space): ");
//        scanf_s("%d %d", &x, &y);
//        while (getchar() != '\n');
//
//        if (x < 0 || x >= cols || y < 0 || y >= rows) {
//            printf("Invalid coordinates!\n");
//            continue;
//        }
//        //permet de choisir l'action
//        printf("Enter r for reveal, f for flag");
//        scanf_s("%c", &action, 1);
//        while (getchar() != '\n');
//
//        if (action == 'r') {
//            //en cas de défaite (une bombe est révélé)
//            if (grid[y][x] == -1) {
//                system("CLS");
//                for (int i = 0; i < rows; i++) {
//                    for (int j = 0; j < cols; j++) {
//                        if (grid[i][j] == -1) {
//                            revealed[i][j] = 1;
//                        }
//                    }
//                }
//                printGrid();
//                printf("You lost!\n");
//                break;
//            }
//
//            reveal(y, x);
//            //permet de vérifier si le joueur a gagné
//            for (int i = 0; i < rows; i++) {
//                for (int j = 0; j < cols; j++) {
//                    if (victory == 1) {
//                        if (revealed[i][j] == 0 && grid[i][j] != -1) {
//                            victory = 0;
//                            break;
//                        }
//                    }
//                }
//            }
//            //en cas de victoire (toutes les bombes sont trouvés)
//            if (victory == 1) {
//                system("CLS");
//                printGrid();
//                printf("You won!\n");
//                break;
//            }
//        }
//        //permet de poser ou d'enlever un drapeau
//        if (action == 'f') {
//            if (flags[y][x] == 0) {
//                flags[y][x] = 1;
//            }
//            else {
//                flags[y][x] = 0;
//            }
//        }
//    }
//}

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


int main(int argc, char* argv[]){
     SDL_Window* window = NULL;
     SDL_Renderer* renderer = NULL;
     int statut = EXIT_FAILURE;
 
     /* Initialisation, création de la fenêtre et du renderer. */
     if (0 != SDL_Init(SDL_INIT_VIDEO))
     {
         fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
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
     int width = 640;
     int height = 480;
     int w_case = width / cols;
     int h_case = height / rows;
 
     window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         width, height, SDL_WINDOW_SHOWN);
     if (NULL == window)
     {
         fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
         goto Quit;
     }
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (NULL == renderer)
     {
         fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
         goto Quit;
     }
 
     /* C’est à partir de maintenant que ça se passe. */
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
     if (NULL == herbe || NULL == terre || NULL == flag || NULL == bomb || NULL == one || NULL == two || NULL == three || NULL == four || NULL == five || NULL == six || NULL == seven || NULL == eight)
     {
         fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
         goto Quit;
     }
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
     SDL_FreeSurface(herbe); /* On libère la surface, on n’en a plus besoin */
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
     if (NULL == texture1 || NULL == texture2 || NULL == texture3 || NULL == texture4 || NULL == texture5 || NULL == texture6 || NULL == texture7 || NULL == texture8 || NULL == texture0 || NULL == textureT || NULL == textureF || NULL == textureB)
     {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
     }
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int x = 0 + i * w_case;
            int y = 0 + j * h_case;
            SDL_Rect rect = { x, y, w_case, h_case };
            if (flags[i][j] == 1 && revealed[i][j] == 0) {
                SDL_RenderCopy(renderer, textureF, NULL, &rect);
            }
            else if (revealed[i][j] == 0) {
                    SDL_RenderCopy(renderer, textureT, NULL, &rect);
            }
            else if (grid[i][j] == -1) {
                    SDL_RenderCopy(renderer, textureB, NULL, &rect);
            }
            else if(grid[i][j] == 1){
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
     SDL_Delay(3000);
     statut = EXIT_SUCCESS;
Quit:
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
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
}