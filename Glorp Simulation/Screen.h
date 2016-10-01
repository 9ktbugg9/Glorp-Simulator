#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

class Screen {
private:
	const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = SCREEN_WIDTH / 16 * 9;
	void close();
	bool init(string, int, int);

public:

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* gTexture = NULL;
	SDL_Surface* gIcon = NULL;
	SDL_Texture* gCurrentTexture = NULL;

	int getWidth() { return SCREEN_WIDTH; }
	int getHeight() { return SCREEN_HEIGHT; }


	Screen(string name, int width, int height) { init(name, width, height); }
	~Screen() { close(); }
};

