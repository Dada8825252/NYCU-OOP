#pragma once
#include<vector>
#include <SDL.h>
#include "Jump.h"
#include "constants.h"
#include <math.h>
using namespace std;
class ThreeD
{
private:
	struct point {
		double x; // world
		double y; // world
		double z; // world
	};
	point p[8];
	int angle; // world
	int anglev; // spinning velocity
	double radian;

	struct screen {
		int x;
		int y;
	};
	screen s[8];

	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 rotate(Uint32 interval, void* param);

public:
	ThreeD();
	ThreeD(double a[8][3]);
	void draw(SDL_Renderer* renderer);
	void startTimer(Uint32 t);
	void stopTimer();

};
