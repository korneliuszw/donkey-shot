//
// Created by wired-mac on 14/01/2024.
//

#ifndef DONKEYSHOT_LEVELREADER_H
#define DONKEYSHOT_LEVELREADER_H
#include <DataStructures.h>
#include "Finish.h"

class Entity;
class TextureManager;
class Player;
class Ladder;
class Platform;

class LevelReader {
private:
    Player* player;
    Finish* finish = nullptr;
    Ladder* createLadder();
    Player* createPlayer();
    Platform* createPlatform();
    Entity* createFinish();
    Entity* readLine();
    FILE* file = nullptr;
    TextureManager* textureManager;
public:
    List<Entity>* readLevel(int levelNumber = 1);
    Player* getPlayer() {
        return player;
    }
    Finish* getFinish() {
        return finish;
    }
    LevelReader(TextureManager* textureManager) : textureManager{textureManager} {}
    ~LevelReader() {
        fclose(file);
    }
};

#endif //DONKEYSHOT_LEVELREADER_H
