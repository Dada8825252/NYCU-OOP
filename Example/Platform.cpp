#include "Platform.h"
#include "Image.h"
#include "constants.h"
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <iostream>
using namespace std;

Platform::Platform(const char* path, int n, SDL_Renderer* renderer)
{
	num = n;
	image = new Image[num];
	setEmerge(false);
	setAlpha(255);
	setButtomLeftMove(false);
	setswitchFlag(false);
	setvelocity(10, 10);
	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		cout << "in constructor\n";
		image[i].set(file, renderer);
	}
	cout << "in constructor\n";
	frame = 0;
}
Platform::Platform(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].set(file, renderer, r, g, b);
	}

	frame = 0;
}
void Platform::setnewimage(const char* path, int n, SDL_Renderer* renderer)
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
/*Jump::Jump(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 gg, Uint8 b)
{
	image.set(path, renderer, r, gg, b);
}*/
void Platform::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}
void Platform::setposition(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}
void Platform::setnowposition(double pos) {
	nowposition = pos;
}
void Platform::setvelocity(double velyy, double velzz) {
	vely = velyy;
	velz = velzz;
}

void Platform::settargetposition(double tpos) {
	target = tpos;
}
void Platform::setswitchFlag(bool sFlag) {
	switchFlag = sFlag;
}
void Platform::setmoveflag(bool mflag) {
	moveflag = mflag;
}
void Platform::setAlpha(int a)
{
	image->setAlpha(a);
}
double Platform::gety() {
	return y;
}
double Platform::getz() {
	return z;
}
double Platform::gettargetpos() {
	return target;
}
int Platform::getAlpha() {
	return image->getAlpha();
}
bool Platform::getswitchFlag() {
	return switchFlag;
}
double* Platform::projected2d() {
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

void Platform::draw(SDL_Renderer* renderer) {

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
	d.w = 200;
	d.h = 100;

	image[frame].draw(renderer, d, { ALLREGION });
	//	cout << "in draw\n";
	//	cout << proj[0] << " " << proj[1] << " " << proj[2] << endl;
/* }
	else {
		//image position
		//stick image

	}*/

}
void Platform::move() {

}
Uint32 Platform::framechanging(Uint32 interval, void* param) {
	//z = velz * time;
	//y = vely * time - 0.5 * g * time * time;

	Platform* p = (Platform*)param;
	if (p->time != 0) {
		p->frame = (p->frame + 1) % p->num;
		if (p->getButtomLeftMove() == true)
		{
		//	cout << "go  "<< p->getButtomLeftMove()<<endl;
			if (p->y > platstarty && p->z > platdownz) {
				if ((p->y) > platstarty)
				{
					if ((p->y) - (p->vely) < platstarty)
					{
						p->y = platstarty;
					}
					else
					{
						p->y -= (p->vely);	
					}
						
					if (p->y == platstarty) 
					{
					//	cout << "false\n";
						p->setButtomLeftMove(false);
						p->switchFlag = true;
					}
					p->z = platupz;
				}
				else
				{
					p->y = platstarty;
					p->setButtomLeftMove(false);
				//	cout << "false\n";
					p->switchFlag = true;
				}
			}
			else {
				p->z -= (p->velz);
				if (p->getAlpha() > 50)
				{
					p->setAlpha(p->getAlpha() - 10);
				}
				else
					p->setAlpha(50);
				//	cout << "down  " << p->moveflag << endl;
				if (p->z <= (platdownz)) {
					p->y = p->target;
					p->z = (platdownz);
					p->setButtomLeftMove(false);
					p->setAlpha(50);
					p->switchFlag = true;
				}
			}
			
		}
		else if(p->getemerge())
		{		
			p->z = (p->z + p->velz);

			if (p->getAlpha() < 260)
			{
				p->setAlpha(p->getAlpha() + 10);
				if (p->getAlpha() == 250)
					p->setAlpha(255);
			}
			else
				p->setAlpha(255);


			if (p->z >= platupz)
				p->setEmerge(false);
		}

		return interval;
	}
	else
		return 0;
}
//overload

Uint32 Platform::changeData(Uint32 interval, void* param)
{
	Platform* p = (Platform*)param;
	//¥øÃZ¥ª²¾
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
		//µ²§ô move ´N fly
		p->setflyormove(false); //fly
		return 0; //touch the edge then stop timer(return time=0
	}

}

//overloading
void Platform::startTimer(Uint32 t)
{
	time = t;
	/*if (flyormove) //move
		timerID = SDL_AddTimer(time, changeData, this);
	else //fly*/
	timerID = SDL_AddTimer(time, framechanging, this);

}
void Platform::stopTimer() {
	time = 0;
}
