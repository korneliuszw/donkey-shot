#ifndef __GAME_H__
#define __GAME_H__

#include <DataStructures.h>
#include <Entity.h>
#include <Player.h>
#include <Window.h>

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 680;

class Game {
private:
    List<Entity>* entities = nullptr;
    TextureManager* textureManager;
    int currentLevel = 0;
public:
    Player* player;
    explicit Game(TextureManager* textureManager);
    void changeLevel(int newLevel = 1);
    void update(const FrameTimings& timings);
    void render(SDL_Renderer* renderer);
};

class GameWindow : public Window<Game> {
public:
    void update(const FrameTimings &timings) override {
        entity->update(timings);
    }

    void drawOntoWindow(SDL_Renderer *renderer) override;

    void handleEvent(SDL_Event &event) override;

    GameWindow(SDL_Renderer* renderer, TextureManager* textureManager, int x, int y);

    ~GameWindow() override;

};

#endif //__GAME_H__