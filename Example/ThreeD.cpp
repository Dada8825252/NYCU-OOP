#include "ThreeD.h"
#include <vector>
#include <SDL.h>
#include "Jump.h"
#include "constants.h"
#include <math.h>
#include<iostream>
using namespace std;
#define n 8
ThreeD::ThreeD() {
	for (int i = 0; i < n; i++) {
		p[i].x = 0;
		p[i].y = 0;
		p[i].z = 0;
	}
	angle = 0;
	anglev = 0;
}
ThreeD::ThreeD(double a[n][3]) {
	for (int i = 0; i < n; i++) {
		p[i].x = a[i][0] * 45;
		p[i].y = a[i][1] * 45;
		p[i].z = a[i][2] * 45;
	}
	angle = 0;
	anglev = 10;
}
void ThreeD::draw(SDL_Renderer* renderer)
{
	double rx[n], ry[n];
	for (int i = 0; i < n; i++)
	{
		rx[i] = cos(radian) * p[i].x - sin(radian) * p[i].y;
		ry[i] = sin(radian) * p[i].x + cos(radian) * p[i].y;
	}

	double anglez = M_PI / 4.0;
	double rotate_z[3][3] =
	{
		cos(anglez),-sin(anglez),0,sin(anglez),cos(anglez),0,0,0,1
	};
	double angley = M_PI / 5.0;

	double rotate_y[3][3] =
	{
		cos(angley),0,sin(angley),0,1,0,-sin(angley),0,cos(angley)
	};
	double anglex = 0;
	double rotate_x[3][3] =
	{
		1,0,0,0,cos(anglex),-sin(anglex),0,sin(anglex),cos(anglex)
	};

	double proj[3][n];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			proj[i][j] = rotate_z[i][0] * rx[j] + rotate_z[i][1] * ry[j] + rotate_z[i][2] * p[j].z;
		}

	}// z 

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			proj[i][j] = rotate_y[i][0] * proj[0][j] + rotate_y[i][1] * proj[1][j] + rotate_y[i][2] * proj[2][j];
		}

	}// y

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			proj[i][j] = rotate_x[i][0] * proj[0][j] + rotate_x[i][1] * proj[1][j] + rotate_x[i][2] * proj[2][j];
		}
	}// x

	for (int i = 0; i < n; i++) {
		s[i].x = proj[1][i] + 250;
		s[i].y = -proj[2][i] + 520;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < n - 1; i++) {
		SDL_RenderDrawLine(renderer, s[i].x, s[i].y, s[i + 1].x, s[i + 1].y);
		if (i < n / 2 - 1)
			SDL_RenderDrawLine(renderer, s[i].x, s[i].y, s[i + 5].x, s[i + 5].y);
	}
	SDL_RenderDrawLine(renderer, s[n - 1].x, s[n - 1].y, s[4].x, s[4].y);
	SDL_RenderDrawLine(renderer, s[3].x, s[3].y, s[0].x, s[0].y);
}
Uint32 ThreeD::rotate(Uint32 interval, void* param)
{
	ThreeD* d = (ThreeD*)param;
	if (d->time != 0)
	{
		if (d->angle >= 0)
		{
			d->angle += d->anglev;
			d->angle %= 360;
		}
		else if ((d->angle) + (d->anglev) < 0)
		{
			d->angle += 360 + (d->anglev);
		}
		d->radian = (double)(d->angle) * M_PI / 180.0;
		//cout << d->radian << endl;
		return interval;
	}
	else
		return 0;


}
void ThreeD::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, rotate, this);

}
void ThreeD::stopTimer() {
	time = 0;
}