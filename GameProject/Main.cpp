#include <SDL.h>
#include <iostream>

#include "TextureLoading.h"

const int screenX = 1920;
const int screenY = 1200;

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

struct Vector {
	float x = 0, y = 0;
};
struct Player {
	SDL_Rect rect = { 200,200,170,170 };
	SDL_Texture * sprite = NULL;
	Vector vel;
};
struct Controller {
	bool right = false;
	bool left = false;

	bool up = false;
	bool down = false;
};

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, screenX, screenY, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

int Input(SDL_Event * e, Controller * c) {
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			return -1;
		}
		//User presses a key
		else if (e->type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e->key.keysym.sym)
			{
			case SDLK_LEFT:
				c->left = true;
				return 1;

			case SDLK_RIGHT:
				c->right = true;
				return 1;

			case SDLK_UP:
				c->up = true;
				return 1;

			case SDLK_DOWN:
				c->down = true;
				return 1;

			default:
				return 0;
			}
		}
		else if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym)
			{
			case SDLK_LEFT:
				c->left = false;
				return 2;

			case SDLK_RIGHT:
				c->right = false;
				return 2;

			case SDLK_UP:
				c->up = false;
				return 2;

			case SDLK_DOWN:
				c->down = false;
				return 2;

			default:
				return 0;
			}
		}
	}
	return -2;
}

void pMove(Player * p, Controller * c) {
	if (p->vel.y > 0) {
		p->vel.y -= .05f;
		p->rect.y += (int)p->vel.y;
	}
	else {
		p->vel.y += .05f;
		p->rect.y += (int)p->vel.y;
	}
	if (c->up) {
		p->vel.y -= .2f;
	}
	else if (c->down) {
		p->vel.y += .2f;
	}
	if (p->vel.x > 0) {
		p->vel.x -= .05f;
		p->rect.x += (int)p->vel.x;
	}
	else {
		p->vel.x += .05f;
		p->rect.x += (int)p->vel.x;
	}
	if (c->left) {
		p->vel.x -= .2f;
	}
	else if (c->right) {
		p->vel.x += .2f;
	}
}

bool GameLogic(Player * p, Controller * c, int f) {
	if (f == -1) {return false;}

	pMove(p, c);

	return true;
}

int main(int argc, char * argv[]) {
	init();

	Player player;
	Controller controls;
	player.sprite = GenerateTexture("shiro", renderer);

	Uint32 gameTicks = SDL_GetTicks();
	int loops;

	SDL_Event e;
	bool inGame = true;
	while (inGame) {
		loops = 0;
		while (SDL_GetTicks() > gameTicks && loops < MAX_FRAMESKIP) {
			gameTicks += SKIP_TICKS;
			loops++;
			int val = Input(&e, &controls);
			inGame = GameLogic(&player, &controls, val);
			if (inGame == false) { break; }

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, player.sprite, NULL, &player.rect);
			SDL_RenderPresent(renderer);
		}
		if (loops > 1) {
			std::cout << "Lag Frames: " << loops - 1 << std::endl;
		}
	}
	return 0;
}