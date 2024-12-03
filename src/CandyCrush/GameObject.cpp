#include "../../include/CandyCrush/GameObject.h"
#include "../../include/CandyCrush/GUIManager.h"
#include <SDL2/SDL.h>

GameObject::GameObject(SDL_Texture *texture, const SDL_Rect &srcRect, const SDL_Rect &dstRect)
    : texture {texture}, srcRect {srcRect}, dstRect {dstRect}
{
}

void GameObject::Draw() const
{
    SDL_RenderCopy(GUIManager::GetInstance().GetRenderer(), texture, NULL, NULL);
}

SDL_Texture* GameObject::GetTexture(void) const
{
    return texture;
}

SDL_Rect GameObject::GetDstRect(void) const
{
    return dstRect;
}

GameObject* GameObject::Clone(void)
{
    return new GameObject(*this);
}
void GameObject::SetDstRectXY(const SDL_Point& point)
{
    dstRect.x = point.x;
    dstRect.y = point.y;
}