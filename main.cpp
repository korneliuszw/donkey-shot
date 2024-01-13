#include <stdio.h>
#include <WindowManager.h>


int main() {
    printf("Uruchamianie...\n");
    WindowManager* windowManager = new WindowManager();
    windowManager->init();
    bool quit = false;
    SDL_Event e;
    FrameTimings frameTimings;
    frameTimings.worldTime = SDL_GetTicks64();
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_n:
                        windowManager->initWindows();
                        break;
                    default:
                        windowManager->gameWindow->handleEvent(e);
                        break;
                }
            }
        }
        frameTimings.timeDelta = SDL_GetTicks64() - frameTimings.worldTime;
        frameTimings.worldTime += frameTimings.timeDelta;
        windowManager->gameWindow->update(frameTimings);
        windowManager->gameInfoWindow->update(frameTimings);
        windowManager->render();
    }
}


