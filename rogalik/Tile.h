#pragma once
#include "Texture.h"
class Tile
{
public:
	Texture* tileset;
	int spriteIndex;
	Tile(Texture* tileset, int spriteIndex) : tileset(tileset), spriteIndex(spriteIndex) {

	}
private:

};

