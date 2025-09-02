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

Candy* TextureManager::GetCandy(CandyType candyType, CandyColor candyColor) const
{
    int candyColorIdx = static_cast<int>(candyColor);
    switch(candyType)
    {
        case CandyType::NORMAL_CANDY: {
            return dynamic_cast<Candy*>(candies[candyColorIdx]->Clone());
        }
        case CandyType::HORIZONTAL_STRIPED_CANDY: {
            return dynamic_cast<Candy*>(horizontalStripedCandies[candyColorIdx]->Clone());
        }
        case CandyType::VERTICAL_STRIPED_CANDY: {
            return dynamic_cast<Candy*>(verticalStripedCandies[candyColorIdx]->Clone());
        }
        case CandyType::BOMB_CANDY: {
            return dynamic_cast<Candy*>(bombCandies[candyColorIdx]->Clone());
        }
        case CandyType::WILD_CANDY: {
            return dynamic_cast<Candy*>(wildCandy->Clone());
        }
        case CandyType::NUM_CANDIES:
        default: {
            break;
        }
    }
    return nullptr;
}

GameObject* TextureManager::GetBackground(void) const
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
    
    spritesheet = board;
}

void TextureManager::LoadCandies(SDL_Texture *board, std::vector<Candy*>& candyVector)
{
    SDL_Rect srcRect = {CANDY_OFFSET_X, CANDY_OFFSET_Y, CANDY_WIDTH_SRC, CANDY_HEIGHT_SRC};
    SDL_Rect dstRect = {0, 0, CANDY_WIDTH_DST, CANDY_HEIGHT_DST};
    for(int i = 0; i < NUM_CANDIES; i++)
    {
        candyVector.push_back(new Candy(board, srcRect, dstRect, static_cast<CandyColor>(i), CandyType::NORMAL_CANDY));
        srcRect.x += srcRect.w;
    }
}

void TextureManager::LoadVerticalStripedCandies(SDL_Texture *board, std::vector<Candy*>& stripedCandyVector)
{
    (void) board;
    (void) stripedCandyVector;
}

void TextureManager::LoadHorizontalStripedCandies(SDL_Texture *board, std::vector<Candy*>& stripedCandyVector)
{
    (void) board;
    (void) stripedCandyVector;
}

void TextureManager::LoadBombCandies(SDL_Texture *board, std::vector<Candy*>& bombCandyVector)
{
    (void) board;
    (void) bombCandyVector;
}

GameObject* TextureManager::LoadBackground(const char *path)
{
    (void) path;
    return nullptr;
}

Candy* TextureManager::LoadWildCandy(SDL_Texture *board)
{
    (void) board;
    return nullptr;
}
