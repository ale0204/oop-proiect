#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_

#include <SDL2/SDL.h>

class GUIManager{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
private:
    static GUIManager *instance;
public:
    static GUIManager& GetInstance();
    void SetWindow(SDL_Window *window);
    void SetRenderer(SDL_Renderer *renderer);
    SDL_Window* GetWindow(void) const;
    SDL_Renderer* GetRenderer(void) const;
};

#endif /* GUI_MANAGER_H_ */