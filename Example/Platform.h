#pragma once
#include <SDL.h> // Using SDL
#include <math.h>
#include "AnimeRole.h"
#include "Image.h"
class Platform :public AnimeRole
{
	private:
		double x;
		double y;
		double z;
		double vely;
		double velz;
		double nowposition;

		double target;
		bool moveflag;
		bool switchFlag;
		double* projected2d();
		char path[100];
		Image* image;
		int frame;
		int num;
		SDL_TimerID timerID;
		Uint32 time;
		static Uint32 framechanging(Uint32 interval, void* param);
		static Uint32 changeData(Uint32 interval, void* param);

	public:
		Platform() {};
		Platform(const char* path, int n, SDL_Renderer* renderer);
		Platform(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void setnewimage(const char* path, int n, SDL_Renderer* renderer);
		void setposition(double xx, double yy, double zz);
		void setnowposition(double pos);
		void setvelocity(double velyy,double velzz);
		void settargetposition(double tpos);
		void setmoveflag(bool mflag);
		void setswitchFlag(bool sFlag);
		void setAlpha(int a);
		double gety();
		double getz();
		double gettargetpos();
		bool getswitchFlag();
		int getAlpha();
		void draw(SDL_Renderer* renderer);
		void move();
		void close();
		void startTimer(Uint32 t);
		void stopTimer();
		

};



