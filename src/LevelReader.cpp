//
// Created by wired-mac on 14/01/2024.
//
#include <stdio.h>
#include <unistd.h>
#include <LevelReader.h>
#include <Entity.h>
#include <Player.h>

void signal_reading_error(char* str) {
    fprintf(stderr, "%s\n", str);
    exit(10);
}

Player *LevelReader::createPlayer() {
    int x, y;
    if (fscanf(file, "%d %d\n", &x, &y) < 2)
        signal_reading_error("Failed to loading level! Corrupted plyer information. Correct format is 'Y <X> <Y>'");
    this->player = new Player(textureManager, x, y);
    return this->player;
}

Ladder *LevelReader::createLadder() {
    int x, y, h;
    if (fscanf(file, "%d %d %d\n", &x, &y, &h) < 3)
        signal_reading_error("Failed to loading level! Corrupted ladder information. Correct format is 'L <X> <Y> <H>'");
    return new Ladder(textureManager, x, y, h);
}

Platform *LevelReader::createPlatform() {
    int x, y, w;
    if (fscanf(file, "%d %d %d\n", &x, &y, &w) < 3)
        signal_reading_error("Failed to loading level! Corrupted platform information. Correct format is 'P <X> <Y> <W>'");
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
        case 'F':
            return createFinish();
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
 * F - linia koncowa. ZAWSZE NA KONCU PLIKU
 * @param levelNumber
 * @return
 */
List<Entity>* LevelReader::readLevel(int levelNumber) {
    auto* entities = new List<Entity>();
    char path[256];
    sprintf(path, "levels/%d.level", levelNumber);
    if (access(path, R_OK) == -1 || (file = fopen(path, "r")) == NULL) {
        signal_reading_error("Failed to load level! Can't read or doesn't exist");
    }
    while (Entity* entity = readLine()) {
        entities->push(entity, true);
    }
    return entities;
}

Entity* LevelReader::createFinish() {
    int x, y;
    char c;
    if (fscanf(file, "%d %d %c", &x, &y, &c) < 2  || (c != 'L' && c != 'R') ) {
        signal_reading_error("Failed to load level! Corrupted finish line. Correct format is 'F <x> <y> <L | R>'");
    }
    this->finish = new Finish(x, y, c == 'L');
    return nullptr;
}
