#pragma once
#include <SDL.h> // Using SDL
#include "Image.h"

class StaticRole
{
	public:
		StaticRole() {};
		StaticRole(const char* path, SDL_Renderer* renderer);
		StaticRole(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void close();
		void setPosition(int onx, int ony, double xx, double yy, double zz);
		void setPosition(double xx, double yy, double aa);
		void setPosition(int xx, int yy);
		void setspeed(double s);
		void setwangle(double w);
		void setcamD(double d);
		int getWidth();
		int getHeight();
		double getspeed();
		void moveWorlda();
		void moveWorldxy();
		void movefarnear();
		void pseudo3D(SDL_Renderer* renderer, double fnear, double ffar, double halfangle);
	//	void realdrawing(SDL_Renderer* renderer);
		void draw(SDL_Renderer* renderer);	
		void drawscene(SDL_Renderer* renderer);
		void projectedscreen(int camx, int camy, int camz);
		void draw2(SDL_Renderer* renderer);
	private:
		char path[100];		
		Image image;
		double worldx;
		double worldy;
		double worldz;
		double worldangle;
		double screenx;
		double screeny;
		double scale;
		double speed;
		double xspeed;//for start pic move
		double camd;
		double wangle;
		double x;
		double y;

};

;