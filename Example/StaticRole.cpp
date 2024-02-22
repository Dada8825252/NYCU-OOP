#include <stdio.h>
#include<iostream>
#include <math.h>
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include "StaticRole.h"
#include "Image.h"
#include "constants.h"
using namespace std;
StaticRole::StaticRole(const char* path, SDL_Renderer* renderer)
{
	image.set(path, renderer);
	image.setAlpha(255);
}

StaticRole::StaticRole(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	image.set(path, renderer, r, g, b);
}

void StaticRole::close()
{
	image.close();
}
void StaticRole::setPosition(int onx, int ony, double xx, double yy, double zz)
{
	x = onx;
	y = ony;
	worldx = xx;
	worldy = yy;
	worldz = zz;
}
void StaticRole::setPosition(double xx, double yy, double aa)
{
	worldx = xx;
	worldy = yy;
	worldangle = aa;
}
void StaticRole::setspeed(double s) {
	speed = s;
}
void StaticRole::setwangle(double w) {
	wangle = w * (double)M_PI / 180;
}
void StaticRole::setcamD(double d) {
	camd = d;
}
int StaticRole::getWidth()
{
	return image.getWidth();
}

int StaticRole::getHeight()
{
	return image.getHeight();
}
double StaticRole::getspeed() {
	return speed;
}
void StaticRole::moveWorlda() {
	worldangle += wangle;
}
void StaticRole::moveWorldxy() {
	worldx += cos(worldangle) * speed;
	worldy += sin(worldangle) * speed;
}
void StaticRole::movefarnear() {
	worldz -= speed; // near: speed- far: speed+
}
void StaticRole::pseudo3D(SDL_Renderer* renderer, double fnear, double ffar, double halfangle)
{
	double fnearx1, fneary1, fnearx2, fneary2;
	double ffarx1, ffary1, ffarx2, ffary2;
	fnearx1 = worldx + cos(worldangle - halfangle) * fnear;
	fneary1 = worldy - sin(worldangle - halfangle) * fnear;

	fnearx2 = worldx + cos(worldangle + halfangle) * fnear;
	fneary2 = worldy - sin(worldangle + halfangle) * fnear;

	ffarx1 = worldx + cos(worldangle - halfangle) * ffar;
	ffary1 = worldy - sin(worldangle - halfangle) * ffar;

	ffarx2 = worldx + cos(worldangle + halfangle) * ffar;
	ffary2 = worldy - sin(worldangle + halfangle) * ffar;

	for (int y = 0; y < HEIGHT/2 ; y++)
	{
		double sampledepth = (double)y / ((double)HEIGHT / 2.0);
		double startx = (ffarx1 - fnearx1) * (1.0-sampledepth) + fnearx1;
		double starty = (ffary1 - fneary1) * (1.0-sampledepth) + fneary1;
		double endx = (ffarx2 - fnearx2) * (1.0-sampledepth) + fnearx2;
		double endy = (ffary2 - fneary2) * (1.0-sampledepth) + fneary2;

	/*	for (int x = 0; x < WIDTH; x++)
		{
			double samplewidth = (double)x / ((double)WIDTH);
			samplex = (endx - startx) * samplewidth + startx;
			sampley = (endy - starty) * samplewidth + starty;

		}*/
	//	samplex = startx;
	//	sampley = starty;
	//	samplew = endx - startx;
	/*	SDL_Rect d, s;
		s.x = samplex / WIDTH * 3580;
		s.y = sampley / HEIGHT * 2480;
		s.w = samplew / WIDTH * 3580;
		s.h = 1;
		d.x = 0;
		d.y = HEIGHT / 2 + y;
		d.w = WIDTH;
		d.h = 1;
		image.draw(renderer, d, s);*/
	//	cout << startx << " " << starty << " " << samplew << endl;
	}
//	realdrawing(renderer);
}
/*void StaticRole::realdrawing(SDL_Renderer* renderer) {
	for (int x = 0; x < 1024; x += 32) {
		for (int y = 0; y < 1024; y++) {
			SDL_SetRenderDrawColor(renderer, 0, 105, 148, 255);
			SDL_RenderDrawLine(renderer, x, y, x, y + 1);
			SDL_RenderDrawLine(renderer, y, x, y, x + 1);
		}
	}
}*/
void StaticRole::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = 0;
	d.y = 0;
	d.w = WIDTH;
	d.h = HEIGHT;
	image.draw(renderer, d, {ALLREGION});
}
void StaticRole::drawscene(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	projectedscreen(+1.5, -3, 0); // view position
	d.x = screenx;
	d.y = screeny;
	d.w = 200 * scale+100;
	d.h = 100 * scale+50;
	image.draw(renderer, d, { ALLREGION });
}
void StaticRole::projectedscreen(int camx, int camy, int camz)
{
	double rotate_z[3][3] =
	{
		cos(wangle),-sin(wangle),0,sin(wangle),cos(wangle),0,0,0,1
	};
	double* proj;
	proj = new double[3];

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_z[i][0] * worldx + rotate_z[i][1] * worldy + rotate_z[i][2] * worldz;
	}// z
	scale = (double)camd / (worldz - camz);
	screenx = (scale * (worldx - camx)) * 200 / 2 + x;
	screeny = -(scale * (worldy - camy)) * 100 / 2 + y;
//	cout << scale << " " << screenx << " " << screeny << endl;
}
void StaticRole::draw2(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = 30;
	d.h = 30;
	//d.w = image.getWidth();
	//d.h = image.getHeight();
	//d.w = WIDTH;
	//d.h = HEIGHT;
	//	printf("in draw static\n");
	image.draw(renderer, d, { ALLREGION });
}
void StaticRole::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}