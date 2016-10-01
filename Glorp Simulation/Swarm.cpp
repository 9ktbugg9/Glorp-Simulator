#include "stdafx.h"
#include "Swarm.h"


void Swarm::update(int speed, bool food) {
	if (food) {
		currentFood++;
		foodX.push_back(rand() % (SCREEN_WIDTH - foodSize) + foodSize);
		foodY.push_back(rand() % (SCREEN_HEIGHT - foodSize) + foodSize);
	}
	for (int i = 0; i < POPULATION; i++)
		if (swarm[i].isDying()) {
			swarm.erase(swarm.begin() + i);
			POPULATION--;
		}
	for (int i = 0; i < POPULATION; i++)
		for (int k = 0; k < speed; k++)
			swarm[i].update();
	
	for (int i = 0; i < POPULATION; i++) 
		for (int f = 0; f < currentFood; f++) {
			SDL_Rect tempFood = {foodX[f], foodY[f], foodSize, foodSize};
			if (checkCollision(swarm[i].getPos(), tempFood)) {
				swarm[i].feed();
				foodX.erase(foodX.begin() + f);
				foodY.erase(foodY.begin() + f);
				currentFood--;
			}
		}


}

void Swarm::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < currentFood; i++) {
		SDL_Rect pos = {foodX[i], foodY[i], foodSize, foodSize};
		SDL_RenderFillRect(renderer, &pos);
	}

	for (int i = 0; i < POPULATION; i++)
		swarm[i].render(renderer);
}

Swarm::Swarm(int pop, int w, int h, SDL_Renderer *rend) : POPULATION(pop), SCREEN_WIDTH(w), SCREEN_HEIGHT(h), renderer(rend), currentFood(0) {
	for (int i = 0; i < POPULATION; i++) {
		Glorp x(w, h);
		swarm.push_back(x);
		swarm[i].initDem(w, h);
	}

}

bool Swarm::checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
		//If any of the sides from A are outside of B
		if (bottomA <= topB) {
			return false;
		}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}