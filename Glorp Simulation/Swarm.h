#pragma once
#include <vector>
#include <random>
#include "Glorp.h"

class Swarm {
private:
	int POPULATION, SCREEN_WIDTH, SCREEN_HEIGHT, currentFood, foodSize = 10;
	SDL_Renderer *renderer;

	vector <Glorp> swarm;
	vector <int> foodX, foodY;

	bool checkCollision(SDL_Rect, SDL_Rect);

public:

	void update(int, bool);
	void render();

	Swarm(int, int, int, SDL_Renderer *);
	~Swarm() { swarm.clear(); }
};

