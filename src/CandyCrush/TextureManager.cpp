#include "../../include/CandyCrush/TextureManager.h"
#include "../../include/CandyCrush/Constants.h"

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

Candy* TextureManager::GetCandy(CandyType candyType, CandyColor candyColor)
{
    int candyColorIdx = static_cast<int>(candyColor);
    switch(candyType)
    {
        case CandyType::NORMAL_CANDY: {
            return new Candy(*candies[candyColorIdx]);
        }
        case CandyType::HORIZONTAL_STRIPED_CANDY: {
            return new Candy(*horizontalStripedCandies[candyColorIdx]);
        }
        case CandyType::VERTICAL_STRIPED_CANDY: {
            return new Candy(*verticalStripedCandies[candyColorIdx]);
        }
        case CandyType::BOMB_CANDY: {
            return new Candy(*bombCandies[candyColorIdx]);
        }
        case CandyType::WILD_CANDY: {
            return new Candy(*wildCandy);
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

void TextureManager::LoadCandies(SDL_Texture *board, std::vector<Candy*>& candies)
{
    SDL_Rect srcRect = {.x = CANDY_OFFSET_X, .y = CANDY_OFFSET_Y, .w = CANDY_WIDTH_SRC, .h = CANDY_HEIGHT_SRC};
    SDL_Rect dstRect = {.x = 0, .y = 0, .w = CANDY_WIDTH_DST, .h = CANDY_HEIGHT_DST};
    for(int i = 0; i < NUM_CANDIES; i++)
    {
        candies.push_back(new Candy(board, srcRect, dstRect, static_cast<CandyColor>(i), CandyType::NORMAL_CANDY));
        srcRect.x += srcRect.w;
    }
}

void TextureManager::LoadVerticalStripedCandies(SDL_Texture *board, std::vector<Candy*>& verticalStripedCandies)
{

}

void TextureManager::LoadHorizontalStripedCandies(SDL_Texture *board, std::vector<Candy*>& horizontalStripedCandies)
{

}

void TextureManager::LoadBombCandies(SDL_Texture *board, std::vector<Candy*>& bombCandies)
{

}

GameObject* TextureManager::LoadBackground(const char *path)
{
    return nullptr;
}

Candy* TextureManager::LoadWildCandy(SDL_Texture *board)
{
    return nullptr;
}
