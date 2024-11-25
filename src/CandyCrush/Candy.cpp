#include "../../include/CandyCrush/Candy.h"
#include "../../include/CandyCrush/Constants.h"

Candy::Candy(SDL_Texture *texture, const SDL_Rect &srcRect, const SDL_Rect &dstRect, CandyColor color, CandyType type)
    : GameObject(texture, srcRect, dstRect), color {color}, type {type}
{}

void Candy::Draw()
{
    SDL_RenderCopy(GUIManager::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
}

SDL_Point* Candy::GetPosition(int mouseX, int mouseY)
{
    static SDL_Point position;
    int dy = (mouseY - initY);
    int dx = (mouseX - initX);
    position.x = dy / CANDY_HEIGHT_DST;
    position.y = dx / CANDY_WIDTH_DST;
    if(dx < 0 || dy < 0)
        return nullptr;
    if(position.x < 0 || position.x >= BOARD_SIZE_X)
        return nullptr;
    if(position.y < 0 || position.y >= BOARD_SIZE_Y)
        return nullptr;
    return &position;
}

CandyColor Candy::RandomColor(void)
{
    return static_cast<CandyColor>(rand() % static_cast<int>(CandyColor::NUM_CANDIES));
}