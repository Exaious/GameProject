#include <iostream>
#include <SDL.h>

const int TICKS_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

void GameLogic() {
	std::cout << "Hammer is a legend" << std::endl;
}

int main(int argc, char * argv[]){
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