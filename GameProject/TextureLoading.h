#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

SDL_Texture * GenerateTexture(std::string path, SDL_Renderer * renderer);