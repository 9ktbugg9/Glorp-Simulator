#include "stdafx.h"
#include <ctime>
#include "SDL.h"
#include "Screen.h"
#include "Swarm.h"

//#define SCREEN_WIDTH 4500
//#define SCREEN_HEIGHT 1080

#define WINDOW_NAME "Glorp"
#define SCREEN_WIDTH 980
#define SCREEN_HEIGHT SCREEN_WIDTH / 16 * 9

#define POPULATION 25
#define FPS 60

int main(int argc, char* args[]) {
	srand(time(NULL));

	Screen screen(WINDOW_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawBlendMode(screen.gRenderer, SDL_BLENDMODE_BLEND);

	SDL_Event event;

	Swarm swarm(POPULATION, SCREEN_WIDTH, SCREEN_HEIGHT, screen.gRenderer);

	Uint32 startingTick, fpsTick = SDL_GetTicks();

	int speed = 1;
	bool running = true, pause = false, foodReady = false;

	while (running) {

		startingTick = SDL_GetTicks();

		if (SDL_PollEvent(&event) != NULL) {
			if (event.type == SDL_QUIT)
				running = false;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;

				if (event.key.keysym.sym == SDLK_p) {
					pause = !pause;

					if (pause) {
						string name = WINDOW_NAME;
						name.append("  *PAUSED*");
						SDL_SetWindowTitle(screen.gWindow, name.c_str());
					}

					else
						SDL_SetWindowTitle(screen.gWindow, WINDOW_NAME);

				}
				if (event.key.keysym.sym == SDLK_RIGHTBRACKET)
					speed *= 2;

				if (event.key.keysym.sym == SDLK_LEFTBRACKET) {
					if (speed <= 1)
						speed = 1;
					else
						speed /= 2;
				}
				if (event.key.keysym.sym == SDLK_f)
					foodReady = true;
			}
		}

		SDL_SetRenderDrawColor(screen.gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(screen.gRenderer);


		swarm.update(speed, foodReady);
		swarm.render();

		foodReady = false;

		SDL_RenderPresent(screen.gRenderer);

		if ((1000 / FPS) > SDL_GetTicks() - startingTick) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
		}

	}

	return 0;
}

