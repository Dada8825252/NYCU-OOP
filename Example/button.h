#pragma once
#include "AnimeRole.h"
class button : public AnimeRole
{
public:
	button() {};
	button(const char* path,int n, SDL_Renderer* renderer);
	button(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void setPosition(double xx, double yy);
	void setAlpha(int a);
	void setispressed(bool b);
	void setpressedEffect(bool b);
	void setdwh(int w, int h);
	int getAlpha();
	void close();
	bool getispressed();
	bool getpressedEffect();
	void draw(SDL_Renderer* renderer);
	void startTimer(Uint32 t);
	void stopTimer();
private :
	char path[100];
	Image* image;
	int frame;
	int num;
	double x;
	double y;
	double z;
	bool ispressed;
	bool pressedEffect;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);
};

