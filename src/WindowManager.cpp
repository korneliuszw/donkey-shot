#include <WindowManager.h>
#include <SDL_ttf.h>


void WindowManager::init() {
    bool created = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }
    else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    else if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else if ((window =
                      SDL_CreateWindow("Donkey shot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == 0) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == 0) {
        printf("SDL_renderer could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        screenSurface = SDL_GetWindowSurface(window);
        SET_DEFAULT_COLOR(renderer);
        textureManager = new TextureManager(renderer);
        created = true;
        initWindows();
    }
    if (!created)
        exit(1);
}
void WindowManager::render() {
    SDL_RenderClear(renderer);
    gameWindow->draw(renderer);
    gameInfoWindow->draw(renderer);
    SDL_RenderPresent(renderer);
}

void WindowManager::initWindows() {
    if (gameWindow != nullptr)
        delete gameWindow;
    if (gameInfoWindow != nullptr)
        delete gameInfoWindow;
    gameInfoWindow = new GameInfoWindow(renderer, textureManager, 0, 0);
    gameWindow = new GameWindow(renderer, textureManager, 0, SCREEN_HEIGHT);
}