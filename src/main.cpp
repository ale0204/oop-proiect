#define SDL_MAIN_HANDLED
#include "../include/TestTable.h"
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void ShowTestWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    // Create SDL window
    SDL_Window *window = SDL_CreateWindow("SDL2, TTF, and Image Test",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Load an image (adjust the path to your image file)
    SDL_Surface *imageSurface = IMG_Load("assets/images/background.png");
    if (!imageSurface) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
    } else {
        SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);

        // Render image
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(imageTexture);
    }

    // Load font and render text (adjust font path and size)
    TTF_Font *font = TTF_OpenFont("assets/fonts/times.ttf", 24);
    if (!font) {
        std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
    } else {
        SDL_Color color = {.r = 255, .g = 255, .b = 255, .a = 255};  // White color
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", color);
        if (textSurface) {
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);

            // Render text
            SDL_Rect textRect = {20, 20, 200, 50}; // x, y, width, height
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        } else {
            std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
        }

        TTF_CloseFont(font);
    }

    // Wait for a few seconds to see the result
    SDL_Delay(5000);

    // Clean up and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main() 
{   
    // TestTable& testTable = TestTable::GetInstance();
    // std::vector<TestTableEntry> entries = testTable.Select();

    // std::for_each(entries.begin(), entries.end(), 
    //     [](const TestTableEntry& entry) {
    //         std::cout << entry << std::endl;
    //     }
    // );
    
    // TestTableEntry entry;
    // std::cin >> entry;
    // if(testTable.Insert(entry))
    // {
    //     std::cout << "Inserted with id " << entry.GetID() << '\n';
    // }
    
    // entries = testTable.Select();
    // std::cout << "Updated table:\n";
    // std::for_each(entries.begin(), entries.end(), 
    //     [](const TestTableEntry& entry) {
    //         std::cout << entry << std::endl;
    //     }
    // );

    ShowTestWindow();

    return 0;
}