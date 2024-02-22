#pragma once
#include <SDL.h> // Using SDL
#include "constants.h"
class RenderWindow
{
	public:
		RenderWindow() {};
		RenderWindow(const char *caption, int winx, int winy, int width, int height);
		void close();
		void clear();
		void clear(Uint32 color);
		void display();
		SDL_Renderer* getRenderer();
		void startTimer(Uint32 t);
		void setLight(bool l);
		bool getChangeLight();
		bool getStar();

	private:
		SDL_Window *window; // The window we'll be rendering to
		SDL_Renderer *renderer; // The renderer contained by the window
		int r;
		int g;
		int b;
		static Uint32 changeLight(Uint32 interval, void* param); // Timer callback 
		SDL_TimerID timerID;
		Uint32 time;
		bool light;
		bool star; //whether the stars need to appear 
		bool ChangeLight; //change light or not 
};

