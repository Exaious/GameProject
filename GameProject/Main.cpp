#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "TextureLoading.h"

const int screenX = 1900;
const int screenY = 900;

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
const int boxNumber = ((screenX/2) * 6);

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

struct VectorF {
	float x = 0, y = 0;
};
struct Player {
	SDL_Rect rect = { 200,200,125,125 };
	SDL_Texture * sprite = NULL;
	VectorF vel;
};
struct Fire {
	SDL_Rect rect = { 0,0,125,125 };
	SDL_Texture * sprite = NULL;
	bool visible = false;
};
struct VectorI {
	int x = 0;
	int y = 0;
	int h = 0;
};
struct Controller {
	bool right = false;
	bool left = false;

	bool up = false;
	bool down = false;
};
SDL_Rect background = { 0,0,(2 * screenX),screenY };

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
int Input(SDL_Event * e, Controller * c, Fire * fire) {
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
				fire[3].visible = true;
				return 1;

			case SDLK_RIGHT:
				c->right = true;
				fire[1].visible = true;
				return 1;

			case SDLK_UP:
				c->up = true;
				fire[0].visible = true;
				return 1;

			case SDLK_DOWN:
				c->down = true;
				fire[2].visible = true;
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
				fire[3].visible = false;
				return 2;

			case SDLK_RIGHT:
				c->right = false;
				fire[1].visible = false;
				return 2;

			case SDLK_UP:
				c->up = false;
				fire[0].visible = false;
				return 2;

			case SDLK_DOWN:
				c->down = false;
				fire[2].visible = false;
				return 2;

			default:
				return 0;
			}
		}
	}
	return -2;
}
bool collision(SDL_Rect * rect1, SDL_Rect * rect2) {
	if (rect1->x < rect2->x + rect2->w &&
		rect1->x + rect1->w > rect2->x &&
		rect1->y < rect2->y + rect2->h &&
		rect1->h + rect1->y > rect2->y) {
		return true;
	}
	return false;
}
void pMove(Player * p, Controller * c) {
	p->vel.y += .03f;
	if (p->vel.y > 0) {
		p->rect.y += (int)p->vel.y;
	}
	else {
		p->vel.y += .02f;
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
void fMove(Player * p, Fire * fire) {
	fire[1].rect.x = p->rect.x - fire[1].rect.w;
	fire[1].rect.y = p->rect.y;
	fire[2].rect.x = p->rect.x;
	fire[2].rect.y = p->rect.y - fire[2].rect.h;
	fire[3].rect.x = p->rect.x + p->rect.w;
	fire[3].rect.y = p->rect.y;
	fire[0].rect.y = p->rect.y + p->rect.h;
	fire[0].rect.x = p->rect.x;

}
bool GameLogic(Player * p, Controller * c, int f, Fire * fire) {
	if (f == -1) { return false; }

	pMove(p, c);
	fMove(p, fire);


	return true;
}



int main(int argc, char * argv[]) {
	init();
	
	Player player;
	Controller controls;
	Fire fire[4];
	SDL_Rect boxDim = { 0,0,100,100 };

	VectorI positions[boxNumber];
	int offsetX = 0;
	int o = 0;
	for (int i = 0; i < boxNumber; ++i) {
		positions[i].x += offsetX;
		offsetX += 100;
		o = (rand() % 4);
		positions[i].y = 500 + (o * 100);
		switch (o) {
		case 0:
			positions[i].h = 400;
			break;
		case 1:
			positions[i].h = 300;
			break;
		case 2:
			positions[i].h = 200;
			break;
		case 3:
			positions[i].h = 100;
			break;
		}

	}

	for (int i = 0; i < 4; i++) {
		fire[i].sprite = GenerateTexture("fire", renderer);
	}
	player.sprite = GenerateTexture("shiro", renderer);
	SDL_Texture * box_T = GenerateTexture("box", renderer);
	SDL_Texture * background_T = GenerateTexture("moon", renderer);

	Uint32 gameTicks = SDL_GetTicks();
	int loops;

	SDL_Event e;
	bool inGame = true;
	while (inGame) {
		loops = 0;
		while (SDL_GetTicks() > gameTicks && loops < MAX_FRAMESKIP) {
			gameTicks += SKIP_TICKS;
			loops++;
			int val = Input(&e, &controls, fire);
			inGame = GameLogic(&player, &controls, val, fire);
			if (inGame == false) { break; }

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, background_T, NULL, &background);
			
			for (int i = 0; i < boxNumber; ++i) {
				boxDim.x = positions[i].x;
				boxDim.y = positions[i].y;
				boxDim.h = positions[i].h;
				SDL_RenderCopy(renderer, box_T, NULL, &boxDim);
			}

			SDL_RenderCopy(renderer, player.sprite, NULL, &player.rect);
			for (int i = 0; i < 4; ++i) {
				if (fire[i].visible) {
					SDL_RenderCopy(renderer, fire[i].sprite, NULL, &fire[i].rect);
				}
			}
			SDL_RenderPresent(renderer);
		}
		if (loops > 1) {
			std::cout << "Lag Frames: " << loops - 1 << std::endl;
		}
	}
	return 0;
}