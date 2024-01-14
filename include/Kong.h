//
// Created by wired-mac on 14/01/2024.
//

#ifndef DONKEYSHOT_KONG_H
#define DONKEYSHOT_KONG_H

#include "AnimatedEntity.h"

constexpr int KONG_WIDTH = 40;
constexpr int KONG_HEIGHT = 32;

enum class KongAnimation {
    DEFAULT
};

class Kong: public AnimatedEntity<KongAnimation> {
public:
    Kong(TextureManager *textureManager, int x, int y);

    void update(const FrameTimings &timings) override;

protected:
    void switchAnimationType() override;
};

#endif //DONKEYSHOT_KONG_H
