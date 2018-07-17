#include <iostream>
#include <SDL.h>

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

int main(int argc, char * argv[]){
	Uint32 next_game_tick = SDL_GetTicks();
	int loops;
	float interpolation;

	bool game_is_running = true;
	while (game_is_running) {

		loops = 0;
		while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
			next_game_tick += SKIP_TICKS;
			loops++;

			std::cout << "Frame" << std::endl;
		}
	}
	return 0;
}