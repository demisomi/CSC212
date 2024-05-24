#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_SIZE = 50;
const int MOVE_SPEED = 5;
const int CHANGE_DIRECTION_INTERVAL = 100; // Change direction every 100 frames

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* ballTexture = NULL;
SDL_Rect ballRect = {0, 0, BALL_SIZE, BALL_SIZE};
int dx = MOVE_SPEED; // Horizontal movement speed
int dy = MOVE_SPEED; // Vertical movement speed
int frameCount = 0; // Frame count for changing direction

bool initSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("Moving Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    // Load ball texture
    ballTexture = IMG_LoadTexture(gRenderer, "ball.png");
    if (ballTexture == NULL) {
        printf("Failed to load ball texture!\n");
        return false;
    }

    return true;
}

void closeSDL() {
    // Free loaded texture
    SDL_DestroyTexture(ballTexture);
    ballTexture = NULL;

    // Destroy window and renderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void updateBallPosition() {
    // Update ball's position
    ballRect.x += dx;
    ballRect.y += dy;

    // Check if the ball hits the screen boundaries
    if (ballRect.x < 0 || ballRect.x > SCREEN_WIDTH - BALL_SIZE) {
        // Reverse horizontal direction
        dx = -dx;
    }
    if (ballRect.y < 0 || ballRect.y > SCREEN_HEIGHT - BALL_SIZE) {
        // Reverse vertical direction
        dy = -dy;
    }
}

void renderScene() {
    // Clear screen
    SDL_RenderClear(gRenderer);

    // Render ball
    SDL_RenderCopy(gRenderer, ballTexture, NULL, &ballRect);

    // Update screen
    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Load media
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        closeSDL();
        return -1;
    }

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Update ball's position
        updateBallPosition();

        // Increment frame count
        frameCount++;

        // Change direction periodically
        if (frameCount >= CHANGE_DIRECTION_INTERVAL) {
            // Generate random direction
            dx = (std::rand() % 2 == 0) ? MOVE_SPEED : -MOVE_SPEED;
            dy = (std::rand() % 2 == 0) ? MOVE_SPEED : -MOVE_SPEED;

            // Reset frame count
            frameCount = 0;
        }

        // Render scene
        renderScene();

        // Delay to control frame rate
        SDL_Delay(16); // Aim for ~60 frames per second
    }

    // Close SDL
    closeSDL();

    return 0;
}

