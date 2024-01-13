#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <AnimatedEntity.h>
#include "Collider.h"
#include "StaticEntities.h"

enum class PlayerAnimation {
    IDLE,
    WALK,
    JUMP_START,
    JUMP,
    FALL,
    LAND
};

struct Vector {
    double x;
    double y;
};

class Player: public AnimatedEntity<PlayerAnimation>, BoxCollider {
private:
    bool onGround = true;
    bool onLadder = false;
    bool climbing = false;
    bool canClimb = false;
    bool isJumping = false;
    int jumpTime = 0;
    Platform* collidingWithPlatform = nullptr;
    bool isMoving = false;
    Vector direction = {1, 0};
    // physics variables are in blocks per second
    double xVelocity = 0;
    double yVelocity = 0;
    double gravity = 11;
protected:
    void switchAnimationType() override;
public:
    Player(TextureManager* textureManager, int x, int y);
    void checkCollisions(List<Entity>& colliders);
    void update(const FrameTimings& timings) override;
    void moveLeft(bool isMovingPressed);
    void moveRight(bool isMovingPressed);
    void moveUp(bool isMovingPressed);
    void moveDown(bool isMovingPressed);
    void jump();
};

#endif //__PLAYER_H__