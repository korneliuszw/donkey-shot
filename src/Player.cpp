//
// Created by wired-mac on 13/01/2024.
//
#include <AnimatedEntity.h>
#include <Player.h>
#include <TextureManager.h>
#include <Collider.h>
#include <StaticEntities.h>

constexpr double JUMP_FORCE = 7.5;
constexpr int JUMP_DURATION = 400;
void Player::switchAnimationType() {
    switch (currentAnimation) {
        case PlayerAnimation::IDLE: {
            animationSheetIndex = 0;
            frameDuration = 200;
            frameCount = 2;
            break;
        }
        case PlayerAnimation::WALK: {
            animationSheetIndex = 12;
            frameDuration = 100;
            frameCount = 4;
            break;
        }
        case PlayerAnimation::JUMP: {
            animationSheetIndex = 24;
            frameDuration = 100;
            frameCount = 8;
            break;
        }
        case PlayerAnimation::JUMP_START: {
            animationSheetIndex = 25;
            frameDuration = 50;
            frameCount = 2;
            break;
        }
        case PlayerAnimation::FALL: {
            animationSheetIndex = 28;
            frameDuration = 100;
            frameCount = 1;
            break;
        }
        case PlayerAnimation::LAND: {
            animationSheetIndex = 29;
            frameDuration = 200;
            frameCount = 2;
            break;
        }
    }
}
Player::Player(TextureManager* textureManager, int x, int y) : AnimatedEntity(textureManager, x, y,
                                                                      PlayerAnimation::IDLE, 192), BoxCollider(this) {
    texture = textureManager->getTexture("sprites/player.png");
    spriteRect = { 0, 0, 24, 24};
    position.height = 1.5;
    position.width = 1.5;
    position.y += position.height;
    fake_width = false;
    switchAnimation(true);
}

void Player::checkCollisions(List<Entity>& colliders) {
    auto head = colliders.getFirst();
    this->onGround = false;
    this->canClimb = false;
    this->collidingWithPlatform = nullptr;
    while (head != nullptr) {
        auto value = head->value;
        if (auto* platformCollider = dynamic_cast<Platform*>(value)) {
            if (this->isColliding(platformCollider)) {
                if (this->position.y - this->position.height >= platformCollider->position.y - platformCollider->position.height)
                    this->onGround = true;
                if (this->position.x > platformCollider->position.x)
                    this->collidingWithPlatform = platformCollider;
            }
        } else if (auto* ladderCollider = dynamic_cast<Ladder*>(value)) {
            if (this->isColliding(ladderCollider)) {
                this->canClimb = true;
            }
        }
        head = head->next;
    }
    if (!this->canClimb) this->onLadder = false;
}
void Player::update(const FrameTimings& timings) {
    flip = direction.x == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    if (isJumping) {
        if (yVelocity == 0) {
            currentAnimation = PlayerAnimation::JUMP_START;
            switchAnimationType();
        } else if (currentAnimation == PlayerAnimation::JUMP_START && yVelocity > 1.25) {
            currentAnimation = PlayerAnimation::JUMP;
            switchAnimationType();
        }
        yVelocity = max(direction.y * (JUMP_FORCE * (timings.timeDelta / 1000.0)), 0);
        jumpTime += timings.timeDelta;
        if (jumpTime >= JUMP_DURATION && direction.y == 1) {
            currentAnimation = PlayerAnimation::FALL;
            switchAnimationType();
            direction.y = -1;
        }
        if (!onGround && collidingWithPlatform && jumpTime < JUMP_DURATION) {
            position.y = collidingWithPlatform->position.y - 0.5;
            yVelocity = -0.5 * (JUMP_FORCE * (timings.timeDelta / 1000.0));
            jumpTime = max(JUMP_DURATION - 200, jumpTime);
        }
        position.y += yVelocity;
    }
    if (direction.y == -1 && isJumping && onGround) {
        isJumping = false;
        currentAnimation = PlayerAnimation::LAND;
        switchAnimationType();
        jumpTime = 0;
    }
    if (!onGround && !onLadder && !(direction.y == 1 && isJumping)) {
        double force = gravity * (timings.timeDelta / 1000.0);
        position.y -= force;
        direction.y = -1;
        currentAnimation = PlayerAnimation::IDLE;
        yVelocity = yVelocity > 0 ? min(0, yVelocity - force) : max(0, yVelocity + force);
        switchAnimationType();
    }
    if (isMoving) {
        position.x += xVelocity * (timings.timeDelta / 1000.0);
        currentAnimation = PlayerAnimation::WALK;
        switchAnimationType();
    } else if (climbing && !(onGround && direction.y == -1)) {
        if (direction.y == -1) printf("On ground %d and climbing down\n", onGround);
        position.y += yVelocity * (timings.timeDelta / 1000.0);
    }
    if (currentAnimation != PlayerAnimation::IDLE) {
        currentAnimation = PlayerAnimation::IDLE;
        switchAnimationType();
    }
    position.x = min(max(position.x, -0.5), SCREEN_WIDTH / BLOCK_WIDTH - 1);
    position.y = min(max(position.y, 1), SCREEN_HEIGHT / BLOCK_HEIGHT - 1);
    updateAnimations(timings.timeDelta);
}
void Player::moveLeft(bool isMovingPressed) {
    isMoving = isMovingPressed;
    if (!isMoving) return;
    xVelocity = -6;
    direction.x = -1;
}
void Player::moveRight(bool isMovingPressed) {
    isMoving = isMovingPressed;
    if (!isMoving) return;
    xVelocity = 6;
    direction.x = 1;
}
void Player::moveUp(bool isMovingPressed) {
    climbing = isMovingPressed && canClimb;
    if (!climbing) return;
    onLadder = true;
    yVelocity = 3.5;
    direction.y = 1;
}
void Player::moveDown(bool isMovingPressed) {
    climbing = isMovingPressed && canClimb;
    if (!climbing) return;
    onLadder = true;
    yVelocity = -3;
    direction.y = -1;
}
void Player::jump() {
    if (isJumping || !onGround) return;
    isJumping = true;
    direction.y = 1;
}