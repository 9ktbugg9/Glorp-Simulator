#include "stdafx.h"
#include "Screen.h"

bool Screen::init(string name, int width, int height) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "-Initialization Failed- Reason: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "-Window Creation Failed- Reason: " << SDL_GetError() << endl;
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				cout << "-Renderer Creation Failed- Reason: " << SDL_GetError() << endl;
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
			}
		}
	}

	IMG_Init(IMG_INIT_PNG);

	gIcon = IMG_Load("images/icon.png");
	SDL_SetWindowIcon(gWindow, gIcon);
	return success;
}

void Screen::close() {

	SDL_FreeSurface(gIcon);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL; gRenderer = NULL;

	SDL_Quit();
}