#include <SDL.h>
#include <iostream>

#include "TextureLoading.h"

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;


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
			SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
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

void GameLogic() {

}

int main(int argc, char * argv[]) {
	init();
	SDL_Texture * texture = GenerateTexture("monkaS", renderer);
	Uint32 gameTicks = SDL_GetTicks();
	int loops;

	bool inGame = true;
	while (inGame) {
		loops = 0;
		while (SDL_GetTicks() > gameTicks && loops < MAX_FRAMESKIP) {
			gameTicks += SKIP_TICKS;
			loops++;
			GameLogic();

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
		if (loops > 1) {
			std::cout << "Lag Frames: " << loops - 1 << std::endl;
		}
	}
	return 0;
}