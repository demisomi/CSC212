#include "pyramid.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// Creates an array of points for a pyramid
std::vector<Point3D> points{
    Point3D{ 0, -1, 0 },   // Base center
    Point3D{ 1,  1, -1 },  // Front right
    Point3D{ -1, 1, -1 },  // Front left
    Point3D{ -1, 1, 1 },   // Back left
    Point3D{ 1,  1, 1 }    // Back right
};

// Creates an array of edges for a pyramid
std::vector<Edge> edges{
    Edge{ 0, 1 },  // Base center to front right
    Edge{ 0, 2 },  // Base center to front left
    Edge{ 0, 3 },  // Base center to back left
    Edge{ 0, 4 },  // Base center to back right
    Edge{ 1, 2 },  // Front right to front left
    Edge{ 2, 3 },  // Front left to back left
    Edge{ 3, 4 },  // Back left to back right
    Edge{ 4, 1 }   // Back right to front right
};

/*
//default C++ function
int main(int argc, char* argv[])
{
    //creating a window and a renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    //creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Cube Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    //Creating an instance of the the Renderer3D class
    Renderer3D render3D(window, renderer, points, edges);

    while (running)
    {
        //if the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        //Calls the function created in the Renderer3D class (render 3D is an instance of the class defined above)
        render3D.render();
    }


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }

    std::cin.get();
    return 0;



    return 0;
}
*/
