//
// Created by wired-mac on 13/01/2024.
//

#ifndef DONKEYSHOT_INFOWINDOW_H
#define DONKEYSHOT_INFOWINDOW_H

#include <Window.h>
#include <SDL_ttf.h>

class GameInfo {
private:
    int gameTime = 0;
    int score = 0;
    char* implementedRequirements = "1, 2, 3, 4, A";
    int fps = 0;
    int frames = 0;
    int fpsTimer = 0;

public:
    void update(const FrameTimings& timings);
    char* getText();

};

class GameInfoWindow : public Window<GameInfo> {
private:
    TTF_Font *font;
    SDL_Color textColor;
public:
    void update(const FrameTimings &timings) override {
        entity->update(timings);
    }

    void drawOntoWindow(SDL_Renderer *renderer) override;

    void handleEvent(SDL_Event &event) override {}

    GameInfoWindow(SDL_Renderer* renderer, TextureManager* textureManager, int x, int y);

    ~GameInfoWindow() override;
};

#endif //DONKEYSHOT_INFOWINDOW_H
