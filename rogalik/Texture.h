#pragma once
#include "commonRender.h"
#include "common.h"
#include "TextureInfo.h"

class Texture
{
public:
	Texture(TextureInfo& textureInfo, SDL_Renderer* sdl_renderer) {
		SDL_Surface* loadedSurface = IMG_Load(textureInfo.path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", textureInfo.path.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, loadedSurface);
			if (sdl_texture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", textureInfo.path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
			ID = textureInfo.ID;
			spriteWidth = textureInfo.spriteWidth;
			spriteHeight = textureInfo.spriteHeight;
			spriteCount = textureInfo.spriteCount;
		}
	}

	SDL_Texture* sdl_texture = NULL;
	unsigned int ID;
	unsigned char spriteWidth, spriteHeight, spriteCount;
	
};

