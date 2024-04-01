#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void drawPyramid() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
    SDL_RenderClear(renderer); // Clear the renderer

    // Define the vertices of the pyramid
    SDL_Point vertices[] = {
        {320, 100}, // Top point
        {200, 400}, // Bottom-left
        {440, 400}, // Bottom-right
        {320, 300}  // Center bottom
    };

    // Draw the triangles to form the pyramid
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set draw color to red
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y); // Top to bottom-left
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y); // Top to bottom-right
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[3].x, vertices[3].y); // Top to center bottom
    SDL_RenderDrawLine(renderer, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y); // Bottom-left to bottom-right
    SDL_RenderDrawLine(renderer, vertices[2].x, vertices[2].y, vertices[3].x, vertices[3].y); // Bottom-right to center bottom
    SDL_RenderDrawLine(renderer, vertices[3].x, vertices[3].y, vertices[1].x, vertices[1].y); // Center bottom to bottom-left

    SDL_RenderPresent(renderer); // Update the renderer
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("SDL2 Pyramid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Main loop flag
    int quit = 0;
    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Draw the pyramid
        drawPyramid();
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

