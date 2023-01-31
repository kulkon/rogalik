#pragma once
#include "common.h"
#include "KeyBinds.h"
#include "GameObject.h"
#include "TestGameObject.h"
#include "Level.h"
class Game
{
public:
	Level* level;

	Game() {
		bindings = Bindings();
		bindings.addBinding(UP, new KeyBind(SDL_SCANCODE_UP));
		bindings.addBinding(DOWN, new KeyBind(SDL_SCANCODE_DOWN));
		bindings.addBinding(LEFT, new KeyBind(SDL_SCANCODE_LEFT));
		bindings.addBinding(RIGHT, new KeyBind(SDL_SCANCODE_RIGHT));

		bindings.addBinding(INTERACT, new MouseBind(1));
		//TestGameObject.game = this;

	}

	void update() {
		bindings.update();
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->update();
		}
	}
	Bindings bindings;
	std::vector<GameObject*> gameObjects;

	void loadLevel() {
		level = new Level(10, 10);
	}
private:
	
};

