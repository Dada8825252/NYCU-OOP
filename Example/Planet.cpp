#include "Planet.h"
#include "Image.h"
#include "constants.h"
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <iostream>
using namespace std;

Planet::Planet() {
	num = 1;
	setAlpha(255);
	vely = 10;
	velz = 10;
}
Planet::Planet(const char* path, int n, SDL_Renderer* renderer, int dww, int dhh, int startYY, int startZZ, int endYY)
{
	num = n;
	image = new Image[num];
	setAlpha(255);
	vely = 10;
	velz = 10;
	dw = dww;
	dh = dhh;
	startY = startYY;
	startZ = startZZ;
	endY = endYY;
	setposition(0, startYY, startZZ);

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		cout << "in constructor\n";
		image[i].set(file, renderer);
	}
	cout << "in constructor\n";
	frame = 0;
}
Planet::Planet(const char* path, int n, SDL_Renderer* renderer, int dww, int dhh, int xx, int yy)  //for star only
{
	num = n;
	image = new Image[num];
	setAlpha(255);
	vely = 10;
	velz = 10;
	dw = dww;
	dh = dhh;
	x = xx;
	y = yy;
	//setposition(0, startYY, startZZ);

	int r = rand() % 100;
	if (r < 90) {
		bling = true;
	}
	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		cout << "in constructor\n";
		image[i].set(file, renderer);
	}
	cout << "in constructor\n";
	frame = 0;
}
void Planet::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}
void Planet::setposition(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}
void Planet::setVelz(double velzz) {
	velz = velzz;
}
void Planet::setVely(double velyy) {
	vely = velyy;
}

void Planet::setAlpha(int a)
{
	image->setAlpha(a);
}

double Planet::gety() {
	return y;
}
double Planet::getz() {
	return z;
}
int Planet::getAlpha() {
	return image->getAlpha();
}
double* Planet::projected2d() {
	double angle = M_PI / 4.0;
	double rotate_z[3][3] =
	{
		cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1
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

	double* proj;
	proj = new double[3];

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_z[i][0] * x + rotate_z[i][1] * y + rotate_z[i][2] * z;
	}// z 

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_y[i][0] * proj[0] + rotate_y[i][1] * proj[1] + rotate_y[i][2] * proj[2];
	}// y

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_x[i][0] * proj[0] + rotate_x[i][1] * proj[1] + rotate_x[i][2] * proj[2];
	}// x

	return proj;
}
void Planet::draw(SDL_Renderer* renderer) {

	double rx = projected2d()[1];
	double ry = projected2d()[2];
	short int xx = (short int)rx + 100;
	short int yy = (short int)-ry + 300;
	//	filledCircleRGBA(renderer, xx, yy, 10, 0x0A, 0xBA, 0xB5, 0xFF);
	//stick image
	SDL_Rect d, s;
	d.x = (int)xx;
	d.y = (int)yy;
	d.w = dw;
	d.h = dh;

	image[frame].draw(renderer, d, { ALLREGION });
	//	cout << "in draw\n";
	//	cout << proj[0] << " " << proj[1] << " " << proj[2] << endl;

}
void Planet::drawStar(SDL_Renderer* renderer, bool star) {
	
	if (star) {
		if (bling) {
				if (getAlpha() < 150) {
					setAlpha(getAlpha() + 30);
				}
				else {
					setAlpha(150);
				}
			}
		
		else {
			if (getAlpha() > 0) {
				setAlpha(getAlpha() - 30);
			}
			else {
				setAlpha(0);
			}
		}
	}
	else {
		setAlpha(0);
	}
	
	
	//setAlpha(150);

	SDL_Rect d, s;
	d.x = (int)x;
	d.y = (int)y;
	d.w = dw;
	d.h = dh;

	image[frame].draw(renderer, d, { ALLREGION });
}
Uint32 Planet::changeData(Uint32 interval, void* param)
{
	Planet* p = (Planet*)param;
	//更改星球座標和透明度
	if (p->move) {
		if (p->y >= ((p->startY + p->endY) / 2)) { //屬於右半邊，上升
			p->y -= 2;
			p->z += 2;
			if (p->getAlpha() < 255) {
				p->setAlpha(25 + p->getAlpha());
				if (p->getAlpha() == 250)
					p->setAlpha(255);
			}

		}
		else if ((p->y <= ((p->startY + p->endY) / 2)) && (p->y >= p->endY)) { //屬於左半邊，下降
			p->y -= 2;
			p->z += 1;
		}
	}


	if (p->time != 0) {
		//printf("change data");
		return interval;
	}
	else {

		return 0; //touch the edge then stop timer(return time=0
	}

}
Uint32 Planet::twinkle(Uint32 interval, void* param) {
	Planet* p = (Planet*)param;
	int r = rand() % 100;
	if (r < 30) {
		p->bling = true;
	}
	else {
		p->bling = false;
	}
	
	if (p->time != 0) {
		return interval;
	}
	else {

		return 0; //touch the edge then stop timer(return time=0
	}
}
void Planet::startTimerStar(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, twinkle, this);
}
void Planet::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);

}
void Planet::stopTimer() {
	time = 0;
}

void Planet::setMove(bool m) {
	move = m;
}
bool Planet::getMove() {
	return move;
}