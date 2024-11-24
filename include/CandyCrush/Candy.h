#ifndef CANDY_H_
#define CANDY_H_
#include "GameObject.h"
#include "GUIManager.h"
#include "enums/CandyColor.h"
#include "enums/CandyType.h"

class Candy : public GameObject {
private:
    CandyColor color;
    CandyType type;
public:
    Candy(SDL_Texture *texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, CandyColor color, CandyType type);
    void Draw() override;
};
#endif /* CANDY_H_ */