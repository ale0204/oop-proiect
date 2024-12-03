#ifndef CANDY_CRUSH_H_
#define CANDY_CRUSH_H_

#include "Game.h"
#include <string>
#include <vector>

class Candy;
enum class CandyColor;

class CandyCrush : public Game {
private:
    std::vector<std::vector<Candy*>> candies;
    Candy *candy1, *candy2;
    int mouseX, mouseY;
    bool mouseDown;
    bool isSwapping;
    bool shouldSwap;
    const int BOARD_SIZE_X, BOARD_SIZE_Y;
private:
    void RenderBackground() const noexcept;
    void RenderBoard() const;
    void SwapCandies(Candy *candy1, Candy *candy2);
    bool MatchFound(int x, int y);
    int CheckColorMatch(int x, int y, CandyColor color);
    Candy* GetCandyFromMouse(void);
    virtual void HandleEvents()  override;
    virtual void Update() override;
    virtual void Render() const override;
    virtual void Afisare(std::ostream& os) const override;
public:
    CandyCrush(const std::string& windowTitle = "Candy Crush", int x = 100, int y = 100, int w = 800, int h = 600, int fps = 60);
    virtual ~CandyCrush() override;
};
#endif /* CANDY_CRUSH_H_ */