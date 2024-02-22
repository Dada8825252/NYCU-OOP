#include "Energy.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "constants.h"
#include "Image.h"
#include <math.h>

Energy::Energy() {
	pic = true;
	life = 5;
	E = new picture[life];
}

Energy::Energy(int xx, int yy, int ww, int hh) {
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	n = 10;
	power = n;
	pic = false;
}
void Energy::setpath(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	image.set(path, renderer, r, g, b);
	image.setAlpha(255);
	pic = true;

}

Energy::Energy(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	image.set(path, renderer, r, g, b);
	image.setAlpha(255);
	pic = true;
	life = 5;
}

void Energy::setlife(int nn) {
	life = nn;
}


void Energy::setpower(int p) {
	power = p;
}

int Energy::getpower() {
	return power;
}

int Energy::getlife() {
	return life;
}

void Energy::draw(SDL_Renderer* renderer) {
	if (pic) {
		for (int i = 0; i < life; i++)
		{
			if (E[i].shown)
			{
				SDL_Rect d, s;
				d.x = E[i].x;
				d.y = E[i].y;
				d.w = E[i].w;
				d.h = E[i].h;
				image.draw(renderer, d, { ALLREGION });
			}
		}
	}
	else {
		for (int i = 0; i < power; i++)
		{
			SDL_Rect rect;
			rect.x = x;
			rect.y = y - i * (h + 5);
			rect.w = w;
			rect.h = h;
			SDL_SetRenderDrawColor(renderer, 175, 225, 175, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_Rect out;
		out.x = x - 3;
		out.y = y - (n - 1) * (h + 5) - 3;
		out.w = w + 6;
		out.h = (h + 5) * n;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &out);
	}

}