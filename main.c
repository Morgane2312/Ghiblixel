#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 715
#define WINDOW_HEIGHT 500
#define PACMAN_SIZE 30
#define PACMAN_SPEED 1
#define ENEMY_SIZE 25
#define ENEMY_SPEED 1.5
#define NUM_ENEMIES 6
#define NUM_PACMANS 1
#define MAX_BARRIERS 50
#define MAX_BAR_WIDTH 20
#define MAX_BAR_HEIGHT 50

typedef struct {
    int x, y, dx, dy, lives;
} Pacman;

typedef struct {
    int x, y, dx, dy;
} Enemy;

typedef struct {
    int x, y, width, height;
} Barrier;

Pacman pacmanSingle = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0, 5};
Pacman pacmans[NUM_PACMANS];
Enemy enemies[NUM_ENEMIES];
SDL_Texture* enemyTexture = NULL;

SDL_Texture* pacmanTextureGauche1 = NULL;
SDL_Texture* pacmanTextureGauche2 = NULL;
SDL_Texture* pacmanTextureDerriere = NULL;
SDL_Texture* pacmanTextureDevant1 = NULL;
SDL_Texture* pacmanTextureDevant2 = NULL;
SDL_Texture* pacmanTextureDroit1 = NULL;
SDL_Texture* pacmanTextureDroit2 = NULL;
SDL_Texture* pacmanTextureDebut = NULL;
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* menuTexture = NULL;
SDL_Texture* deathTexture = NULL;
Barrier barriers[MAX_BARRIERS];

void loadPacmanTextures(SDL_Renderer* renderer) {
    const char* filePathGauche1 = "assets/totoro_gauche_1.png";
    const char* filePathGauche2 = "assets/totoro_gauche_2.png";
    const char* filePathDerriere = "assets/totoro_dos.png";
    const char* filePathDevant1 = "assets/totoro_bas_1.png";
    const char* filePathDevant2 = "assets/totoro_bas_2.png";
    const char* filePathDroit1 = "assets/totoro_droit_1.png";
    const char* filePathDroit2 = "assets/totoro_droit_2.png";
    const char* filePathDebut = "assets/totoro.png";
    
printf("Loading textures from:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           filePathGauche1, filePathGauche2, filePathDerriere, filePathDevant1,
           filePathDevant2, filePathDroit1, filePathDroit2, filePathDebut);
    
    SDL_Surface* tempSurfaceGauche1 = IMG_Load(filePathGauche1);
    SDL_Surface* tempSurfaceGauche2 = IMG_Load(filePathGauche2);
    SDL_Surface* tempSurfaceDerriere = IMG_Load(filePathDerriere);
    SDL_Surface* tempSurfaceDevant1 = IMG_Load(filePathDevant1);
    SDL_Surface* tempSurfaceDevant2 = IMG_Load(filePathDevant2);
    SDL_Surface* tempSurfaceDroit1 = IMG_Load(filePathDroit1);
    SDL_Surface* tempSurfaceDroit2 = IMG_Load(filePathDroit2);
    SDL_Surface* tempSurfaceDebut = IMG_Load(filePathDebut);

   if (!tempSurfaceGauche1 || !tempSurfaceGauche2 || !tempSurfaceDerriere || !tempSurfaceDevant1 || !tempSurfaceDevant2 || !tempSurfaceDroit1 || !tempSurfaceDroit2 || !tempSurfaceDebut) {
        printf("Impossible de charger l'une des images! Erreur SDL: %s\n", IMG_GetError());
        exit(1);
    }

    pacmanTextureGauche1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceGauche1);
    pacmanTextureGauche2 = SDL_CreateTextureFromSurface(renderer, tempSurfaceGauche2);
    pacmanTextureDerriere = SDL_CreateTextureFromSurface(renderer, tempSurfaceDerriere);
    pacmanTextureDevant1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceDevant1);
    pacmanTextureDevant2 = SDL_CreateTextureFromSurface(renderer, tempSurfaceDevant2);
    pacmanTextureDroit1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceDroit1);
    pacmanTextureDroit2 = SDL_CreateTextureFromSurface(renderer, tempSurfaceDroit2);
    pacmanTextureDebut = SDL_CreateTextureFromSurface(renderer, tempSurfaceDebut);

    SDL_FreeSurface(tempSurfaceGauche1);
    SDL_FreeSurface(tempSurfaceGauche2);
    SDL_FreeSurface(tempSurfaceDerriere);
    SDL_FreeSurface(tempSurfaceDevant1);
    SDL_FreeSurface(tempSurfaceDevant2);
    SDL_FreeSurface(tempSurfaceDroit1);
    SDL_FreeSurface(tempSurfaceDroit2);
    SDL_FreeSurface(tempSurfaceDebut);
}

void initBarriers() {
    // Barrières horizontales
    barriers[0].x = 206;
    barriers[0].y = 165;
    barriers[0].width = 57;
    barriers[0].height = 10;

    barriers[1].x = 315;
    barriers[1].y = 164;
    barriers[1].width = 160;
    barriers[1].height = 10;

    barriers[2].x = 260;
    barriers[2].y = 115;
    barriers[2].width = 52;
    barriers[2].height = 10;

    barriers[3].x = 360;
    barriers[3].y = 370;
    barriers[3].width = 90;
    barriers[3].height = 10;

    barriers[4].x = 150;
    barriers[4].y = 416;
    barriers[4].width = 350;
    barriers[4].height = 8;

    barriers[5].x = 130;
    barriers[5].y = 325;
    barriers[5].width = 50;
    barriers[5].height = 10;

    barriers[6].x = 120;
    barriers[6].y = 385;
    barriers[6].width = 35;
    barriers[6].height = 8;

    barriers[7].x = 495;
    barriers[7].y = 350;
    barriers[7].width = 100;
    barriers[7].height = 8;

    barriers[8].x = 550;
    barriers[8].y = 203;
    barriers[8].width = 40;
    barriers[8].height = 8;

    barriers[9].x = 164;
    barriers[9].y = 50;
    barriers[9].width = 325;
    barriers[9].height = 8;

    barriers[10].x = 120;
    barriers[10].y = 150;
    barriers[10].width = 40;
    barriers[10].height = 8;
       
    barriers[11].x = 490;
    barriers[11].y = 85;
    barriers[11].width = 50;
    barriers[11].height = 8;

    barriers[12].x = 533;
    barriers[12].y = 270;
    barriers[12].width = 50;
    barriers[12].height = 8;

    // Barrières verticales
    barriers[13].x = 115;
    barriers[13].y = 160;
    barriers[13].width = 8;
    barriers[13].height = 235;

    barriers[14].x = 590;
    barriers[14].y = 203;
    barriers[14].width = 8;
    barriers[14].height = 155;

    barriers[15].x = 545;
    barriers[15].y = 90;
    barriers[15].width = 8;
    barriers[15].height = 120;

    barriers[16].x = 490;
    barriers[16].y = 350;
    barriers[16].width = 8;
    barriers[16].height = 70;

    barriers[17].x = 150;
    barriers[17].y = 390;
    barriers[17].width = 8;
    barriers[17].height = 30;

    barriers[18].x = 150;
    barriers[18].y = 60;
    barriers[18].width = 8;
    barriers[18].height = 98;

    barriers[19].x = 260;
    barriers[19].y = 55;
    barriers[19].width = 8;
    barriers[19].height = 60;

    barriers[20].x = 205;
    barriers[20].y = 55;
    barriers[20].width = 8;
    barriers[20].height = 110;

    barriers[21].x = 305;
    barriers[21].y = 122;
    barriers[21].width = 8;
    barriers[21].height = 50;

    barriers[22].x = 475;
    barriers[22].y = 170;
    barriers[22].width = 8;
    barriers[22].height = 80;

    barriers[23].x = 450;
    barriers[23].y = 290;
    barriers[23].width = 8;
    barriers[23].height = 80;

    barriers[24].x = 350;
    barriers[24].y = 220;
    barriers[24].width = 8;
    barriers[24].height = 160;

    barriers[25].x = 180;
    barriers[25].y = 270;
    barriers[25].width = 8;
    barriers[25].height = 60;

    barriers[26].x = 255;
    barriers[26].y = 165;
    barriers[26].width = 8;
    barriers[26].height = 60;

    barriers[27].x = 490;
    barriers[27].y = 50;
    barriers[27].width = 8;
    barriers[27].height = 35;

    //Autour de la map
    barriers[28].x = 0;
    barriers[28].y = 420;
    barriers[28].width = 715;
    barriers[28].height = 200;

    barriers[29].x = 0;
    barriers[29].y = 0;
    barriers[29].width = 115;
    barriers[29].height = 800;

    barriers[30].x = 0;
    barriers[30].y = 500;
    barriers[30].width = 50;
    barriers[30].height = 55;

    barriers[31].x = 495;
    barriers[31].y = 35;
    barriers[31].width = 300;
    barriers[31].height = 55;

    barriers[32].x = 100;
    barriers[32].y = 35;
    barriers[32].width = 55;
    barriers[32].height = 120;

    barriers[33].x = 100;
    barriers[33].y = 390;
    barriers[33].width = 55;
    barriers[33].height = 120;

    barriers[34].x = 500;
    barriers[34].y = 400;
    barriers[34].width = 50;
    barriers[34].height = 50;

    barriers[35].x = 0;
    barriers[35].y = 0;
    barriers[35].width = 715;
    barriers[35].height = 54;

    barriers[36].x = 598;
    barriers[36].y = 0;
    barriers[36].width = 120;
    barriers[36].height = 500;

    barriers[37].x = 550;
    barriers[37].y = 50;
    barriers[37].width = 50;
    barriers[37].height = 155;

    barriers[38].x = 498;
    barriers[38].y = 350;
    barriers[38].width = 200;
    barriers[38].height = 155;
}

void handleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_UP:    pacmanSingle.dy = -1; pacmanSingle.dx = 0; break;
        case SDLK_DOWN:  pacmanSingle.dy = 1;  pacmanSingle.dx = 0; break;
        case SDLK_LEFT:  pacmanSingle.dx = -1; pacmanSingle.dy = 0; break;
        case SDLK_RIGHT: pacmanSingle.dx = 1;  pacmanSingle.dy = 0; break;
        default: break;
    }
}

void updatePacman() {
    int newX = pacmanSingle.x + pacmanSingle.dx * PACMAN_SPEED;
    int newY = pacmanSingle.y + pacmanSingle.dy * PACMAN_SPEED;

    for (int i = 0; i < MAX_BARRIERS; i++) {
        int barrierX = barriers[i].x;
        int barrierY = barriers[i].y;
        int barrierWidth = barriers[i].width;
        int barrierHeight = barriers[i].height;

        // Vérifier la collision avec la barrière
        if (newX < barrierX + barrierWidth &&
            newX + PACMAN_SIZE > barrierX &&
            newY < barrierY + barrierHeight &&
            newY + PACMAN_SIZE > barrierY) {
            // Collision détectée, annuler le déplacement
            newX = pacmanSingle.x;
            newY = pacmanSingle.y;
        }
    }

    // Limiter les mouvements à l'intérieur de la fenêtre
    if (newX < 0) newX = 0;
    if (newX > WINDOW_WIDTH - PACMAN_SIZE) newX = WINDOW_WIDTH - PACMAN_SIZE;
    if (newY < 0) newY = 0;
    if (newY > WINDOW_HEIGHT - PACMAN_SIZE) newY = WINDOW_HEIGHT - PACMAN_SIZE;

    pacmanSingle.x = newX;
    pacmanSingle.y = newY;
}

void loadMenuTexture(SDL_Renderer* renderer) {
    const char* menuFilePath = "assets/menu.png";
    SDL_Surface* tempSurface = IMG_Load(menuFilePath);
    if (!tempSurface) {
        printf("Impossible de charger l'image du menu %s! Erreur SDL: %s\n", menuFilePath, IMG_GetError());
        exit(1);
    }
    menuTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void initEnemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i].x = rand() % (WINDOW_WIDTH - PACMAN_SIZE);
        enemies[i].y = rand() % (WINDOW_HEIGHT - PACMAN_SIZE);
        if (rand() % 2) {
            enemies[i].dx = (rand() % 2) * 2 - 1; 
            enemies[i].dy = 0;
        } else {                                  
            enemies[i].dx = 0;
            enemies[i].dy = (rand() % 2) * 2 - 1;
        }
    }
}

void loadEnemyTexture(SDL_Renderer* renderer) {
    const char* filePath = "assets/noiraude.png";
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (!tempSurface) {
        printf("Impossible de charger l'image %s! SDL Error: %s\n", filePath, IMG_GetError());
        exit(1);
    }
    enemyTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath) {
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (!tempSurface) {
        printf("Impossible de charger l'image %s! SDL Error: %s\n", filePath, IMG_GetError());
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void updateEnemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        // Calculer la nouvelle position des ennemis
        int newX = (int)(enemies[i].x + enemies[i].dx * ENEMY_SPEED);
        int newY = (int)(enemies[i].y + enemies[i].dy * ENEMY_SPEED);

        // Vérifier les collisions avec les barrières
        for (int j = 0; j < MAX_BARRIERS; j++) {
            if (newX < barriers[j].x + barriers[j].width &&
                newX + ENEMY_SIZE > barriers[j].x &&
                newY < barriers[j].y + barriers[j].height &&
                newY + ENEMY_SIZE > barriers[j].y) {
                // Collision détectée, inverser la direction de déplacement
                enemies[i].dx *= -1;
                enemies[i].dy *= -1;
                break; // Sortir de la boucle pour éviter de vérifier les collisions avec d'autres barrières
            }
        }

        // Mettre à jour la position des ennemis
        enemies[i].x = newX;
        enemies[i].y = newY;

        // Vérifier les collisions avec les bords de l'écran
        if (enemies[i].x <= 0 || enemies[i].x >= WINDOW_WIDTH - ENEMY_SIZE) enemies[i].dx *= -1;
        if (enemies[i].y <= 0 || enemies[i].y >= WINDOW_HEIGHT - ENEMY_SIZE) enemies[i].dy *= -1;
    }
}
bool checkCollision(Enemy* enemy, Pacman* pacman) {
    return !(enemy->x + PACMAN_SIZE < pacman->x || enemy->x > pacman->x + PACMAN_SIZE ||
             enemy->y + PACMAN_SIZE < pacman->y || enemy->y > pacman->y + PACMAN_SIZE);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Could not initialize SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    loadPacmanTextures(renderer);
    loadEnemyTexture(renderer);

    backgroundTexture = loadTexture(renderer, "assets/map_1.png");
    loadMenuTexture(renderer);
    deathTexture = loadTexture(renderer, "assets/mort.png");

    initBarriers(); // Initialisation des barrières
    initEnemies();

    bool running = true;
    bool gameOver = false; // Déclaration de la variable pour suivre l'état du jeu
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                handleInput(event);
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Code pour relancer le jeu après la mort
                if (gameOver) {
                    // Réinitialisation du jeu
                    pacmanSingle.lives = 5;
                    initBarriers();
                    initEnemies();
                    gameOver = false;
                }
            }
        }

        if (!gameOver) {
            if (pacmanSingle.dx == 0 && pacmanSingle.dy == 0) {
                SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
                SDL_RenderPresent(renderer);
                continue;
            }

            updatePacman();
            updateEnemies();

            for (int i = 0; i < NUM_ENEMIES; i++) {
                if (checkCollision(&enemies[i], &pacmanSingle)) {
                    pacmanSingle.lives--;
                    printf("Pacman touché ! Vies restantes : %d\n", pacmanSingle.lives);
                    if (pacmanSingle.lives <= 0) {
                        printf("Pacman a perdu toutes ses vies ! Fin du jeu.\n");
                        // Code pour la fin du jeu
                        gameOver = true;
                    }

                    enemies[i].x = rand() % (WINDOW_WIDTH - PACMAN_SIZE);
                    enemies[i].y = rand() % (WINDOW_HEIGHT - PACMAN_SIZE);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 125, 175, 66, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Affichage des barrières
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < MAX_BARRIERS; i++) {
            SDL_Rect barrierRect = { barriers[i].x, barriers[i].y, barriers[i].width, barriers[i].height };
            SDL_RenderFillRect(renderer, &barrierRect);
        }

        // Affichage des ennemis
        SDL_Rect enemyRect = { 0, 0, ENEMY_SIZE, ENEMY_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        
        for (int i = 0; i < NUM_ENEMIES; i++) {
            enemyRect.x = enemies[i].x;
            enemyRect.y = enemies[i].y;
            SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyRect);
        }

        // Affichage de Pacman
        SDL_Rect pacmanRect = { pacmanSingle.x, pacmanSingle.y, PACMAN_SIZE, PACMAN_SIZE };
        SDL_Texture* currentTexture = NULL;

        if (pacmanSingle.dy == -1) {
            currentTexture = pacmanTextureDerriere;
        } else if (pacmanSingle.dx == 1) {
            currentTexture = (SDL_GetTicks() / 250) % 2 == 0 ? pacmanTextureDroit1 : pacmanTextureDroit2;
        } else if (pacmanSingle.dx == -1) {
            currentTexture = (SDL_GetTicks() / 250) % 2 == 0 ? pacmanTextureGauche1 : pacmanTextureGauche2;
        } else if (pacmanSingle.dy == 1) {
            currentTexture = (SDL_GetTicks() / 250) % 2 == 0 ? pacmanTextureDevant1 : pacmanTextureDevant2;
        }

        if (currentTexture != NULL) {
            SDL_RenderCopy(renderer, currentTexture, NULL, &pacmanRect);
        }

        // Affichage de l'écran de fin si nécessaire
        if (gameOver) {
            SDL_RenderCopy(renderer, deathTexture, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(pacmanTextureGauche1);
    SDL_DestroyTexture(pacmanTextureGauche2);
    SDL_DestroyTexture(pacmanTextureDerriere);
    SDL_DestroyTexture(pacmanTextureDevant1);
    SDL_DestroyTexture(pacmanTextureDevant2);
    SDL_DestroyTexture(pacmanTextureDroit1);
    SDL_DestroyTexture(pacmanTextureDroit2);
    SDL_DestroyTexture(pacmanTextureDebut);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(deathTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
