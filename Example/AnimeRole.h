#pragma once
#include <SDL.h> // Using SDL
#include "Image.h"

class AnimeRole
{
	private:
		char path[100];
		int num;  
		Image* image;
		int frame;
		int x;
		int y;
		int dw;
		int dh;
		SDL_TimerID timerID;
		Uint32 time;
		bool ButtomLeftMove; //to determine whether to move the role after the penguin jumped
		bool emerge;
		bool over;
		bool backgroundEnded;
		int xspeed;
	protected:
		static Uint32 changeData(Uint32 interval, void* param); // Timer callback 
		int getWidth();
		int getHeight();
		int getframe();
		int getnum();
		
		bool getemerge();
		bool getButtomLeftMove();
		bool getBLMove();
		bool flyormove = true; //true:move false:false
	public:
		AnimeRole(){};
		AnimeRole(const char* path, int n, SDL_Renderer* renderer);
		AnimeRole(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void close();
		void setover(bool b);
		void setdw(int w);
		void setdh(int h);
		void setframe(int f);
		void setXspeed(int xs);
		void setPosition(int xx, int yy);
		void setbackgroundEnded(bool b);
		int getXspeed();
		bool getover();
		int getdw();
		int getdh();
		bool getbackgroundEnded();
		void draw(SDL_Renderer* renderer);
		void startTimer(Uint32 t);
		void stopTimer();
		AnimeRole(const char* path, int n, SDL_Renderer* renderer, bool emg);
		void setButtomLeftMove(bool f);
		void setflyormove(bool set);
		void setEmerge(bool f);
		void BLMove(void* param);

};

