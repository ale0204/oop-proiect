#include "../../include/CandyCrush/CandyCrush.h"
#include "../../include/CandyCrush/TextureManager.h"
#include <SDL2/SDL.h>

const int NUM_CANDIES = 6;

CandyCrush::CandyCrush(const std::string &windowTitle, int x, int y, int w, int h, int fps)
    : Game(windowTitle, x, y, w, h, fps)
{
    CandyType candyType = CandyType::NORMAL_CANDY;
    for(int i = 0; i < NUM_CANDIES; i++)
        candies.push_back(TextureManager::GetInstance().GetCandy(candyType, static_cast<CandyColor>(i)));
}

void CandyCrush::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
            case SDL_QUIT: {
                running = false;
                break;
            }
            case SDL_KEYDOWN: {
                // HandleKeyDownEvent(event);
                break;
            }
            default: {
                // events not handled yet or that don't require handling
                break;
            }
        }
    }
}
void CandyCrush::Update()
{

}
void CandyCrush::Render()
{
    SDL_RenderClear(renderer);
    RenderBackground();
    RenderBoard();
    SDL_RenderPresent(renderer);
}

void CandyCrush::RenderBackground()
{

}

void CandyCrush::RenderBoard()
{
    for(GameObject *candy : candies)
        candy->Draw();
}


CandyCrush::~CandyCrush()   
{

}