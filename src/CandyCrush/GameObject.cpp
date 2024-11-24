#include "../../include/CandyCrush/GameObject.h"
#include "../../include/CandyCrush/GUIManager.h"
#include <SDL2/SDL.h>

GameObject::GameObject(SDL_Texture *texture, const SDL_Rect &srcRect, const SDL_Rect &dstRect)
    : texture {texture}, srcRect {srcRect}, dstRect {dstRect}
{
}

void GameObject::Draw()
{
    SDL_RenderCopy(GUIManager::GetInstance().GetRenderer(), texture, NULL, NULL);
}

SDL_Texture* GameObject::GetTexture()
{
    return texture;
}