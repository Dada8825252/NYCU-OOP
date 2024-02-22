#include "RotatingCoin.h"
#include "Image2.h"
#include <stdio.h>
#include "constants.h"
#include <stdlib.h>

RotatingCoin::RotatingCoin(const char* path, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.generateTexture();

	renderer = ren;
	num = 1;
	frame = 0;
	hn = 1;
	wn = 1;
}

// call this function in main.cpp
RotatingCoin::RotatingCoin(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.generateTexture();
	
	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
	show = false;
	int r;
	r = rand() % 100;
	printf("random probability: %d", r);
	if (r < 50) {	
		show = true;
	}
	
}

// Renew in this example
RotatingCoin::RotatingCoin(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey({ r, g, b, 255 });
	image.generateTexture();

	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
}

// Renew in this example
void RotatingCoin::close()
{
	// Free loaded image	
	image.close();

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}

void RotatingCoin::setPosition(double xx, double yy,double zz)
{
	x = xx;
	y = yy;
	z = zz;
}

// Renew in this example
int RotatingCoin::getWidth()
{
	return image.getWidth() / wn;
}

// Renew in this example
int RotatingCoin::getHeight()
{
	return image.getHeight() / hn;
}

double* RotatingCoin::projected2d() {
	double angle = M_PI / 4.0;
	double rotate_z[3][3] =
	{
		cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1
	};
	double angley = M_PI / 5.0;

	double rotate_y[3][3] =
	{
		cos(angley),0,sin(angley),0,1,0,-sin(angley),0,cos(angley)
	};
	double anglex = 0;
	double rotate_x[3][3] =
	{
		1,0,0,0,cos(anglex),-sin(anglex),0,sin(anglex),cos(anglex)
	};

	double* proj;
	proj = new double[3];

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_z[i][0] * x + rotate_z[i][1] * y + rotate_z[i][2] * z;
	}// z 

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_y[i][0] * proj[0] + rotate_y[i][1] * proj[1] + rotate_y[i][2] * proj[2];
	}// y

	for (int i = 0; i < 3; i++) {
		proj[i] = rotate_x[i][0] * proj[0] + rotate_x[i][1] * proj[1] + rotate_x[i][2] * proj[2];
	}// x

	return proj;
}


// Renew in this example
void RotatingCoin::draw()
{
	int wc = frame % wn;
	int hc = frame / wn;
	
	double rx = projected2d()[1];
	double ry = projected2d()[2];
	short int xx = (short int)rx + 100;
	short int yy = (short int)-ry + 300;
	
	SDL_Rect s, d;
	s.x = getWidth() * wc;
	s.y = getHeight() * hc;
	s.w = getWidth();
	s.h = getHeight();
	d.x = (int)xx;
	d.y = (int)yy;
	//d.w = s.w;
	d.w = 40;
	d.h = 40;
	//d.h = s.h;
	if (show) {
		setAlpha(255);
	}
	else {
		setAlpha(0);
	}
	image.setSrcRegion(s);
	image.setDstRegion(d);
	image.draw();
}

// Renew in this example
Uint32 RotatingCoin::changeData(Uint32 interval, void* param)
{
	RotatingCoin* p = (RotatingCoin*)param;

	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}

}

void RotatingCoin::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void RotatingCoin::stopTimer()
{
	time = 0;
}
void RotatingCoin::setAlpha(int a)
{
	image.setAlpha(a);
}

void RotatingCoin::setShow(bool s) {
	show = s;
}

int RotatingCoin::getAlpha() {
	return image.getAlpha();
}
bool RotatingCoin::getShow() {
	return show;
}