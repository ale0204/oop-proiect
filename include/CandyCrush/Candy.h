#ifndef CANDY_H_
#define CANDY_H_

#include <iostream>

#include "GameObject.h"
#include "GUIManager.h"
#include "enums/CandyColor.h"
#include "enums/CandyType.h"

class Candy : public GameObject {
private:
    CandyColor color;
    CandyType type;
    int posX;
    int posY;
public:
    Candy(SDL_Texture *texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, CandyColor color, CandyType type);
    void Draw() const override;
    virtual GameObject* Clone() override;
    CandyColor GetColor(void) const;
    CandyType GetType(void) const;
    SDL_Point GetPosition(void) const;
    void SetPosition(int x, int y);
    static void SwapCandies(Candy *candy1, Candy *candy2);
    static SDL_Point* GetPosition(int mouseX, int mouseY);
    static CandyColor RandomColor(void);
    ~Candy() override = default;
};

class DemoCandy {
public:
    virtual void FunctieVirtuala() {}
    virtual ~DemoCandy() = default;
};

class HorizontalStripedCandy : public DemoCandy {
public:
    void FunctieHorizontalStripedCandy(void)
    {
        std::cout << "Functie HorizontalStripedCandy\n";
    }
};

class VerticalStripedCandy : public DemoCandy {
public:
    void FunctieVerticalStripedCandy(void)
    {
        std::cout << "Functie VerticalStripedCandy\n";
    }
};

class BombCandy : public DemoCandy {
public:
    void FunctieBombCandy(void)
    {
        std::cout << "Functie BombCandy\n";
    }
};

class WildCandy : public DemoCandy {
public:
    void FunctieWildCandy(void)
    {
        std::cout << "Functie WildCandy\n";
    }
};

class CandyFactory {
public:
    static DemoCandy* CreateCandy(CandyType candyType)
    {
        switch(candyType)
        {
            case CandyType::NORMAL_CANDY: {
                std::cout << "Creez NORMAL CANDY\n";
                return new DemoCandy();
            }
            case CandyType::HORIZONTAL_STRIPED_CANDY: {
                std::cout << "Creez H CANDY\n";
                return new HorizontalStripedCandy();
            }
            case CandyType::VERTICAL_STRIPED_CANDY: {
                std::cout << "Creez V CANDY\n";
                return new VerticalStripedCandy();
            }
            case CandyType::BOMB_CANDY: {
                std::cout << "Creez BOMB CANDY\n";
                return new BombCandy();
            }
            case CandyType::WILD_CANDY: {
                std::cout << "Creez WILD CANDY\n";
                return new WildCandy();  
            }
            case CandyType::NUM_CANDIES:
            default: {
                break;
            }
        }
        return nullptr;
    }
};
#endif /* CANDY_H_ */