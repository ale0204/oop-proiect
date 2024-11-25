#include "../../include/CandyCrush/CandyCrush.h"
#include "../../include/CandyCrush/TextureManager.h"
#include "../../include/CandyCrush/Constants.h"
#include <SDL2/SDL.h>

CandyCrush::CandyCrush(const std::string &windowTitle, int x, int y, int w, int h, int fps)
    : Game(windowTitle, x, y, w, h, fps), BOARD_SIZE_X{::BOARD_SIZE_X}, BOARD_SIZE_Y{::BOARD_SIZE_Y}
{   
    
    candies = std::vector<std::vector<Candy*>>(BOARD_SIZE_X, std::vector<Candy*>(BOARD_SIZE_Y));
    
    SDL_Point dstXY = {.x = initX, .y = initY};
    for(size_t i = 0; i < candies.size(); i++)
    {
        dstXY.x = initX;
        for(size_t j = 0; j < candies[i].size(); j++)
        {
            candies[i][j] = nullptr;
            // do {
            if(candies[i][j] != nullptr)
            {
                delete candies[i][j];
                candies[i][j] = nullptr;
            }
            candies[i][j] = TextureManager::GetInstance().GetCandy(CandyType::NORMAL_CANDY, Candy::RandomColor());
            // }while(MatchFound(candies[i][j]) == false);
            candies[i][j]->SetDstRectXY(dstXY);
            dstXY.x += CANDY_WIDTH_DST;
        }
        dstXY.y += CANDY_HEIGHT_DST;
    }
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
            case SDL_MOUSEBUTTONDOWN: {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point *position = Candy::GetPosition(mouseX, mouseY);
                if(position != nullptr)
                    printf("Clicked (%d, %d) in (%d, %d)\n", mouseX, mouseY, position->x, position->y);
                else
                    printf("Clicked outside of the candy matrix\n");
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
    for(size_t i = 0; i < candies.size(); i++)
        for(GameObject *candy : candies[i])
            candy->Draw();
}


CandyCrush::~CandyCrush()   
{

}