#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <SDL.h>
#include <Game.h>
#include <SDL_image.h>
#include "InfoWindow.h"

class WindowManager {
private:
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Renderer* renderer = nullptr;
public:
    GameWindow* gameWindow = nullptr;
    GameInfoWindow* gameInfoWindow = nullptr;
    TextureManager* textureManager;
    void init();
    void render();
    void initWindows();
    ~WindowManager() {
        delete textureManager;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif //__WINDOW_MANAGER_H__