#include "../../include/CandyCrush/GUIManager.h"

GUIManager* GUIManager::instance = nullptr;

GUIManager& GUIManager::GetInstance()
{
    if(instance == nullptr)
        instance = new GUIManager();
    return *instance;
}

void GUIManager::SetWindow(SDL_Window *newWindow) { 
    this->window = newWindow;
}

void GUIManager::SetRenderer(SDL_Renderer *newRenderer) { 
    this->renderer = newRenderer;
}

SDL_Window* GUIManager::GetWindow(void) const { 
    return window; 
}

SDL_Renderer* GUIManager::GetRenderer(void) const {
    return renderer;
}
