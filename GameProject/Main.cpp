#include <iostream>
#include <SDL.h>

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void GameLogic() {
	std::cout << "Hammer is a legend" << std::endl;
}

int main(int argc, char * argv[]){

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}


	Uint32 gameTick = SDL_GetTicks();
	int loops;


	bool inGame = true;
	while (inGame) {
		loops = 0;
		while (SDL_GetTicks() > gameTick && loops < MAX_FRAMESKIP) {
			gameTick += SKIP_TICKS;
			loops++;
			GameLogic();
		}
	}
	return 0;
}