#include "TextureLoading.h"
SDL_Texture * GenerateTexture(std::string path, SDL_Renderer * renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load((path + ".png").c_str());
	if (loadedSurface == NULL) { std::cout << "Error" << std::endl; }
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture = NULL) { std::cout << "Error" << std::endl; }
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}