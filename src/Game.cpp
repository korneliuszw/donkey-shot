//
// Created by wired-mac on 13/01/2024.
//
#include <Game.h>
#include <StaticEntities.h>
#include "LevelReader.h"

Game::Game(TextureManager *textureManager) : textureManager{textureManager} {
    this->changeLevel(1);
}

void Game::changeLevel(int newLevel) {
    if (newLevel == currentLevel) return;
    LevelReader reader(textureManager);
    if (entities) {
        auto head = entities->getFirst();
        while (head != nullptr) {
            delete head->value;
            head = head->next;
        }
        delete entities;
    }
    entities = reader.readLevel(newLevel);
    player = reader.getPlayer();
    currentLevel = newLevel;
}

void Game::update(const FrameTimings &timings) {
    player->checkCollisions(*entities);
    player->update(timings);
}

void Game::render(SDL_Renderer *renderer) {
    auto head = entities->getFirst();
    while (head != nullptr) {
        head->getValue()->draw(renderer);
        head = head->next;
    }
}

void GameWindow::drawOntoWindow(SDL_Renderer *renderer) {
    SDL_SetRenderTarget(renderer, windowTexture);
    SET_DEFAULT_COLOR(renderer);
    SDL_RenderClear(renderer);
    entity->render(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_Rect rect = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, windowTexture, nullptr, &rect);
}

GameWindow::GameWindow(SDL_Renderer *renderer, TextureManager *textureManager, int x, int y) : Window<Game>() {
    entity = new Game(textureManager);
    this->x = x;
    this->y = WINDOW_HEIGHT - y;
    this->w = SCREEN_WIDTH;
    this->h = SCREEN_HEIGHT;
    windowTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH,
                                      SCREEN_HEIGHT);
}

GameWindow::~GameWindow() {
    delete entity;
    SDL_DestroyTexture(windowTexture);
}

void GameWindow::handleEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
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
            case SDLK_1:
                entity->changeLevel(1);
                break;
            case SDLK_2:
                entity->changeLevel(2);
                break;
            case SDLK_3:
                entity->changeLevel(3);
                break;
            default:
                break;

        }
    }
}