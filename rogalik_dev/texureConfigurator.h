#pragma once
#include "../rogalik/TextureInfo.h"

void createTextureConfigFile() {
	TexturesInfo t = TexturesInfo();
	t.addInfo(0, "textures/testSheet.png", 32, 32, 4);
	t.addInfo(1, "textures/floor.png", 32, 32, 1);
	t.addInfo(2, "textures/default.png", 32, 32, 1);
	t.write();
	t.read();
}