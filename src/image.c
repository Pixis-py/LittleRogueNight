/**
 * @file image.c
 * @author Maelig Pesantez
 * @brief image.c is used to simplify the creation of an SDL texture so it's not obligated to rewrite 15+lines to create one
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../lib/image.h"

/// @brief Function loadTexture is used to create a texture and load it so we don't have to rewrite 15+ lines of code when we have to create one
/// @param imagePath 
/// @param renderer 
/// @return texture
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
