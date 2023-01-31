#pragma once
#include "common.h"
#include <SDL.h>


const Uint8* gKeyboardState;

class ActionState {
public:
	bool started, stopped, isPerformed;
};


class GeneralBind : public ActionState
{
public:
	
	virtual void updateState() = 0;
protected:
	
	void Started() {
		started = isPerformed = true;
		stopped = false;
	}

	void Stopped() {
		stopped = true;
		started = isPerformed = false;
	}

	void NoChange() {
		started = stopped = false;
	}

};

class KeyBind : public GeneralBind
{
private:
	SDL_Scancode scanCode;
public:
	KeyBind(SDL_Scancode scanCode) {
		this->scanCode = scanCode;
	}

	void updateState() {
		if (gKeyboardState[scanCode]) {
			if (!isPerformed)Started();
			else NoChange();
		}
		else
		{
			if (isPerformed) Stopped();
			else NoChange();
		}
	}
};

class MultiBind : public GeneralBind {
private:
	std::vector<GeneralBind*> subBinds;
public:
	MultiBind() {

	}
	void addSubBind(GeneralBind* subBind) {
		subBinds.push_back(subBind);
	}

	void updateState() {
		for (size_t i = 0; i < subBinds.size(); i++)
		{
			subBinds[i]->updateState();

		}
	}
};

class MouseBind : public GeneralBind
{
private:
	Uint32 mouseButtonMask;
public:
	MouseBind(Uint32 mask) {
		mouseButtonMask = mask;
	}

	void updateState() {
		if (SDL_GetMouseState(NULL, NULL) & mouseButtonMask) {
			if (!isPerformed)Started();
			else NoChange();
		}
		else
		{
			if (isPerformed) Stopped();
			else NoChange();
		}
	}
};

//ACTION_COUNT is not an action, it keeps count of actions in the enumerator
enum Action {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ATTACK1,
	ATTACK2,
	INTERACT,
	ACTION_COUNT
};

class Bindings {
public:
	Bindings() {
		for (size_t i = 0; i < ACTION_COUNT; i++)
		{
			binds[i] = NULL;
		}
		gKeyboardState = SDL_GetKeyboardState(NULL);
	}


	ActionState* getActionState(Action action) {
		return binds[action];
	}
	void update() {
		for (size_t i = 0; i < ACTION_COUNT; i++)
		{
			if(binds[i] != NULL) binds[i]->updateState();
		}
	}

	void addBinding(Action action, GeneralBind* bind) {
		if (binds[action] != NULL) delete binds[action];
		binds[action] = bind;
	}

private:
	GeneralBind* binds[ACTION_COUNT];
};


