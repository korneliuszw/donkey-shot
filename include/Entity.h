#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SDL.h>
#include <TextureManager.h>

constexpr int SCREEN_HEIGHT = 555;
constexpr int SCREEN_WIDTH = 640;
constexpr int BLOCK_WIDTH = 32;
constexpr int BLOCK_HEIGHT = 32;
class BlockPosition {
public:
    double x;
    double y;
    double width;
    double height;
    BlockPosition(double x, double y, double width, double height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
};

struct FrameTimings {
    unsigned long worldTime;
    unsigned long timeDelta;
};

class Entity {
protected:
    SDL_Texture* texture;
    TextureManager* textureManager;
    SDL_Rect spriteRect;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool fake_width  = true;
public:
    Entity(TextureManager* textureManager, int x, int y): textureManager(textureManager), position(x, y, 1, 1) {}
    virtual void update(const FrameTimings& timings) {};
    void draw(SDL_Renderer* renderer);

    BlockPosition position;
};

#endif //__ENTITY_H__