#pragma once
#include <SDL.h> // Using SDL
#include "Image2.h"
class RotatingCoin  
{
public:
	RotatingCoin() {};
	RotatingCoin(const char* path, SDL_Renderer* ren);
	RotatingCoin(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	RotatingCoin(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(double xx, double yy, double zz);
	void setAlpha(int a);
	void setShow(bool s);
	int getWidth();
	int getHeight();
	int getAlpha();
	bool getShow();
	void draw();
	void startTimer(Uint32 t);
	void stopTimer();
	double* projected2d();

private:
	SDL_Renderer* renderer;
	int num;
	int wn; // New in this example, image number in width
	int hn; // New in this example, image number in height
	Image2 image;  
	int frame;
	bool show;
	double x;
	double y;
	double z;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param); // Timer callback 
};

