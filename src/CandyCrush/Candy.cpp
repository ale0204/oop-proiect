#include "../../include/CandyCrush/Candy.h"
#include "../../include/CandyCrush/Constants.h"
#include "../../include/CandyCrush/TextureManager.h"

Candy::Candy(SDL_Texture *texture, const SDL_Rect &srcRect, const SDL_Rect &dstRect, CandyColor color, CandyType type)
    : GameObject(texture, srcRect, dstRect), color {color}, type {type}, posX{0}, posY{0}, shouldDelete {false}, isMoving {false}
{
}

void Candy::Draw() const
{
    SDL_RenderCopy(GUIManager::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
}

Candy* Candy::Clone()
{
    return new Candy(*this);
}
CandyColor Candy::GetColor(void) const
{
    return color;
}

CandyType Candy::GetType(void) const
{
    return type;
}

SDL_Point Candy::GetPosition(void) const
{
    SDL_Point point;
    point.x = posX; point.y = posY;
    return point;
}

void Candy::SetPosition(int x, int y)
{
    posX = x;
    posY = y;
}

void Candy::MarkForDeletion(void)
{
    shouldDelete = true;
}

void Candy::MoveY(int dy)
{
    dstRect.y += dy;
}
bool Candy::ShouldDelete(void) const
{
    return shouldDelete;
}

bool Candy::IsMoving(void) const
{
    return isMoving;
}

void Candy::SetMoving(bool moving)
{
    isMoving = moving;
}
void Candy::SwapCandies(Candy *candy1, Candy *candy2)
{
    if (candy1 == nullptr || candy2 == nullptr) {
        return; // Guard against null pointers
    }
    // std::swap(candy1->srcRect, candy2->srcRect);
    std::swap(candy1->dstRect, candy2->dstRect);
    std::swap(candy1->posX, candy2->posX);
    std::swap(candy1->posY, candy2->posY);
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

Candy* Candy::GenerateRandomCandy(void)
{
    return TextureManager::GetInstance().GetCandy(CandyType::NORMAL_CANDY, RandomColor());
}