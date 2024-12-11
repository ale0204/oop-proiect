#include "../../include/CandyCrush/Game.h"
#include "../../include/CandyCrush/GUIManager.h"
#include "../../include/CandyCrush/TextureManager.h"
#include "../../include/CandyCrush/CandyCrush.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>


Game::Game(const std::string& windowTitle, int x, int y, int w, int h, int fps)
    : running {true}, fps {fps}, frameTime{1000/static_cast<Uint64>(fps)}
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::string exception_message = std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError() + '\n';
        SDL_Quit();
        throw SDLInitException(exception_message, 100);
    }
    if (TTF_Init() == -1) {
        std::string exception_message = std::string("TTF_Init failed: ") + TTF_GetError() + '\n';
        SDL_Quit(); TTF_Quit();
        throw TTFInitException(exception_message, 200);
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::string exception_message = std::string("IMG_Init failed: ") + IMG_GetError() + '\n';
        SDL_Quit(); TTF_Quit(); IMG_Quit();
        throw IMGInitException(exception_message, 300);
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(windowTitle.c_str(), x, y, w, h, 0);
    if(window == NULL)
    {
        std::cerr << "SDL_CreateWindow() failed: " << SDL_GetError() << '\n';
        TTF_Quit(); SDL_Quit(); IMG_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL)
    {
        std::cerr << "SDL_CreateRenderer() failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        TTF_Quit(); SDL_Quit(); IMG_Quit();
        exit(EXIT_FAILURE);
    }

    GUIManager::GetInstance().SetWindow(window);
    GUIManager::GetInstance().SetRenderer(renderer);
}

void Game::Play()
{
    while(running == true)
    {
        Uint64 deltaTime;
        Uint64 frameStart = SDL_GetTicks64();
    
        HandleEvents();
        Update();
        Render();
        
        deltaTime = SDL_GetTicks64() - frameStart;
        if(deltaTime < frameTime)
            SDL_Delay(static_cast<Uint32>(frameTime - deltaTime));
    }
}

Game::~Game()
{
    std::cout << "~Game()\n";
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit(); SDL_Quit(); IMG_Quit();
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    game.Afisare(os);
    return os;
}