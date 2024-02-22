#pragma once
#include <SDL.h> // Using SDL
#include <math.h>
#include "AnimeRole.h"
#include "Image.h"
#include "Mixer.h"

class Jump :public AnimeRole
{
	private:
		double x;
		double y;
		double z;
		double velwind; // x-axis
		double vely;
		double velz;
		double flyx;
		double az;
		double nowposition;
		double distance;
		double angle;
		int points;
		double target;
		
		char path[100];
		Image* image;
		int frame;
		int num;
		bool fall;
		SDL_TimerID timerID;
		Uint32 time;
		static Uint32 framechanging(Uint32 interval, void* param);
		static Uint32 changeData(Uint32 interval, void* param);
		static Uint32 jumping(Uint32 interval, void* param);
		double vlift; // lift velocity 
		bool jumpflag;
		bool overflag;

	public:
		Jump();
		Jump(const char* path, int n, SDL_Renderer* renderer);
		Jump(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void setnewimage(const char* path, int n, SDL_Renderer* renderer, bool once);
		void setnewimage(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, bool once);
		void setdistance(double d);
		void setposition(double xx, double yy, double zz, double theta);
		void setnowposition(double pos);
		void setvelocity(double velxx, double azz);
		void setvelocity(double velyy, double velzz, double azz);
		void setwindvelocity(double vwind);
		void setflyback(double flyxx);
		void setpoints(int p);
		void settargetposition(double tpos);
		void setAlpha(int a);
		void setvelz(double vz);
		void setx(double xx);
		void sety(double yy);
		void setz(double zz);
		double getx();
		double gety();
		double getz();
		double getvely();
		double getvelz();
		double getaz();
		double getvelwind();
		double getflyx();
		double getdistance();
		int getpoints();
		double getnowposition();
		double gettarget();
		int getAlpha();
		void draw(SDL_Renderer* renderer);
		void move();
		void close();
		void startTimer(Uint32 t);
		void stopTimer();

		void lift();
		void setvlift(double vl);
		void setjumpflag(bool f);
		bool getjumpflag();
		void setoverflag(bool ol);
		bool getoverflag();
		void setfallflag(bool f);
		bool getfallflag();

		double* projected2d();
};



