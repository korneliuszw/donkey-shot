//
// Created by wired-mac on 14/01/2024.
//

#include "Finish.h"

bool Finish::isFinished(Player *player) {
    if (left) {
        return player->position.x < this->x && player->position.y > this->y;
    }
    return player->position.x + player->position.width > this->x && player->position.y > this->y;
}
