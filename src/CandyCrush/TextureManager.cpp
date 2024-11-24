#include "../../include/CandyCrush/TextureManager.h"


const int NUM_CANDIES = 6;
const int CANDY_OFFSET_X = 0;
const int CANDY_OFFSET_Y = 240;
const int CANDY_WIDTH = 120;
const int CANDY_HEIGHT = CANDY_WIDTH;

TextureManager* TextureManager::instance = nullptr;


TextureManager::TextureManager(const std::string& spritesPath, const std::string& backgroundPath)
    : spritesPath {spritesPath}, backgroundPath {backgroundPath} {}

TextureManager& TextureManager::GetInstance()
{
    if(instance == nullptr) {
        instance = new TextureManager();
        instance->LoadGameObjects(GUIManager::GetInstance().GetRenderer());
    }
    return *instance;
}

GameObject* TextureManager::GetCandy(CandyType candyType, CandyColor candyColor)
{
    int candyColorIdx = static_cast<int>(candyColor);
    switch(candyType)
    {
        case CandyType::NORMAL_CANDY: {
            return candies[candyColorIdx];
        }
        case CandyType::HORIZONTAL_STRIPED_CANDY: {
            return horizontalStripedCandies[candyColorIdx];
        }
        case CandyType::VERTICAL_STRIPED_CANDY: {
            return verticalStripedCandies[candyColorIdx];
        }
        case CandyType::BOMB_CANDY: {
            return bombCandies[candyColorIdx];
        }
        case CandyType::WILD_CANDY: {
            return wildCandy;
        }
    }
}

GameObject* TextureManager::GetBackground(void)
{
    return background;
}

SDL_Texture* TextureManager::CreateTextureFromImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = IMG_Load(path);
    if(surface == NULL)
    {
        std::cerr << "File " << path << " not found\n";
        exit(EXIT_FAILURE);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::LoadGameObjects(SDL_Renderer *renderer)
{
    SDL_Texture *board = CreateTextureFromImage(renderer, spritesPath.c_str());

    LoadCandies(board, candies);
    LoadVerticalStripedCandies(board, verticalStripedCandies);
    LoadHorizontalStripedCandies(board, horizontalStripedCandies);
    LoadBombCandies(board, bombCandies);
    wildCandy = LoadWildCandy(board);
    background = LoadBackground(backgroundPath.c_str());
}

void TextureManager::LoadCandies(SDL_Texture *board, std::vector<GameObject*>& candies)
{
    SDL_Rect srcRect = {.x = CANDY_OFFSET_X, .y = CANDY_OFFSET_Y, .w = CANDY_WIDTH, .h = CANDY_HEIGHT};
    SDL_Rect dstRect = {.x = 50, .y = 50, .w = CANDY_WIDTH/2, .h = CANDY_HEIGHT/2};
    for(int i = 0; i < NUM_CANDIES; i++)
    {
        candies.push_back(new Candy(board, srcRect, dstRect, static_cast<CandyColor>(i), CandyType::NORMAL_CANDY));
        dstRect.x += dstRect.w;
        srcRect.x += srcRect.w;
    }
}

void TextureManager::LoadVerticalStripedCandies(SDL_Texture *board, std::vector<GameObject*>& verticalStripedCandies)
{

}

void TextureManager::LoadHorizontalStripedCandies(SDL_Texture *board, std::vector<GameObject*>& horizontalStripedCandies)
{

}

void TextureManager::LoadBombCandies(SDL_Texture *board, std::vector<GameObject*>& bombCandies)
{

}

GameObject* TextureManager::LoadBackground(const char *path)
{
    return nullptr;
}

GameObject* TextureManager::LoadWildCandy(SDL_Texture *board)
{
    return nullptr;
}
