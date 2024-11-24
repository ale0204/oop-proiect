#include "../../include/CandyCrush/Candy.h"

Candy::Candy(SDL_Texture *texture, const SDL_Rect &srcRect, const SDL_Rect &dstRect, CandyColor color, CandyType type)
    : GameObject(texture, srcRect, dstRect), color {color}, type {type}
{
}

void Candy::Draw()
{
    SDL_RenderCopy(GUIManager::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
} 
