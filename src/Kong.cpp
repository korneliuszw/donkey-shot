//
// Created by wired-mac on 14/01/2024.
//

#include "Kong.h"

void Kong::update(const FrameTimings &timings) {
    this->updateAnimations(timings.timeDelta);
}

void Kong::switchAnimationType() {
    frameDuration = 500;
    frameCount = 7;
    animationSheetIndex = 0;
}

Kong::Kong(TextureManager *textureManager, int x, int y)
        : AnimatedEntity(textureManager, x, y, KongAnimation::DEFAULT, 341) {
    texture = textureManager->getTexture("sprites/kong.png");
    fake_width = false;
    spriteRect = {0, 0, KONG_WIDTH, KONG_HEIGHT};
    spriteSpacings = 8;
    flip = SDL_FLIP_HORIZONTAL;
    switchAnimation(true);
}