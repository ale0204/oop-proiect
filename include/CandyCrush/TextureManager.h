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

class TextureManager {
private:
    const std::string spritesPath;
    const std::string backgroundPath;
    std::vector<GameObject*> candies;
    std::vector<GameObject*> verticalStripedCandies;
    std::vector<GameObject*> horizontalStripedCandies;
    std::vector<GameObject*> bombCandies;
    GameObject *wildCandy;
    GameObject *background;
private:
    static TextureManager *instance;
    TextureManager(const std::string& spritesPath = "../assets/images/candy_crush_spritesheet.png",
                   const std::string& backgroundPath = "../assets/images/background.png");
public:
    static TextureManager& GetInstance();
    GameObject* GetCandy(CandyType candyType, CandyColor candyColor);
    GameObject* GetBackground(void);
private:
    SDL_Texture* CreateTextureFromImage(SDL_Renderer *renderer, const char *path);
    void LoadGameObjects(SDL_Renderer *renderer);
    void LoadCandies(SDL_Texture *board, std::vector<GameObject*>& candies);
    void LoadVerticalStripedCandies(SDL_Texture *board, std::vector<GameObject*>& verticalStripedCandies);
    void LoadHorizontalStripedCandies(SDL_Texture *board, std::vector<GameObject*>& horizontalStripedCandies);
    void LoadBombCandies(SDL_Texture *board, std::vector<GameObject*>& bombCandies);
    GameObject* LoadBackground(const char *path);
    GameObject* LoadWildCandy(SDL_Texture *board);
};

#endif /* TEXTURE_MANAGER_H_ */