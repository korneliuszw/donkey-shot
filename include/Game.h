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
    List<Entity> entities;
public:
    Player* player;
    explicit Game(TextureManager* textureManager);
    void update(const FrameTimings& timings) {
        player->checkCollisions(entities);
        player->update(timings);
    }
    void render(SDL_Renderer* renderer) {
        auto head = entities.getFirst();
        while (head != nullptr) {
            head->getValue()->draw(renderer);
            head = head->next;
        }
    }
};

class GameWindow : public Window<Game> {
public:
    void update(const FrameTimings &timings) override {
        entity->update(timings);
    }

    void drawOntoWindow(SDL_Renderer *renderer) override;

    void handleEvent(SDL_Event &event) override {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
//                case SDLK_UP:
//                    entity->player->moveUp();
//                    break;
//                case SDLK_DOWN:
//                    entity->player->moveDown();
//                    break;
                case SDLK_LEFT:
                    entity->player->moveLeft(event.type == SDL_KEYDOWN);
                    break;
                case SDLK_RIGHT:
                    entity->player->moveRight(event.type == SDL_KEYDOWN);
                    break;
                case SDLK_UP:
                    entity->player->moveUp(event.type == SDL_KEYDOWN);
                    break;
                case SDLK_DOWN:
                    entity->player->moveDown(event.type == SDL_KEYDOWN);
                    break;
                case SDLK_SPACE:
                    entity->player->jump();
                    break;
                default:
                    break;
            }
        }
    }
    GameWindow(SDL_Renderer* renderer, TextureManager* textureManager, int x, int y);

    ~GameWindow() override;

};

#endif //__GAME_H__