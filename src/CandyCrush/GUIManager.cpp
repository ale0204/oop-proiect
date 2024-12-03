#include "../../include/CandyCrush/GUIManager.h"

GUIManager* GUIManager::instance = nullptr;

GUIManager& GUIManager::GetInstance()
{
    if(instance == nullptr)
        instance = new GUIManager();
    return *instance;
}

void GUIManager::SetWindow(SDL_Window *window) { 
    this->window = window;
}

void GUIManager::SetRenderer(SDL_Renderer *renderer) { 
    this->renderer = renderer;
}

SDL_Window* GUIManager::GetWindow(void) const { 
    return window; 
}

SDL_Renderer* GUIManager::GetRenderer(void) const {
    return renderer;
}
