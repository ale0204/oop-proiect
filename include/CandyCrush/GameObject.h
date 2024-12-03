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
    virtual void Draw() const;
    SDL_Texture* GetTexture(void) const;
    void SetDstRectXY(const SDL_Point& point);
    SDL_Rect GetDstRect(void) const;
    virtual GameObject* Clone(void);
    virtual ~GameObject() = default;
};

#endif /* GAME_OBJECT_H_ */