#pragma once
#include "GameObject.h"
#include "KeyBinds.h"
#include "Collisions.h"

class TestGameObject : public GameObject
{
public:
	static Bindings* testb;
	Collider* col;
	TestGameObject(Bindings* b) {
		bindings = b;
		testb = b;
	}
	float speed = 0.1;
	Bindings* bindings;
	Camera* camera;
	Vector2 testV;
	void update() {
		if (bindings->getActionState(UP)->isPerformed) pos.y += 1*speed;
		if (bindings->getActionState(DOWN)->isPerformed) pos.y -= 1*speed;
		if (bindings->getActionState(LEFT)->isPerformed) pos.x -= 1*speed;
		if (bindings->getActionState(RIGHT)->isPerformed) pos.x += 1*speed;
		col->pos.x = pos.x;
		col->pos.y = pos.y;
		Sprite* s = (Sprite*)components[0];
		if (testb->getActionState(INTERACT)->started) s->scale += 1;
		int posX, posY;
		Vector2 v1, v2;
		camera->pos.x = pos.x;
		camera->pos.y = pos.y;
		
		SDL_GetMouseState(&posX, &posY);
		v1.x = posX;
		v1.y = posY;
		testV.x = 1;
		testV.y = 0;
		camera->screenToCameraSpace(v1, v2);
		//std::cout << Vector2::cosBetweenVectors(v2, testV) << std::endl;
		
		
	}
};

Bindings* TestGameObject::testb;