//
// Created by wired-mac on 13/01/2024.
//

#ifndef DONKEYSHOT_COLLIDER_H
#define DONKEYSHOT_COLLIDER_H

#include "Entity.h"
class BoxCollider;
//class CircleCollider;
//class AngledCollider;

class Collider {
private:
    Entity* entity;
public:
//    virtual void isColliding(CircleCollider* collider) = 0;
    virtual void isColliding(BoxCollider* collider) = 0;
//    virtual void isColliding(AngledCollider* collider) = 0;
};

class BoxCollider {
private:
    Entity* entity;
public:
    bool isColliding(BoxCollider* collider) {
        auto ALeft = entity->position.x;
        auto ARight = entity->position.x + entity->position.width;
        auto ATop = entity->position.y;
        auto ABottom = entity->position.y - entity->position.height;
        auto BLeft = collider->entity->position.x;
        auto BRight = collider->entity->position.x + collider->entity->position.width;
        auto BTop = collider->entity->position.y;
        auto BBottom = collider->entity->position.y - collider->entity->position.height;
        return ALeft <= BRight && ARight >= BLeft && ATop >= BBottom && ABottom <= BTop;
    }
    explicit BoxCollider(Entity* entity): entity(entity) {}
};


#endif //DONKEYSHOT_COLLIDER_H
