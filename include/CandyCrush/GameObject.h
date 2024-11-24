#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <SDL2/SDL.h>
#include <string>

class GameObject {
protected:
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
public:
    GameObject(SDL_Texture *texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect);
    virtual void Draw();
    SDL_Texture* GetTexture();
};

#endif /* GAME_OBJECT_H_ */