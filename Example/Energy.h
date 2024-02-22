#pragma once
#include <SDL.h>
#include "constants.h"
#include <math.h>
#include "StaticRole.h"
#include "Image.h"
class Energy : public StaticRole
{
private:
	int x;
	int y;
	int w;
	int h;
	int n;
	int life;
	int power;
	bool shown;
	bool pic;
	char path[100];
	Image image;

public:
	Energy();
	Energy(int xx, int yy, int ww, int hh);
	struct picture {
		int x;
		int y;
		int w;
		int h;
		bool shown;
		void setposition(int xx, int yy) { x = xx; y = yy; };
		void setdwh(int ww, int hh) { w = ww; h = hh; };
		void setshown(bool s) { shown = s; };
	};
	picture* E;
	void setpath(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	Energy(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void setlife(int nn);
	void draw(SDL_Renderer* renderer);
	void setpower(int p);
	int getpower();
	int getlife();


};