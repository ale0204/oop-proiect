#include "../../include/CandyCrush/CandyCrush.h"
#include "../../include/CandyCrush/TextureManager.h"
#include "../../include/CandyCrush/Constants.h"
#include <SDL2/SDL.h>

CandyCrush::CandyCrush(const std::string &windowTitle, int x, int y, int w, int h, int fps)
    : Game(windowTitle, x, y, w, h, fps), BOARD_SIZE_X{::BOARD_SIZE_X}, BOARD_SIZE_Y{::BOARD_SIZE_Y}
{   
    mouseDown = false;
    isSwapping = false;
    shouldSwap = false;
    candy1 = nullptr;
    candy2 = nullptr;
    candies = std::vector<std::vector<Candy*>>(BOARD_SIZE_X, std::vector<Candy*>(BOARD_SIZE_Y));
    for(size_t i = 0; i < candies.size(); i++)
        for(size_t j = 0; j < candies[i].size(); j++)
            candies[i][j] = nullptr;
    
    SDL_Point dstXY = SDL_Point({.x = initX, .y = initY});
    for(size_t i = 0; i < candies.size(); i++)
    {
        dstXY.x = initX;
        for(size_t j = 0; j < candies[i].size(); j++)
        {
            do {
                if(candies[i][j] != nullptr)
                {
                    delete candies[i][j];
                    candies[i][j] = nullptr;
                }
                candies[i][j] = TextureManager::GetInstance()
                                .GetCandy(CandyType::NORMAL_CANDY, Candy::RandomColor());
            } while(MatchFound(i, j) == true);
            candies[i][j]->SetDstRectXY(dstXY);
            candies[i][j]->SetPosition((int) i, (int) j);
            dstXY.x += CANDY_WIDTH_DST;
        }
        dstXY.y += CANDY_HEIGHT_DST;
    }
}

void CandyCrush::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
            case SDL_QUIT: {
                running = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                Candy *candy = GetCandyFromMouse();
                if(candy != nullptr)
                {
                    mouseDown = true;
                    candy1 = candy;
                    candy2 = nullptr;
                    SDL_Point position = candy->GetPosition();
                    printf("Clicked (%d, %d) in (%d, %d)\n", mouseX, mouseY, position.x, position.y);
                }
                break;
            }
            case SDL_MOUSEMOTION: {
                if(mouseDown == false || shouldSwap == true)
                    break;
                Candy *candy = GetCandyFromMouse();
                if(candy != nullptr && candy2 == nullptr && candy != candy1)
                {
                    shouldSwap = true;
                    candy2 = candy;
                    SDL_Point position1 = candy1->GetPosition();
                    SDL_Point position2 = candy2->GetPosition();
                    printf("Moved to (%d, %d) in (%d, %d) from (%d, %d)\n", mouseX, mouseY, position2.x, position2.y, position1.x, position1.y);
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                mouseDown = false;
                break;
            }
            default: {
                // events not handled yet or that don't require handling
                break;
            }
        }
    }
}
void CandyCrush::Update()
{
    if(shouldSwap == true)
    {
        // swap the selected candies to their new position for matchfinding
        SwapCandies(candy1, candy2);

        int numMatches = 0;
        if(MatchFound(candy1->GetPosition().x, candy1->GetPosition().y) == true) {
            numMatches++;
        }
        if(MatchFound(candy2->GetPosition().x, candy2->GetPosition().y) == true) {
            numMatches++;
        }

        // swap back after matchfinding is done
        SwapCandies(candy1, candy2);

        // signal to start swapping animation between candy1 and candy2
        if(numMatches != 0)
        {
            // for now, just plain swap
            SwapCandies(candy1, candy2);
            // isSwapping = true;
        }
        shouldSwap = false;
    }
    if(isSwapping == true)
    {
        // handle swapping animation

        // when swapping animation is done:
        isSwapping = false;
        // shouldDelete = true;
    }
    // if(shouldDelete == true)
    // {

    // }
}

void CandyCrush::Render() const
{
    SDL_RenderClear(renderer);
    RenderBackground();
    RenderBoard();
    SDL_RenderPresent(renderer);
}

void CandyCrush::Afisare(std::ostream &os) const
{
    os << "Candy Crush";
}

void CandyCrush::RenderBackground() const noexcept
{

}

void CandyCrush::RenderBoard() const
{
    for(size_t i = 0; i < candies.size(); i++)
        for(GameObject *candy : candies[i])
            candy->Draw();
}

void CandyCrush::SwapCandies(Candy *candy1, Candy *candy2)
{
    SDL_Point pos1 = candy1->GetPosition();
    SDL_Point pos2 = candy2->GetPosition();
    candies[pos1.x][pos1.y] = candy2;
    candies[pos2.x][pos2.y] = candy1;
    Candy::SwapCandies(candy1, candy2);
}
int CandyCrush::CheckColorMatch(int x, int y, CandyColor color)
{
    return static_cast<int>(candies[x][y]->GetColor() == color || candies[x][y]->GetType() == CandyType::WILD_CANDY);
}

Candy* CandyCrush::GetCandyFromMouse(void)
{
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point *position = Candy::GetPosition(mouseX, mouseY);
    return (position == nullptr) ? nullptr : candies[position->x][position->y];
}

bool CandyCrush::MatchFound(int x, int y)
{
    CandyColor color = candies[x][y]->GetColor();
    // current candy gives 1 point for row and for col
    int rowMatch = 1;
    int colMatch = 1;
    // check left
    if(y == 1) {
        // just one candy to check
        rowMatch += CheckColorMatch(x, y-1, color);
    }
    else if(y > 1) { 
        // at least 2 on left side => check 2 candies
        for(int j = 1; j <= 2; j++)
        {
            rowMatch += CheckColorMatch(x, y-j, color);
            // closest candy not a match, no need to check further
            if(j == 1 && rowMatch == 1)
                break;
        }
    }
    // check right
    if(y == BOARD_SIZE_Y-2 && candies[x][y+1] != nullptr) {
        // just one candy to check
        rowMatch += CheckColorMatch(x, y+1, color);
    }
    else if(y < BOARD_SIZE_Y-2) { 
        // at least 2 on right side => check 2 candies
        for(int j = 1; j <= 2; j++)
        {
            if(candies[x][y+j] == nullptr)
                break;
            int matchFound = CheckColorMatch(x, y+j, color);
            rowMatch += matchFound;
            // closest candy not a match, no need to check further
            if(j == 1 && matchFound == 0)
                break;
        }
    }
    // check up
    if(x == 1) {
        // just one candy to check
        colMatch += CheckColorMatch(x-1, y, color);
    }
    else if(x > 1) { 
        // at least 2 above => check 2 candies
        for(int i = 1; i <= 2; i++)
        {
            colMatch += CheckColorMatch(x-i, y, color);
            // closest candy not a match, no need to check further
            if(i == 1 && colMatch == 1)
                break;
        }
    }
    // check down
    if(x == BOARD_SIZE_X-2 && candies[x+1][y] != nullptr) {
        // just one candy to check
        colMatch += CheckColorMatch(x+1, y, color);
    }
    else if(x < BOARD_SIZE_X-2) { 
        // at least 2 below  => check 2 candies
        for(int i = 1; i <= 2; i++)
        {
            if(candies[x+i][y] == nullptr)
                break;
            int matchFound = CheckColorMatch(x+i, y, color);
            colMatch += matchFound;
            // closest candy not a match, no need to check further
            if(i == 1 && matchFound == 0)
                break;
        }
    }
    return rowMatch >= 3 || colMatch >= 3;
}

CandyCrush::~CandyCrush()   
{
    std::cout << "~CandyCrush()\n";
}