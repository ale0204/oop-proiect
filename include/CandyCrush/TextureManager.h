#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Candy.h"
#include "GUIManager.h"
#include "enums/CandyColor.h"
#include "enums/CandyType.h"
#define CC_RELEASE 1
class TextureManager {
private:
    const std::string spritesPath;
    const std::string backgroundPath;
    std::vector<Candy*> candies;
    std::vector<Candy*> verticalStripedCandies;
    std::vector<Candy*> horizontalStripedCandies;
    std::vector<Candy*> bombCandies;
    SDL_Texture *spritesheet;
    Candy *wildCandy;
    GameObject *background;
private:
    static TextureManager *instance;
#ifdef CC_RELEASE
    TextureManager(const std::string& spritesPath = "assets/images/candy_crush_spritesheet.png",
                   const std::string& backgroundPath = "assets/images/background.png");
#else
    TextureManager(const std::string& spritesPath = "../assets/images/candy_crush_spritesheet.png",
                   const std::string& backgroundPath = "../assets/images/background.png");
#endif
public:
    static TextureManager& GetInstance();
    Candy* GetCandy(CandyType candyType, CandyColor candyColor) const;
    GameObject* GetBackground(void) const;
private:
    SDL_Texture* CreateTextureFromImage(SDL_Renderer *renderer, const char *path);
    void LoadGameObjects(SDL_Renderer *renderer);
    void LoadCandies(SDL_Texture *board, std::vector<Candy*>& candyVector);
    // TODO altadata
    void LoadVerticalStripedCandies(SDL_Texture *board, std::vector<Candy*>& stripedCandyVector);
    void LoadHorizontalStripedCandies(SDL_Texture *board, std::vector<Candy*>& stripedCandyVector);
    void LoadBombCandies(SDL_Texture *board, std::vector<Candy*>& bombCandyVector);
    GameObject* LoadBackground(const char *path);
    Candy* LoadWildCandy(SDL_Texture *board);
};

#endif /* TEXTURE_MANAGER_H_ */