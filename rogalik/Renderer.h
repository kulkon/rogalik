#pragma once
#include "Sprite.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "Level.h"
#include "Game.h"
class Renderer
{
public:
	int frame = 0;
	Camera* camera;


	Renderer(SDL_Window* window) {
		sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x80, 0x80, 0x80);
		srcRect = new SDL_Rect();
		srcRect->x = srcRect->y = 0;
		srcRect->w = srcRect->h = 32;
		destRect = new SDL_Rect();
		destRect->x = destRect->y = 0;
		destRect->w = destRect->h = 32;
		camera = new Camera(1600, 900);
		destFRect = new SDL_FRect();
	}
	~Renderer() {
		SDL_DestroyRenderer(sdl_renderer);
	}



	SDL_Rect* srcRect, * destRect;
	SDL_FRect* destFRect;
	void renderAll() {
		//srcRect->x = 32 * frame;
		SDL_RenderClear(sdl_renderer);
		//SDL_RenderCopy(sdl_renderer, textures[0]->sdl_texture, srcRect, destRect);
		renderSprites();
		SDL_RenderPresent(sdl_renderer);
	}

	
	void renderSprite(Vector2 &pos, Texture* texture, int spriteIndex, float scale, float angle, bool center) {
		if (texture == NULL) texture = textures[2];
		Vector2 v;
		srcRect->x = spriteIndex * texture->spriteWidth;
		srcRect->y = 0;
		camera->worldToScreenSpace(pos, v);



		destFRect->x = v.x;
		destFRect->y = v.y;
		//destFRect->w = texture->spriteWidth * scale * camera->zoom;
		//destFRect->h = texture->spriteHeight * scale * camera->zoom;
		destFRect->w = 1 * scale * camera->zoom;
		destFRect->h = 1 * scale * camera->zoom;
		if (center) {
			destFRect->x -= destFRect->w / 2;
			destFRect->y -= destFRect->h / 2;
		}
		else destFRect->y -= destFRect->h;
		SDL_RenderCopyExF(sdl_renderer, texture->sdl_texture, srcRect, destFRect, angle, NULL, SDL_FLIP_NONE);
	}

	void renderSprites() {
		Vector2 v = Vector2();
		for (int i = 0; i < game->level->levelWidth; i++)
		{
			v.x = i;
			for (int j = 0; j < game->level->levelHeight; j++)
			{
				v.y = j;
				renderSprite(v, game->level->tiles[i][j]->tileset, game->level->tiles[i][j]->spriteIndex, 1.0, 0, false);
			}
		}
		for (size_t i = 0; i < sprites.size(); i++)
		{
			renderSprite(sprites[i]->parentObject->pos, textures[sprites[i]->textureId], sprites[i]->spriteIndex, sprites[i]->scale, sprites[i]->parentObject->angle, true);
		}
	}

	Game* game;
	void renderLevel() {
		//level->tiles
	}

	void loadTextures() {
		TexturesInfo infos = TexturesInfo();
		infos.read();
		for (int i = 0; i < infos.textureInfos.size(); i++)
		{
			textures[infos.textureInfos[i].ID] = new Texture(infos.textureInfos[i], sdl_renderer);
		}
	}
	std::vector<Sprite*> sprites;
	std::map<unsigned int, Texture*> textures;
private:
	
	
	SDL_Renderer* sdl_renderer;
};

