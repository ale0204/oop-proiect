#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <string>

class Game {
protected:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    const int fps;
    const Uint64 frameTime;
public:
    Game(const std::string& windowTitle, int x, int y, int w, int h, int fps);
    void Play();
protected:
    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~Game();
};

#endif /* GAME_H_ */