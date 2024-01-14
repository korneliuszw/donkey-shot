//
// Created by wired-mac on 14/01/2024.
//

#ifndef DONKEYSHOT_FINISH_H
#define DONKEYSHOT_FINISH_H

#include "Player.h"

class Finish {
private:
    int x, y;
    bool left = false;
public:
    Finish(int x, int y, bool left = false) : x{x}, y{y}, left{left} {}
    bool isFinished(Player* player);
};

#endif //DONKEYSHOT_FINISH_H
