#include "AnimeRole.h"
#include "Image.h"
#include <stdio.h>
#include "constants.h"
#include<iostream>
using namespace std;

AnimeRole::AnimeRole(const char* path, int n, SDL_Renderer* renderer)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].set(file, renderer);
	}
	
	frame = 0;
	setdw(image[frame].getWidth());
	setdh(image[frame].getHeight());
	setXspeed(0);
	setover(false);
	setbackgroundEnded(false);
}

AnimeRole::AnimeRole(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
	//	printf("in constructor\n");
		image[i].set(file, renderer, r, g ,b);
	}
	
	frame = 0;

	setdw(image[frame].getWidth());
	setdh(image[frame].getHeight());
	setXspeed(0);
	setover(false);
	setbackgroundEnded(false);
}

void AnimeRole::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}

void AnimeRole::setover(bool b)
{
	over = b;
}

void AnimeRole::setdw(int w)
{
	dw = w;
}

void AnimeRole::setdh(int h)
{
	dh = h;
}

void AnimeRole::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

void AnimeRole::setbackgroundEnded(bool b)
{
	backgroundEnded = b;
}

int AnimeRole::getXspeed()
{
	return xspeed;
}

bool AnimeRole::getover()
{
	return over;
}

int AnimeRole::getdw()
{
	return dw;
}

int AnimeRole::getdh()
{
	return dh;
}

bool AnimeRole::getbackgroundEnded()
{
	return backgroundEnded;
}

int AnimeRole::getWidth()
{
	return image[frame].getWidth();
}

int AnimeRole::getHeight()
{
	return image[frame].getHeight();
}

void AnimeRole::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	//d.w = image[frame].getWidth();
	d.w = dw;
	d.h = dh;
	//d.h = image[frame].getHeight();

	image[frame].draw(renderer, d, { ALLREGION });
}

void AnimeRole::BLMove(void* param) {
	AnimeRole* p = (AnimeRole*) param;
	if(p->ButtomLeftMove == true) {
		if (p->time != 0) {
			(p->x) -= 5;
			(p->y) += 5;
			if ((p->x) == 20 || (p->y) == HEIGHT) {
				(p->ButtomLeftMove) = false;
				
			}
		}
	}
}

Uint32 AnimeRole::changeData(Uint32 interval, void* param)
{
	AnimeRole* p = (AnimeRole*)param;
	//printf("call changeData");

	//moving start background 
	if (p->getXspeed() > 0) {
		if(p->x >= -2700)
			p->x = p->x - p->xspeed;
		else
		{
			//cout << "ended" << endl;
			p->setbackgroundEnded(true);
			//p->x = 0;
		}
		//cout << p->x << endl;
	}
	if (p->emerge == true && p->time != 0) {
		//printf("tr");
		//p->x = (p->x - 5);
		p->y = (p->y - 5);
		if (p->y == 100) {
			p->emerge = false;
		}

	}
	if (p->ButtomLeftMove == true && p->time != 0) {
			//printf("tr");
			p->x = (p->x - 5);
			p->y = (p->y + 5);
			if (p->x == 20 || p->y == (HEIGHT-80)) {
				p->ButtomLeftMove = false;
			}
	}
	//ending scene
	if (p->getover()) {
		p->y = p->y + 5;
	}
	if (p->time != 0)
		return interval;
	
	else
		return 0;
	
	

	/*if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;  // image frame	
		p->x = (p->x - 5 + WIDTH) % WIDTH; // iamge position

		return interval;
	}
	else
	{
		return 0;
	}*/
	

	//return 0;
}

void AnimeRole::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void AnimeRole::stopTimer()
{
	time = 0;	
}


AnimeRole::AnimeRole(const char* path, int n, SDL_Renderer* renderer, bool emg)
{
	num = n;
	image = new Image[num];

	emerge = emg;
	ButtomLeftMove = false;

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].set(file, renderer);
	}

	frame = 0;
}

void AnimeRole::setButtomLeftMove(bool f) {
	ButtomLeftMove = f;

}
void AnimeRole::setflyormove(bool set) {
	flyormove = set;
}
void AnimeRole::setEmerge(bool f) {
	emerge = f;
}
void AnimeRole::setframe(int f) {
	frame = f;
}

void AnimeRole::setXspeed(int xs)
{
	xspeed = xs;
}

/*
void AnimeRole::EmergeMove(bool f) {
	if (f) {

	}
}
*/

bool AnimeRole::getBLMove() {
	return ButtomLeftMove;
}
int AnimeRole::getnum() {
	return num;
}

int AnimeRole::getframe() {
	return frame;
}
bool AnimeRole::getemerge() {
	return emerge;
}
bool AnimeRole::getButtomLeftMove() {
	return ButtomLeftMove;
}
