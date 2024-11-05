#define SDL_MAIN_HANDLED
#include "../include/TestTable.h"
#include <algorithm>
#include <SDL2/SDL.h>
void ShowTestWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() 
{   
    TestTable& testTable = TestTable::GetInstance();
    std::vector<TestTableEntry> entries = testTable.Select();

    std::for_each(entries.begin(), entries.end(), 
        [](const TestTableEntry& entry) {
            std::cout << entry << std::endl;
        }
    );
    
    TestTableEntry entry;
    std::cin >> entry;
    if(testTable.Insert(entry))
    {
        std::cout << "Inserted with id " << entry.GetID() << '\n';
    }
    
    entries = testTable.Select();
    std::cout << "Updated table:\n";
    std::for_each(entries.begin(), entries.end(), 
        [](const TestTableEntry& entry) {
            std::cout << entry << std::endl;
        }
    );

    ShowTestWindow();

    return 0;
}