#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "TextureLoading.h"


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
		background.x += (int)p->vel.x;
	}
	else {
		p->vel.x += .05f;
		p->rect.x += (int)p->vel.x;
		background.x += (int)p->vel.x;
	}
	if (c->left) {
		p->vel.x -= .2f;
	}
	else if (c->right) {
		p->vel.x += .2f;
	}
}