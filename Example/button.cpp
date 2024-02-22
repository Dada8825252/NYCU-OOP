#include "button.h"
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include "Image.h"
#include "constants.h"
#include<iostream>
using namespace std;

//無法完成按下去變暗的特效 問題可能出在setAlpha() 
//把 pressedEffect合併到 ispressed
button::button(const char* path,int n, SDL_Renderer* renderer)
{
	setispressed(false);
	setAlpha(255);
	setpressedEffect(true);
	num = n;
	image = new Image[num];
	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		image[i].set(file, renderer);
	}
	frame = 0;
}
//new
button::button(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	setispressed(false);
	setAlpha(255);
	setpressedEffect(true);
	num = n;
	image = new Image[num];
	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		image[i].set(file, renderer, r, g, b);
	}
	frame = 0;
}
void button::setPosition(double xx, double yy) {
	
	x = xx;
	y = yy;
}
void button::setAlpha(int a)
{
	//image->setAlpha(a);
}
void button::setispressed(bool b)
{
	ispressed = b;
}
void button::setpressedEffect(bool b)
{
	pressedEffect = b;
}
void button::setdwh(int w, int h)
{
	setdw(w);
	setdh(h);
}
int button::getAlpha() {
	return image->getAlpha();
}
bool button::getispressed()
{
	return ispressed;
}
bool button::getpressedEffect()
{
	return pressedEffect;
}
void button::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = getdw();
	d.h = getdh();
	
	image[frame].draw(renderer, d, { ALLREGION });
}

void button::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}
void button::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);

}
void button::stopTimer() {
	time = 0;
}

Uint32 button::changeData(Uint32 interval, void* param)
{
	button* b = (button*)param;
	if (b->ispressed == true) {

		if (b->getAlpha() >= 25) {
			cout << "changing less" << endl;
			b->setAlpha(b->getAlpha() - 25);
		}
		else {
			b->setpressedEffect(false);
		}
			

			
	}
	else {
		b->setAlpha(255);
	}

	if (b->time != 0)
		return interval;

	else
		return 0;
}
