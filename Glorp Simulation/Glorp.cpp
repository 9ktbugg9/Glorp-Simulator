#include "stdafx.h"
#include "Glorp.h"
#include <iostream>

int Glorp::mWidth = 0;
int Glorp::mHeight = 0;

void Glorp::update() {

	mHunger -= map(mSize, 10, 60, 0.1, 0.04);

	if (mHunger <= 0)
		dying = true;
	if (instrDuration <= 0) {
		nextInstr();
	}
	double xSpeed = mVel * cos(mDir * PI / 180);
	double ySpeed = mVel * sin(mDir * PI / 180);

	mX += xSpeed;
	mY += ySpeed;

	pos.x = mX;
	pos.y = mY;

	if (mY < 0 - mSize)
		mY = mHeight;
	else if (mY > mHeight)
		mY = 0 - mSize;
	if (mX < 0 - mSize)
		mX = mWidth;
	else if (mX > mWidth)
		mX = 0 - mSize;

	instrDuration--;
}

void Glorp::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, mRed, mGreen, mBlue, map(mHunger, 0, 100, 0, 255));
	SDL_RenderFillRect(renderer, &pos);
}

void Glorp::initAll(int width, int height) {
	mWidth = width;
	mHeight = height;
	initDNA();
	mX = pos.x = rand() % mWidth;
	mY = pos.y = rand() % mHeight;
	mSize = rand() % (60 - 10 + 1) + 10;
	mVel = map(mSize, 1, 60, 2.5, .5);
	pos.w = mSize;
	pos.h = mSize;
	string::size_type sz;
	for (int i = 1, x = 0; i < 4; i++, x += 3) {
		string sConv;
		int iConv;
		sConv += DNA[2 + x];
		sConv += DNA[3 + x];
		sConv += DNA[4 + x];
		iConv = stoi(sConv, &sz);
		if (i == 1)
			mRed = iConv;
		if (i == 2)
			mGreen = iConv;
		if (i == 3)
			mBlue = iConv;
	}
	instrAmmount = (DNA.length() - 11) / 7;
}

void Glorp::initDNA() {
	DNA = "";
	int size = rand() % 99 + 1;
	if (size > 9)
		DNA += to_string(size);
	else
		DNA += to_string(0) += to_string(size);

	for (int i = 0; i < 3; i++) {
		int color = rand() % 256;
		if (color > 9)
			if (color > 99)
				DNA += to_string(color);
			else
				DNA += to_string(0) += to_string(color);
		else
			DNA += to_string(0) += to_string(0) += to_string(color);

	}
	int maxInstructions = rand() % 4 + 1;
	for (int i = 0; i < maxInstructions; i++) {
		DNA += "|";

		int cDir = rand() % 360 + 1;
		if (cDir > 9)
			if (cDir > 99)
				DNA += to_string(cDir);
			else
				DNA += to_string(0) += to_string(cDir);
		else
			DNA += to_string(0) += to_string(0) += to_string(cDir);

		DNA += "(";

		int cDur = rand() % 300 + 1;
		if (cDur > 9)
			if (cDur > 99)
				DNA += to_string(cDur);
			else
				DNA += to_string(0) += to_string(cDur);
		else
			DNA += to_string(0) += to_string(0) += to_string(cDur);
	}
}
//
//Glorp Glorp::mutate() {
//
//}
//
//Glorp Glorp::split() {
//
//}
//

void Glorp::nextInstr() {
	if (currentInstr <= instrAmmount) {
		if (currentInstr == instrAmmount)
			currentInstr = 0;
		currentInstr++;
	}
	string sDir = "";
	for (int i = 0; i < 3; i++) {
		sDir += DNA[12 + i + (8 * (currentInstr - 1))];
	}
	string::size_type sz;
	mDir = stoi(sDir, &sz);

	string instrTime = "";
	for (int i = 0; i < 3; i++) {
		instrTime += DNA[16 + i + (8 * (currentInstr - 1))];
	}
	instrDuration = stoi(instrTime, &sz);
	mDir = static_cast<int>(map(mDir, 0, 360, -180, 180));
}

double Glorp::map(double value, double istart, double istop, double ostart, double ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}