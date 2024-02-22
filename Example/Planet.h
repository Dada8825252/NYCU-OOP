#pragma once
#include "AnimeRole.h"
class Planet :
	public AnimeRole
{
private:
	double x;
	double y;
	double z;
	double vely;
	double velz;
	int startY;  //起始位置
	int startZ;
	int endY;  //下山位置 (z座標的開始與結束相同
	int dw;  //呈現在window上的大小
	int dh;
	bool move; //是否開始動
	bool bling;//whether the stars twinkle
	double* projected2d();
	char path[100];
	Image* image;
	int frame;
	int num;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);
	static Uint32 twinkle(Uint32 interval, void* param);

public:
	Planet();
	Planet(const char* path, int n, SDL_Renderer* renderer, int dww, int dhh, int startYY, int startZZ, int endYY);
	Planet(const char* path, int n, SDL_Renderer* renderer, int dww, int dhh, int xx, int yy);
	void setVelz(double velzz);
	void setVely(double velyy);
	void setAlpha(int a);
	double gety();
	double getz();
	int getAlpha();
	void draw(SDL_Renderer* renderer);//for the sun and moon
	void drawStar(SDL_Renderer* renderer, bool star); //for stars
	void close();
	void startTimer(Uint32 t);
	void startTimerStar(Uint32 t);
	void stopTimer();
	void setposition(double xx, double yy, double zz);
	void setMove(bool m);
	bool getMove();

};

