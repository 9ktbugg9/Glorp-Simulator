#pragma once
#include <string>
#include <random>
#include "SDL.h"
using namespace std;

#define PI 3.14159265

class Glorp {
private:
	string DNA;	//-size 2-red 3-green 3-blue 3-path +11~ -
	int mSize, mFullness, instrAmmount = 0, currentInstr = 0, instrDuration = 0, mDir;
	static int mWidth, mHeight;
	double mVel, mX, mY, mHunger = 100;
	int mRed, mGreen, mBlue;
	bool dying = false;
	SDL_Rect pos;

	void initAll(int, int);
	void initDNA();
	void nextInstr();

	double map(double, double, double, double, double);

	Glorp mutate();

public:
	Glorp split();

	string getDNA() { return DNA; }
	void initDem(int w, int h) { initAll(w, h); }
	int getRed() { return mRed; }
	int getGreen() { return mGreen; }
	int getBlue() { return mBlue; }
	int isDying() { return dying; }
	void update();
	void render(SDL_Renderer *);
	SDL_Rect &getPos() { return pos; }

	void feed() { if (mHunger += 25 > 100) mHunger = 100; }

	Glorp() {}
	Glorp(int w, int h) { initAll(w, h); }
	~Glorp() {}
};

