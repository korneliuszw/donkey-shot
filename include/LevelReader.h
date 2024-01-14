//
// Created by wired-mac on 14/01/2024.
//

#ifndef DONKEYSHOT_LEVELREADER_H
#define DONKEYSHOT_LEVELREADER_H
#include <DataStructures.h>

class Entity;
class TextureManager;
class Player;
class Ladder;
class Platform;

class LevelReader {
private:
    Player* player;
    Ladder* createLadder();
    Player* createPlayer();
    Platform* createPlatform();
    Entity* readLine();
    FILE* file = nullptr;
    TextureManager* textureManager;
public:
    List<Entity>* readLevel(int levelNumber = 1);
    Player* getPlayer() {
        return player;
    }
    LevelReader(TextureManager* textureManager) : textureManager{textureManager} {}
    ~LevelReader() {
        fclose(file);
    }
};

#endif //DONKEYSHOT_LEVELREADER_H
