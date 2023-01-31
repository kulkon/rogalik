#pragma once
#include "GameObject.h"
#include "Texture.h"

class Sprite : public GameObjectComponent {
public:
	int textureId;
	int spriteIndex;
	float scale = 1;
	Sprite(int textureID, int i) {
		textureId = textureID;
		spriteIndex = i;
	}
};

