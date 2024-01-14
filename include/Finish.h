//
// Created by wired-mac on 14/01/2024.
//

#ifndef DONKEYSHOT_FINISH_H
#define DONKEYSHOT_FINISH_H

#include "Player.h"
#include "Kong.h"

class Finish {
private:
    int x, y;
    bool left = false;
public:
    Kong* kong = nullptr;
    Finish(int x, int y, bool left = false) : x{x}, y{y}, left{left} {}
    void createKong(TextureManager* textureManager);
    bool isFinished(Player* player);
    ~Finish() {
        delete kong;
    }
};

#endif //DONKEYSHOT_FINISH_H
