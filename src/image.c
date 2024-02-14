#include "../lib/image.h"

SDL_Texture* loadTexture(const char* imagePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "Erreur 1 lors de la création de la texture : %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}
