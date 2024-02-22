#include "Jump.h"
#include "Image.h"
#include "constants.h"
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "Image.h"

Jump::Jump()
{
	//cout << "call default constructor" << endl;
	setdistance(0);
	setvelocity(0, 0, 0);
	setpoints(0);
	settargetposition(275);
}
Jump::Jump(const char* path, int n, SDL_Renderer* renderer)
{
	num = n;
	image = new Image[num];
	
	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		
		image[i].set(file, renderer);
		image[i].setAlpha(255);
	}
	setjumpflag(false);
	settargetposition(300);
	setoverflag(false);
	frame = 0;
}
Jump::Jump(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		
		image[i].set(file, renderer, r, g, b);
	}
	setjumpflag(false);
	settargetposition(300);
	setoverflag(false);
	frame = 0;
}
void Jump::setnewimage(const char* path, int n, SDL_Renderer* renderer, bool once)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		//	cout << "in constructor\n";
		image[i].set(file, renderer);

	}

	//	cout << "in constructor\n";
	frame = 0;
}
void Jump::setnewimage(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, bool once)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
	//	cout << "in constructor\n";
		image[i].set(file, renderer, r, g, b);
		/*if (i == num - 1 && once == 1)
			stopTimer();*/
	}
	
//	cout << "in constructor\n";
	frame = 0;
}
/*Jump::Jump(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 gg, Uint8 b)
{
	image.set(path, renderer, r, gg, b);
}*/
void Jump::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}
void Jump::setposition(double xx, double yy, double zz,double theta) {
	x = xx;
	y = yy;
	angle = theta;
	nowposition = yy;
	z = zz;
}
void Jump::setnowposition(double pos) {
	nowposition = pos;
}
void Jump::setvelocity(double velyy, double velzz, double azz) {
	vely = velyy; //橫向速度
	velz = velzz; //縱向速度
	az = azz; //縱向加速度
	velwind = 0;
	flyx = 0;
}
void Jump::setvelocity(double velxx, double azz) {
	vely = velxx;
	az = azz;
	velz = 0.5 * az * distance / vely;
}
void Jump::setwindvelocity(double vwind) {
	velwind = vwind;
}
void Jump::setdistance(double d) {
	distance = d;
}
void Jump::setflyback(double flyxx) {
	flyx = flyxx;
}
void Jump::setpoints(int p) {
	points = p;
}
void Jump::settargetposition(double tpos) {
	target = tpos;
}
void Jump::setAlpha(int a)
{
	for (int i = 0; i < num; i++) {
		image[i].setAlpha(a);
	}
	
}
double Jump::getdistance() {
	return distance;
}
double Jump::gettarget() {
	return target;
}
int Jump::getpoints() {
	return points;
}
double Jump::getnowposition()
{
	return nowposition;
}
int Jump::getAlpha() {
	return image->getAlpha();
}
double* Jump::projected2d() {
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

void Jump::draw(SDL_Renderer* renderer) {

//	if (flyormove == false) { //fly
		double rx = projected2d()[1];
		double ry = projected2d()[2];
		short int xx = (short int)rx + 100;
		short int yy = (short int)-ry + 300;
	//	filledCircleRGBA(renderer, xx, yy, 10, 0x0A, 0xBA, 0xB5, 0xFF);
		//stick image
		SDL_Rect d, s;
		d.x = (int)xx;
		d.y = (int)yy;
		d.w = 300;
		d.h = 300;

		image[frame].draw(renderer, d, { ALLREGION });
	//	cout << "in draw\n";
	//	cout << proj[0] << " " << proj[1] << " " << proj[2] << endl;
/* }
	else {
		//image position
		//stick image

	}*/

}
void Jump::move() {

}
Uint32 Jump::framechanging(Uint32 interval, void* param) {
	//z = velz * time;
	//y = vely * time - 0.5 * g * time * time;
	Jump* j = (Jump*)param;
	if (j->time != 0) {
		j->frame = (j->frame + 1) % j->num;
		static int flag = 1;
		if (j->jumpflag)
		{
			//cout << j->getdistance() << endl;
			//cout << j->z << " " << j->y << " " << j->distance << endl;
			if ((((j->y) <= (j->distance)) || (j->z) > 0))
			{
				//	cout << "start\n";
				if ((j->y) + (j->vely) < (j->distance))
				{
					cout << "run\n";
					j->y += (j->vely);
					j->z += (j->velz);
					j->velz -= (j->az);
					j->x += (j->velwind) + (j->flyx);
				}
				else
				{
					j->y = j->distance;
					j->z = 0;
				}
			}

		}
		else if (!(j->fall))
		{
			if ((j->y) > (j->nowposition))
			{
				if ((j->y) - 10 < (j->nowposition))
				{
					j->y = (j->nowposition);
					j->distance = 0;
					flag = 1;
				}
				else
					j->y -= 10;

				j->z = 0;
			}
			else
			{
				j->y = (j->nowposition);
				j->z = 0;
				j->distance = j->nowposition;
			}
		}
		else if (j->fall)
		{
			if (j->z > platdownz)
			{
				j->z += j->velz;
				j->setAlpha(j->getAlpha() - 10);
			}
			else
			{
				j->setAlpha(255);
				j->fall = 0;
				j->y = (j->nowposition);
				j->z = 0;
				j->distance = j->nowposition;
			}

		}
		return interval;
	}
	else
		return 0;
}
//overload

Uint32 Jump::changeData(Uint32 interval, void* param)
{
	Jump* p = (Jump*)param;
	//企鵝左移
	if (p->getButtomLeftMove() == true && p->time != 0) {
		//image frame
		p->setframe((p->getframe() + 1) % (p->getnum()));
		//image position
		p->x = (p->x - 5);
		p->y = (p->y + 5);
		if (p->x == 20 || p->y == (HEIGHT - 80)) {
			p->setButtomLeftMove(false);
		}
		return interval;
	}
	else {
		//結束 move 就 fly
		p->setflyormove(false); //fly
		return 0; //touch the edge then stop timer(return time=0
	}

}

//overloading
void Jump::startTimer(Uint32 t)
{
	time = t;
	
	timerID = SDL_AddTimer(time, framechanging, this);

}
void Jump::stopTimer() {
	time = 0;
}

void Jump::setfallflag(bool f) {
	fall = f;
}

bool Jump::getfallflag()
{
	return fall;
}

double Jump::getvely() {
	return vely;
}


void Jump::lift() {
	z += vlift;
	//	y += vlift / 2;
}
void Jump::setvelz(double vz)
{
	velz = vz;
}
void Jump::setx(double xx)
{
	x = xx;
}
void Jump::sety(double yy)
{
	y = yy;
}
void Jump::setz(double zz)
{
	z = zz;
}
void Jump::setvlift(double vl) {
	vlift = vl;
	vely = vl / 2;
}

void Jump::setjumpflag(bool f) {
	jumpflag = f;
}
double Jump::getx()
{
	return x;
}
double Jump::gety() {
	return y;
}
double Jump::getz()
{
	return z;
}
double Jump::getvelz()
{
	return velz;
}
double Jump::getaz()
{
	return az;
}
double Jump::getvelwind()
{
	return velwind;
}
double Jump::getflyx()
{
	return flyx;
}
bool Jump::getjumpflag() {
	return jumpflag;
}

void Jump::setoverflag(bool ol) {
	overflag = ol;
}

bool Jump::getoverflag() {
	return overflag;
}

Uint32 Jump::jumping(Uint32 interval, void* param)
{
	Jump* j = (Jump*)param;
	if (j->time != 0)
	{
		j->frame = (j->frame + 1) % j->num;
		//static bool jumpflag = 1;
		if (j->jumpflag)
		{
			if (j->z + j->vlift >= 0)
			{
				j->vlift -= j->az;
				j->z += j->vlift;
				j->y += j->vely;
			}
			else
			{
				double landedpoint = j->y + 100;
				j->target = 320;
				if (landedpoint >= j->target - 50 && landedpoint <= j->target + 100) // successfully landed
				{
					j->z = 0;
					j->setjumpflag(false);
				}
				else
				{
					//	do { j->z += j->vlift/10; } while (j->z > platdownz);	
					static int over = 0;
					over++;
					if (over == 5)
						j->setoverflag(true);
					else
					{
						j->y = 0;
						j->z = 0;
						j->vlift = 0;
					}

				}
			}
		}
		else
		{

		}
		return interval;
	}
	else
		return 0;
}
