#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <string>

#include "../../include/CandyCrush/exceptions/SDLInitException.h"
#include "../../include/CandyCrush/exceptions/TTFInitException.h"
#include "../../include/CandyCrush/exceptions/IMGInitException.h"

class Game {
protected:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    const int fps;
    const Uint64 frameTime;
public:
    void Play();
    virtual ~Game();
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
protected:
    Game(const std::string& windowTitle, int x, int y, int w, int h, int fps);
    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() const = 0;
    virtual void Afisare(std::ostream& os) const = 0;
};

#endif /* GAME_H_ */