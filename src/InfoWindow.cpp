//
// Created by wired-mac on 13/01/2024.
//

#include <SDL_ttf.h>
#include <InfoWindow.h>

void GameInfo::update(const FrameTimings& timings) {
    gameTime += timings.timeDelta;
    if (fpsTimer > 500) {
        fps = frames * 2;
        fpsTimer -= 500;
        frames = 0;
    }
    fpsTimer += timings.timeDelta;
    frames++;
}
char* GameInfo::getText() {
    char* text = new char[300];
    int secondsTimestamp = gameTime / 1000;
    int hours = secondsTimestamp / 3600;
    int minutes = (secondsTimestamp % 3600) / 60;
    int seconds = secondsTimestamp % 60;
    sprintf(text, "Game time: %02dh:%02dm:%02ds\nFPS: %d\nScore: %d\nImplemented requirements: %s", hours, minutes, seconds, fps, score, implementedRequirements);
    return text;
}
GameInfoWindow::GameInfoWindow(SDL_Renderer* renderer, TextureManager* textureManager, int x, int y) {
    entity = new GameInfo();
    this->x = x;
    this->y = y;
    this->w = SCREEN_WIDTH;
    this->h = 125;
    windowTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, h);
    font = TTF_OpenFont("sprites/Roboto.ttf", 16);
    textColor = {0xFF, 0xFF, 0xFF, 0xFF};
}

GameInfoWindow::~GameInfoWindow() {
    delete entity;
    SDL_DestroyTexture(windowTexture);
    TTF_CloseFont(font);
}

void GameInfoWindow::drawOntoWindow(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0xFA, 0x0);
    SDL_RenderClear(renderer);
    char* text = ((GameInfo*)entity)->getText();
    char* line = strtok(text, "\n");
    SDL_Rect rect = {20, 5, 0, 0};
    while (line != nullptr) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, line, textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        rect.w = textSurface->w;
        rect.h = textSurface->h;
        SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
        rect.y += rect.h + 10;
        line = strtok(nullptr, "\n");
    }
    SET_DEFAULT_COLOR(renderer);
}
