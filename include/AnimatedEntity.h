#ifndef __ANIMATED_ENTITY_H__
#define __ANIMATED_ENTITY_H__
#include <Entity.h>

template <class Animation>
class AnimatedEntity: public Entity {
private:
    int currentFrameTime = 0;
    int frameNumber = 0;
    int textureWidth = 0;
protected:
    int animationSheetIndex = 0;
    int currentSheetIndex = 0;
    int frameDuration = 0;
    int frameCount = 0;
    Animation currentAnimation;
    virtual void switchAnimationType() = 0;
    void switchAnimation(bool changeAnimationType = false) {
        if (changeAnimationType) {
            switchAnimationType();
            currentSheetIndex = 0;
        }
        currentSheetIndex = frameNumber + animationSheetIndex;
        spriteRect.x = (currentSheetIndex * spriteRect.w) % textureWidth;
        spriteRect.y = (currentSheetIndex * spriteRect.w) / textureWidth * spriteRect.h;
    }

    void updateAnimations(unsigned long timeDelta) {
        if (frameDuration == 0)
            return;
        currentFrameTime += timeDelta;
        if (currentFrameTime >= frameDuration) {
            frameNumber = (frameNumber + 1) % frameCount;
            switchAnimation();
            currentFrameTime = 0;
        }
    }
    AnimatedEntity(TextureManager *textureManager, int x, int y, Animation currentAnimation, int textureWidth)
            : Entity(textureManager, x, y), currentAnimation(currentAnimation), textureWidth(textureWidth) {}

};

#endif //__ANIMATED_ENTITY_H__