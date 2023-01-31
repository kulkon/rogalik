/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"
#include "Renderer.h"
#include "Game.h"
//Screen dimension constants
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

int main(int argc, char* args[]);

//Loads individual image as texture

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
Renderer* renderer;

//Current displayed texture
SDL_Texture* gTexture = NULL;

Sprite* gSprite = NULL;




int fpsCap;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = new Renderer(gWindow);
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}

	return success;
}



bool loadMedia()
{
	//Loading success flag
	bool success = true;

	renderer->loadTextures();
	
	
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window	
	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	delete renderer;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

Game* gGame;
#include "Collisions.h"
Collisions* cols;
int testCounter = 0;
void update() {
	testCounter++;
	if (testCounter == fpsCap) {
		//std::cout << "update " << SDL_GetTicks();
		renderer->frame++;
		if (renderer->frame > 3) renderer->frame = 0;
		testCounter = 0;
	}
	gGame->update();
	cols->checkForCollisions();
}


void render() {
	renderer->renderAll();
}

bool loop() {
	bool quit = false;
	
	Uint32 prevTime = 0;
	double counter = 0;
	SDL_Event e;
	int deltaTime = SDL_GetTicks() - prevTime;
	prevTime = SDL_GetTicks();
	counter += deltaTime;
	
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			std::cout << std::endl << "quit using x" << std::endl;
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				std::cout << std::endl << "quit using escape" << std::endl;
				quit = true;
				break;
			case SDLK_KP_PLUS:
				renderer->camera->zoom *= 2;
				std::cout << "plus";
				break;
			case SDLK_KP_MINUS:
				renderer->frame--;
				renderer->camera->zoom /= 2;
				std::cout << "minus";
				break;
			default:
				break;
			}
		}
		else
		{
			//std::cout << SDL_GetMouseState(NULL, NULL) << std::endl;
		}
	}
	update();
	render();
	
	counter -= 1000.0 / (double)fpsCap;
	SDL_Delay(500/fpsCap);
	return quit;
}



#include "TestGameObject.h"


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			cols = new Collisions();

			gGame = new Game();
			TestGameObject* tgo = new TestGameObject(&gGame->bindings);
			tgo->camera = renderer->camera;
			gGame->gameObjects.push_back(tgo);
			Sprite* s = new Sprite(0, 0);
			gGame->gameObjects[0]->addComponent(s);
			
			renderer->sprites.push_back(s);
			gGame->loadLevel();
			renderer->game = gGame;
			tgo->col = *cols->dynamicColliders.begin();

			//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			//ShapeIntersections::getIntersectionPoints();
			fpsCap = 120;
			double frameTime = 1000.0 / fpsCap;
			Uint32 prevTime = 0, currentTime;
			int timeDiff;
			double counter = 0;
			while (true) {
				currentTime = SDL_GetTicks();
				timeDiff = currentTime - prevTime;
				counter += timeDiff;
				prevTime = currentTime;
				if (counter > frameTime) {
					
					bool quit = loop();
					if (quit) break;
					counter -= frameTime;
				}
				
			}

			

		}
	}
	


	//Free resources and close SDL
	close();

	return 0;
}