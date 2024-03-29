/**
 * @file image.h
 * @author Maelig Pesantez
 * @brief image.h is used to simplify the creation of an SDL texture so it's not obligated to rewrite 15+lines to create one
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef IMAGE_H
#define IMAGE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/// @brief Function loadTexture is used to create a texture and load it so we don't have to rewrite 15+ lines of code when we have to create one
/// @param imagePath 
/// @param renderer 
/// @return texture
SDL_Texture* loadTexture(const char* , SDL_Renderer* );

#endif

