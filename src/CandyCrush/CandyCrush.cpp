#include "../../include/CandyCrush/CandyCrush.h"
#include "../../include/CandyCrush/TextureManager.h"
#include "../../include/CandyCrush/Constants.h"
#include <SDL2/SDL.h>

CandyCrush::CandyCrush(const std::string &windowTitle, int x, int y, int w, int h, int fps)
    : Game(windowTitle, x, y, w, h, fps), BOARD_SIZE_X{::BOARD_SIZE_X}, BOARD_SIZE_Y{::BOARD_SIZE_Y}
{   
    gameState = GameState::DEFAULT;
    mouseDown = false;
    candy1 = nullptr;
    candy2 = nullptr;
    animationTime = 200; // ms
    candies = std::vector<std::vector<Candy*>>(BOARD_SIZE_X, std::vector<Candy*>(BOARD_SIZE_Y));
    for(size_t i = 0; i < candies.size(); i++)
        for(size_t j = 0; j < candies[i].size(); j++)
            candies[i][j] = nullptr;
    
    SDL_Point dstXY;
    dstXY.x = initX; dstXY.y = initY;
    for(int i = 0; i < BOARD_SIZE_X; i++)
    {
        dstXY.x = initX;
        for(int j = 0; j < BOARD_SIZE_Y; j++)
        {
            do {
                if(candies[i][j] != nullptr)
                {
                    delete candies[i][j];
                    candies[i][j] = nullptr;
                }
                candies[i][j] = Candy::GenerateRandomCandy();
            } while(MarkMatchFound(i, j, false) == true);
            candies[i][j]->SetDstRectXY(dstXY);
            candies[i][j]->SetPosition(i, j);
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
                }
                break;
            }
            case SDL_MOUSEMOTION: {
                if(mouseDown == false || gameState == GameState::SWAP_CANDIES)
                    break;
                Candy *candy = GetCandyFromMouse();
                if(candy != nullptr && candy2 == nullptr && candy != candy1)
                {
                    gameState = GameState::SWAP_CANDIES;
                    candy2 = candy;
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

bool CandyCrush::SwapCandiesState(void)
{
    // swap the selected candies to their new position for matchfinding
    SwapCandies(candy1, candy2);

    bool match1 = MarkMatchFound(candy1->GetPosition().x, candy1->GetPosition().y);
    bool match2 = MarkMatchFound(candy2->GetPosition().x, candy2->GetPosition().y);
    bool matchFound = match1 || match2;
    // swap back after matchfinding is done
    SwapCandies(candy1, candy2);

    // signal to start swapping animation between candy1 and candy2
    if(match1 == true || match2 == true)
    {
        // for now, just plain swap
        SwapCandies(candy1, candy2);
    }
    return matchFound;
}

void CandyCrush::DeleteCandiesState(void)
{
    for(size_t i = 0; i < candies.size(); i++)
    {
        for(size_t j = 0; j < candies[i].size(); j++)
        {
            if(candies[i][j] == nullptr)
                continue;
            if(candies[i][j]->ShouldDelete() == true)
            {
                delete candies[i][j];
                candies[i][j] = nullptr;
            }
        }
    }
}

void CandyCrush::UpdateAfterDeletionState(void)
{
    // move all candies down, by iterating through all rows from bottom to top
    // for an empty position, find the nearest candy to fill it
    // look for the first not null candy for the swap of positions
    // and fill the empty position with the found candy
    // mark the found candy position null 
    // to continue iterating and filling it as well
    for (int i = BOARD_SIZE_X-1; i >= 0; i--)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if (candies[i][j] == nullptr)
            {
                for (int k = i-1; k >= 0; k--)
                {
                    if (candies[k][j] != nullptr)
                    {
                        candies[i][j] = candies[k][j];
                        candies[i][j]->SetPosition(i, j);
                        candies[i][j]->SetMoving(true);
                        candies[k][j] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    // create new candies on the remaining positions
    // start checking for matches on the updated board
    FillEmptyPositions();
}

void CandyCrush::Update()
{
    switch(gameState)
    {
        case GameState::SWAP_CANDIES: {
            bool matchFound = SwapCandiesState();
            // Mark candies for deletion when a match is found
            gameState = (matchFound == true) ? GameState::DELETE_CANDIES : GameState::DEFAULT;
            break;
        }
        case GameState::DELETE_CANDIES: {
            DeleteCandiesState();
            gameState = GameState::UPDATE_BOARD_AFTER_DELETION;
            break;
        }
        case GameState::UPDATE_BOARD_AFTER_DELETION: {
            UpdateAfterDeletionState();
            gameState = GameState::MOVING_ANIMATION;
            break;
        }
        case GameState::MOVING_ANIMATION: {
            bool stillMoving = MoveCandies();
            if(stillMoving == false)
                gameState = GameState::CHECK_FOR_MATCHES;
            break;
        }
        case GameState::CHECK_FOR_MATCHES: {
            bool matchFound = CheckBoardForMatches();
            gameState = (matchFound == true) ? GameState::DELETE_CANDIES : GameState::DEFAULT;
            break;
        }
        case GameState::DEFAULT: {
            break;
        }
    }
}

void CandyCrush::FillEmptyPositions(void)
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if(candies[i][j] == nullptr)
            {
                candies[i][j] = Candy::GenerateRandomCandy();
                candies[i][j]->SetDstRectXY(SDL_Point{initX + j*CANDY_WIDTH_DST, initY-CANDY_HEIGHT_DST});
                candies[i][j]->SetMoving(true);
                candies[i][j]->SetPosition(i, j);
            }
        }
    }
}

bool CandyCrush::MoveCandies(void)
{
    float dy = 1000*CANDY_HEIGHT_DST/(fps*animationTime);
    bool stillMoving = false;
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            SDL_Point dstPos = {initX + j*CANDY_WIDTH_DST, initY + i*CANDY_HEIGHT_DST};
            if(candies[i][j] == nullptr)
                continue;
            if(candies[i][j]->IsMoving() == false)
                continue;

            stillMoving = true;
            candies[i][j]->MoveY(dy);
            if(candies[i][j]->GetDstRect().y >= dstPos.y)
            {
                candies[i][j]->SetDstRectXY(dstPos);
                candies[i][j]->SetMoving(false);
            }
        }
    }
    return stillMoving;
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
            if(candy != nullptr)
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
    if(candies[x][y] == nullptr)
        return 0;
    return static_cast<int>(candies[x][y]->GetColor() == color || candies[x][y]->GetType() == CandyType::WILD_CANDY);
}

Candy* CandyCrush::GetCandyFromMouse(void)
{
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point *position = Candy::GetPosition(mouseX, mouseY);
    return (position == nullptr) ? nullptr : candies[position->x][position->y];
}

bool CandyCrush::MarkMatchFound(int x, int y, bool mark)
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
    if(mark && rowMatch >= 3)
        MarkRowForDeletion(x);
    if(mark && colMatch >= 3)
        MarkColumnForDeletion(y);
    return rowMatch >= 3 || colMatch >= 3;
}

void CandyCrush::MarkRowForDeletion(int row) const
{
    // suppose the first candy is the one that produced the rowmatch
    size_t startPos = 0;
    int count = 1;
    CandyColor matchColor = candies[row][0]->GetColor();
    for(size_t j = 1; j < candies[row].size(); j++)
    {
        CandyColor currentColor = candies[row][j]->GetColor();
        // same color as matchColor, increase counter
        if(currentColor == matchColor)
            count++;
        // match found before loop finished
        else if(count >= 3)
        {
            for(size_t idx = startPos; idx < startPos + count; idx++)
                candies[row][idx]->MarkForDeletion();
            break;
        }
        else
            count = 1, matchColor = currentColor, startPos = j;
    }
    // match found until the end
    if(count >= 3)
    {
        for(size_t idx = startPos; idx < startPos + count; idx++)
            candies[row][idx]->MarkForDeletion();
    }
}
void CandyCrush::MarkColumnForDeletion(int col) const
{
    // suppose the first candy is the one that produced the colmatch
    size_t startPos = 0;
    int count = 1;
    CandyColor matchColor = candies[0][col]->GetColor();
    for(size_t i = 1; i < candies.size(); i++)
    {
        CandyColor currentColor = candies[i][col]->GetColor();
        // same color as matchColor, increase counter
        if(currentColor == matchColor)
            count++;
        // match found before loop finished
        else if(count >= 3)
        {
            for(size_t idx = startPos; idx < startPos + count; idx++)
                candies[idx][col]->MarkForDeletion();
            break;
        }
        else
            count = 1, matchColor = currentColor, startPos = i;
    }
    // match found until the end
    if(count >= 3)
    {
        for(size_t idx = startPos; idx < startPos + count; idx++)
            candies[idx][col]->MarkForDeletion();
    }
}

bool CandyCrush::CheckBoardForMatches(void)
{
    bool matchFound = false;
    for(int i = 0; i < BOARD_SIZE_X; i++)
    {
        for(int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if(MarkMatchFound(i, j) == true)
                matchFound = true;
        }
    }
    return matchFound;
}

CandyCrush::~CandyCrush()   
{
    std::cout << "~CandyCrush()\n";
}