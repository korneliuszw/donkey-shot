#include <TextureManager.h>
#include <SDL_image.h>

SDL_Texture* TextureManager::findTexture(char* path) {
    auto head = textures.getFirst();
    while (head != nullptr) {
        const auto val = head->getValue();
        if (safe_string_compare(val->path, path)) {
            return val->texture;
        }
        head = head->next;
    }
    return nullptr;
}
void TextureManager::applyTextureSettings(SDL_Texture* texture, TextureSettings settings) {
    if (settings.blend) {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}
SDL_Texture* TextureManager::loadSurface(char* path, TextureSettings settings) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        exit(1);
    }
    char* pathCopy = (char*)malloc(strlen(path) + 1);
    strcpy(pathCopy, path);
    textures.push(new TextureIdentifier{ pathCopy, texture });
    applyTextureSettings(texture, settings);
    return texture;
}
SDL_Texture* TextureManager::getTexture(char* path, TextureSettings settings) {
    SDL_Texture* texture = findTexture(path);
    if (texture != nullptr)
        return texture;
    return loadSurface(path, settings);
}
