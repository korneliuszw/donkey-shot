#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL.h>
#include <Entity.h>

#define SET_DEFAULT_COLOR(renderer) SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0)

template <typename T>
class Window {
protected:
    int x, y, w, h;
public:
    SDL_Texture *windowTexture;
    T* entity;
    virtual void update(const FrameTimings& timings) = 0;
    virtual void drawOntoWindow(SDL_Renderer* renderer) = 0;
    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderTarget(renderer, windowTexture);
        drawOntoWindow(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_Rect rect = {x, y, w, h};
//        printf("Drawing window at (%d, %d) with size (%d, %d)\n", x, y, w, h);
        SDL_RenderCopy(renderer, windowTexture, nullptr, &rect);
    }
    virtual void handleEvent(SDL_Event& event) {};
    virtual ~Window() = default;
};
#endif