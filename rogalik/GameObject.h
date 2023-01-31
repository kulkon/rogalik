#pragma once
#include "common.h"

class GameObject;

class GameObjectComponent {
public:
	GameObject* parentObject;
};

class GameObject
{
public:
	Vector2 pos;
	GameObject* parent;
	float angle = 0;
	GameObject() {

	}

	virtual void update() = 0;

	void addComponent(GameObjectComponent* component) {
		components.push_back(component);
		component->parentObject = this;
	}

protected:
	std::vector<GameObjectComponent*> components;
	
};

