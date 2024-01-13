#ifndef __STATIC_ENTITIES_H__
#define __STATIC_ENTITIES_H__
#include <Entity.h>
#include <Collider.h>

class Ladder: public Entity, public BoxCollider {
public:
    Ladder(TextureManager* textureManager, int x, int y, int h) : Entity(textureManager, x, y), BoxCollider(this) {
        texture = textureManager->getTexture("sprites/ladder.png", {true});
        position.height = h;
        spriteRect = { 0, 0, 32, 32};
    }
};
class Platform : public Entity, public BoxCollider {
public:
    Platform(TextureManager* textureManager, int x, int y, int width) : Entity(textureManager, x, y), BoxCollider(this) {
        texture = textureManager->getTexture("sprites/platform.png");
        position.width = width;
        spriteRect = { 0, 0, 32, 32};
    }
};

#endif //__STATIC_ENTITIES_H__