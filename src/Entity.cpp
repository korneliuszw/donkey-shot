#include <SDL.h>
#include <Entity.h>
void Entity::draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = position.x * BLOCK_WIDTH;
    rect.y = SCREEN_HEIGHT - (position.y * BLOCK_HEIGHT);
    rect.w = (fake_width ? 1 : position.width) * BLOCK_WIDTH;
    rect.h = (fake_width ? 1 : position.height) * BLOCK_HEIGHT;
    for (int i = 0; i < (fake_width ? position.width : 1); i++) {
        if (i > 0) rect.x += BLOCK_WIDTH;
        for (int j = 0; j < (fake_width ? position.height : 1); j++) {
            if (j > 0) rect.y += BLOCK_HEIGHT;
            SDL_RenderCopyEx(renderer, texture, &spriteRect, &rect, 0, NULL, flip);
        }
    }
};
