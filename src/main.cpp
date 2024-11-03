#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

int main() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello, SDL2!", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Delay(3000); // Wait for 3 seconds

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}