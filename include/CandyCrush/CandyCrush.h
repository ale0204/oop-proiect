#ifndef CANDY_CRUSH_H_
#define CANDY_CRUSH_H_

#include "Game.h"
#include "Candy.h"
#include <string>
#include <vector>

class CandyCrush : public Game {
private:
    std::vector<GameObject*> candies;
protected:
    void RenderBackground();
    void RenderBoard();
    virtual void HandleEvents()  override;
    virtual void Update() override;
    virtual void Render() override;
public:
    CandyCrush(const std::string& windowTitle = "Candy Crush", int x = 100, int y = 100, int w = 800, int h = 600, int fps = 60);
    virtual ~CandyCrush() override;
};
#endif /* CANDY_CRUSH_H_ */