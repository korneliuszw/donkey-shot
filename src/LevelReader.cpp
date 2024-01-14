//
// Created by wired-mac on 14/01/2024.
//
#include <stdio.h>
#include <unistd.h>
#include <LevelReader.h>
#include <Entity.h>
#include <Player.h>

Player *LevelReader::createPlayer() {
    int x, y;
    fscanf(file, "%d %d\n", &x, &y);
    this->player = new Player(textureManager, x, y);
    return this->player;
}

Ladder *LevelReader::createLadder() {
    int x, y, h;
    fscanf(file, "%d %d %d\n", &x, &y, &h);
    return new Ladder(textureManager, x, y, h);
}

Platform *LevelReader::createPlatform() {
    int x, y, w;
    fscanf(file, "%d %d %d\n", &x, &y, &w);
    return new Platform(textureManager, x, y, w);
}

Entity *LevelReader::readLine() {
    char type;
    if (fscanf(file, "%c", &type) == EOF)
        return nullptr;
    switch (type) {
        case 'Y':
            return createPlayer();
        case 'P':
            return createPlatform();
        case 'L':
            return createLadder();
        default:
            return nullptr;
    }
}

/**
 * Poziomy trzymane sa w folderze levels, w pliku o nazwie {levelNumber}.level, znajdujacym sie tam gdzie plik wykonywalny
 * Kazda linijka opisuje typ obiektu oraz argumenty do jego konstukturoa
 * Obecne typy
 * Y - gracz
 * P - platform
 * L - drabinka
 * @param levelNumber
 * @return
 */
List<Entity>* LevelReader::readLevel(int levelNumber) {
    auto* entities = new List<Entity>();
    char path[256];
    sprintf(path, "levels/%d.level", levelNumber);
    if (access(path, R_OK) == -1 || (file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Level %d failed to load!!", levelNumber);
        exit(10);
    }
    while (Entity* entity = readLine()) {
        entities->push(entity, true);
    }
    return entities;
}
