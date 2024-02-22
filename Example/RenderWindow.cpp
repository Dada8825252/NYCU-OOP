#include "RenderWindow.h"
#include <stdio.h>
#include "constants.h"
RenderWindow::RenderWindow(const char* caption, int winx, int winy, int width, int height)
{
	// Create window	
	// SDL_WINDOWPOS_UNDEFINED: Used to indicate that you don't care what the window position is.
	window = SDL_CreateWindow(caption, winx, winy, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	// Create renderer	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}
	r = 205;
	g = 228;
	b = 234;
	light = NIGHT;

	printf("SDL system initializes successfully!!!\n");
}

void RenderWindow::close()
{
	// Destroy renderer	
	// Destroy window		
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderClear(renderer);
}

void RenderWindow::clear(Uint32 color)
{
	SDL_SetRenderDrawColor(renderer, color / 0x1000000, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100);
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}
Uint32 RenderWindow::changeLight(Uint32 interval, void* param)
{
	RenderWindow* p = (RenderWindow*)param;
	if (p->light == NIGHT) {
		if (p->r < 5) {
			p->r = 0;
		}
		if (p->r != 0) {
			p->r -= LightChange;  //LightChange:每單位時間改變顏色係數的量
			p->g -= LightChange;
			p->b -= LightChange;
			p->ChangeLight = false;
		}
		if (p->r == 0) { //徹底變成黑夜之後可以開始變白天了
			p->ChangeLight = true;
		}
	}
	else {  //DAY
		if (p->r > 200) {
			p->r = 205;
		}
		if (p->r != 205) {
			p->r += LightChange;
			p->g += LightChange;
			p->b += LightChange;
			p->ChangeLight = false;
		}
		if (p->r == 205) {
			p->ChangeLight = true;
		}
	}

	if (p->r <= 120) {
		p->star = true;
	}
	else {
		p->star = false;
	}

	if (p->time != 0)
		return interval;

	else
		return 0;
}
bool RenderWindow::getChangeLight() {
	return ChangeLight;
}
bool RenderWindow::getStar() {
	return star;
}
void RenderWindow::startTimer(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, changeLight, this);
}
void RenderWindow::setLight(bool l) {
	light = l;
}