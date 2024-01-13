#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <SDL.h>
#include <DataStructures.h>

struct TextureSettings {
    bool blend;
};
class TextureManager {
private:
    class TextureIdentifier {
    public:
        char *path;
        SDL_Texture *texture;
    };
    List<TextureIdentifier> textures;
    SDL_Texture* findTexture(char* path);
    void applyTextureSettings(SDL_Texture* texture, TextureSettings settings);
    SDL_Texture* loadSurface(char* path, TextureSettings settings);
    SDL_Renderer* renderer;
public:
    explicit TextureManager(SDL_Renderer* renderer): renderer(renderer) {}
    SDL_Texture* getTexture(char* path, TextureSettings settings = {false});
};

#endif