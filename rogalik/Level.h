#pragma once
#include "common.h"
#include "Tile.h"
class Level
{
public:
	Tile*** tiles;
	int levelWidth, levelHeight;
	Level(int w, int h) {
		levelWidth = w;
		levelHeight = h;
		tiles = (Tile***)malloc(sizeof(Tile**) * levelWidth);
		for (int i = 0; i < levelWidth; i++)
		{
			tiles[i] = (Tile**)malloc(sizeof(Tile*) * levelHeight);
			for (size_t j = 0; j < levelHeight; j++)
			{



				tiles[i][j] = new Tile(NULL, 0);
			}
		}

	}
};
