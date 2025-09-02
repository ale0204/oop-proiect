#ifndef CANDY_CRUSH_H_
#define CANDY_CRUSH_H_

#include "Game.h"
#include "enums/GameState.h"
#include <string>
#include <vector>

class Candy;
enum class CandyColor;

class CandyCrush : public Game {
private:
    std::vector<std::vector<Candy*>> candies;
    Candy *candy1, *candy2;
    GameState gameState;
    int mouseX, mouseY;
    int animationTime;
    bool mouseDown;
    const int BOARD_SIZE_X, BOARD_SIZE_Y;
private:
    void RenderBackground() const noexcept;
    void RenderBoard() const;
    void SwapCandies(Candy *candy1, Candy *candy2);
    bool SwapCandiesContinuously(void);
    bool SwapCandiesState(void);
    void DeleteCandiesState(void);
    bool MarkMatchFound(int x, int y, bool mark = true);
    int CheckColorMatch(int x, int y, CandyColor color);
    Candy* GetCandyFromMouse(void);
    void MarkRowForDeletion(int row) const;
    void MarkColumnForDeletion(int col) const;
    void UpdateAfterDeletionState(void);
    bool MoveCandies(void);
    void FillEmptyPositions(void);
    bool CheckBoardForMatches(void);
    virtual void HandleEvents()  override;
    virtual void Update() override;
    virtual void Render() const override;
    virtual void Afisare(std::ostream& os) const override;
public:
    CandyCrush(const std::string& windowTitle = "Candy Crush", int x = 100, int y = 100, int w = 800, int h = 600, int fps = 60);
    virtual ~CandyCrush() override;
};
#endif /* CANDY_CRUSH_H_ */