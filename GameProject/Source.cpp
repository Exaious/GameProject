SDL_Rect background = { 0,0,(2 * screenX),screenY };
background.sprite = GenerateTexture("Moon", renderer);
SDL_RenderCopy(renderer, background.sprite, NULL, &background.rect);