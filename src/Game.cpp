//
// Created by wired-mac on 13/01/2024.
//
#include <Game.h>
#include <StaticEntities.h>
Game::Game(TextureManager* textureManager) {
player = new Player(textureManager, 1, 1);
entities.push(new Platform(textureManager, 0, 1, 20), true);
entities.push(new Platform(textureManager, 3, 5, 6), true);
entities.push(new Platform(textureManager, 12, 5, 8), true);
entities.push(new Platform(textureManager, 3, 8, 14), true);
entities.push(new Platform(textureManager, 7, 12, 14), true);
entities.push(new Platform(textureManager, 11, 15, 3), true);
entities.push(new Ladder(textureManager, 5, 5, 4), true);
entities.push(new Ladder(textureManager, 12, 5, 4), true);
entities.push(new Ladder(textureManager, 3, 8, 4), true);
entities.push(new Ladder(textureManager, 15, 8, 4), true);
entities.push(new Ladder(textureManager, 9, 12, 4), true);
entities.push(new Ladder(textureManager, 11, 15, 3), true);
entities.push(player, true);
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
GameWindow::GameWindow(SDL_Renderer* renderer, TextureManager* textureManager, int x, int y) : Window<Game>() {
    entity = new Game(textureManager);
    this->x = x;
    this->y = WINDOW_HEIGHT - y;
    this->w = SCREEN_WIDTH;
    this->h = SCREEN_HEIGHT;
    windowTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
}
GameWindow::~GameWindow() {
    delete entity;
    SDL_DestroyTexture(windowTexture);
}
