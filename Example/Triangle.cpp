#include "Triangle.h"
#include <time.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<ctime>
using namespace std;


Triangle::Triangle(const char* path, SDL_Renderer* renderer) :Jump() {

	anglev = 1; //the turning velocity
	angle = 0;
	ysign = -1;
	zsign = -1;
	squeeze = 1;
	setsqueezesign(true);
	setstartjump(false);
	setstartsqueeze(false);
	setstartrotate(true);
	objLoad(path);

	cout << "size :" << size(meshCube.tris) << endl;
	fNear = 0.1f;
	fFar = 1000.0f;
	fFov = 90.0f;
	fAspectRatio = (float)HEIGHT / (float)WIDTH;
	fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * M_PI);

	//set mat
	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
	//fElapsedTime = 2;
}


void Triangle::setstartgame(bool sg)
{
	startgame = sg;
}

void Triangle::setstartjump(bool sj)
{
	startjump = sj;
}

void Triangle::setstartsqueeze(bool sq)
{
	startsqueeze = sq;
}

void Triangle::setsqueezesign(bool sz)
{
	squeezesign = sz;
}

void Triangle::setstartrotate(bool sr)
{
	startrotate = sr;
}

void Triangle::setflyback(double flyxx)
{
	Jump::setflyback(flyxx);
}

void Triangle::setdistance(double d)
{
	Jump::setdistance(d);
}

void Triangle::setvelocity(double velxx, double azz)
{
	Jump::setvelocity(velxx, azz);
}

void Triangle::setnowposition(double pos)
{
	Jump::setnowposition(pos);
}

void Triangle::setwindvelocity(double vwind)
{
	Jump::setwindvelocity(vwind);
}



double Triangle::getsqueeze()
{
	return squeeze;
}

double Triangle::gety()
{
	return Jump::gety();
}

double Triangle::getdistance()
{
	return Jump::getdistance();
}

double Triangle::gettarget()
{
	return Jump::gettarget();
}

void Triangle::setvlift(double vl)
{
	Jump::setvlift(vl);
}

void Triangle::setjumpflag(bool f)
{
	Jump::setjumpflag(f);
}

void Triangle::setfallflag(bool f)
{
	Jump::setfallflag(f);
}


//set o by i
void Triangle::MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m) {

	o.y = i.y * m.m[0][0] + i.z * m.m[1][0] + i.x * m.m[2][0] + m.m[3][0]; //y axis(width 
	o.z = i.y * m.m[0][1] + i.z * m.m[1][1] + i.x * m.m[2][1] + m.m[3][1]; //z axis(height
	o.x = i.y * m.m[0][2] + i.z * m.m[1][2] + i.x * m.m[2][2] + m.m[3][2]; //x axis(depth1
	float w = i.y * m.m[0][3] + i.z * m.m[1][3] + i.x * m.m[2][3] + m.m[3][3];

	//4D->3D
	if (w != 0) {
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}

}

void Triangle::draw(SDL_Renderer* renderer) {
	//cout << "rotateornot :" << startrotate << endl;
	cout << "y :" << gety() << " distance :" << getdistance() << endl;

	double ry = projected2d()[1];
	double rz = projected2d()[2];
	short int yy = (short int)ry;
	short int zz = (short int)-rz;

	//set rotation depth
	matRotX.m[0][0] = cosf(angle);
	matRotX.m[0][1] = sinf(angle);
	matRotX.m[1][0] = -sinf(angle);
	matRotX.m[1][1] = cosf(angle);
	matRotX.m[2][2] = 1;
	matRotX.m[3][3] = 1;

	//set rotation width
	matRotY.m[0][0] = 1;
	matRotY.m[1][1] = cosf(angle * 0.5f);
	matRotY.m[1][2] = sinf(angle * 0.5f);
	matRotY.m[2][1] = -sinf(angle * 0.5f);
	matRotY.m[2][2] = cosf(angle * 0.5f);
	matRotY.m[3][3] = 1;

	//set rotation height
	matRotZ.m[0][0] = cosf(angle * 0.5f);
	matRotZ.m[0][2] = -sinf(angle * 0.5f);
	matRotZ.m[1][1] = 1;
	matRotZ.m[2][0] = sinf(angle * 0.5f);
	matRotZ.m[2][2] = cosf(angle * 0.5f);
	matRotZ.m[3][3] = 1;


	for (auto tri : meshCube.tris) { //tri:which side
		triangle triProjected, triTranslated, triRotatedZYX, triRotatedZY, triRotatedZ;


		//turn 3d vertices to 2d
		//rotated around the origin of the object
		MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
		MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
		MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);
		triTranslated = triRotatedZ;

		//to let us get backward from the triangle(we may be inside of the triangle
		for (int i = 0; i < 3; i++) {
			triTranslated.p[i].x = triRotatedZ.p[i].x + 7.0f; //x:dipth  to move further
		}

		//finish all the tranformation then projected to triProjected
		for (int i = 0; i < 3; i++) {
			MultiplyMatrixVector(triTranslated.p[i], triProjected.p[i], matProj); //p[] which triangle
		}
		
		if (startgame) {
			for (int i = 0; i < 3; i++) {
				triProjected.p[i].z += 0.35f;
				triProjected.p[i].y -= 0.35f;

				if (startsqueeze) {
					triProjected.p[i].z = (triProjected.p[i].z - 0.794463) * squeeze + 0.794463;
				}
				else {
					triProjected.p[i].z = triProjected.p[i].z;
				}

				triProjected.p[i].z += zz / 1000.0;
				triProjected.p[i].y += yy / 1000.0;
				triProjected.p[i].x += getx() / 1000.0;
			}
		}

		//scale into view
		triProjected.p[0].y += 1.0f; triProjected.p[0].z += 1.0f;
		triProjected.p[1].y += 1.0f; triProjected.p[1].z += 1.0f;
		triProjected.p[2].y += 1.0f; triProjected.p[2].z += 1.0f;

		triProjected.p[0].y *= 0.5f * WIDTH; //400
		triProjected.p[0].z *= 0.5f * HEIGHT; //300
		triProjected.p[1].y *= 0.5f * WIDTH;
		triProjected.p[1].z *= 0.5f * HEIGHT;
		triProjected.p[2].y *= 0.5f * WIDTH;
		triProjected.p[2].z *= 0.5f * HEIGHT;

		//	Draw Triangle
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, triProjected.p[0].y, triProjected.p[0].z, triProjected.p[1].y, triProjected.p[1].z);
		SDL_RenderDrawLine(renderer, triProjected.p[1].y, triProjected.p[1].z, triProjected.p[2].y, triProjected.p[2].z);
		SDL_RenderDrawLine(renderer, triProjected.p[2].y, triProjected.p[2].z, triProjected.p[0].y, triProjected.p[0].z);

	}

}
double*** Triangle::projected() {
	double rotate_z[3][3] =
	{
		cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1
	};
	double*** proj;
	proj = new double** [12];
	for (int i = 0; i < 3; i++) {
		proj[i] = new double* [3];
		for (int j = 0; j < 3; j++) {
			proj[i][j] = new double[3];
		}
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				proj[i][j][k] = rotate_z[k][0] * meshCube.tris[i].p[j].x + rotate_z[k][1] * meshCube.tris[i].p[j].y + rotate_z[k][2] * meshCube.tris[i].p[j].z;
			}
		}
	}// z 
	return proj;
}

void Triangle::setAngle(Uint64 t)
{
	angle = t;
}
bool Triangle::objLoad(const char* path)
{
	FILE* file;
	errno_t err;
	err = fopen_s(&file, path, "r");
	if (err != 0) {
		printf("The file 'Low_poly_penguin.txt' was not opened\n");
		return false;
	}
	else {
		printf("The file 'Low_poly_penguin.txt' was  opened\n");
	}
	while (1) {

		char lineHeader[128] = { 0 };
		vec3d vec, normal;
		triangle tri;
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 127);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			fscanf_s(file, "%f %f %fn", &vec.y, &vec.z, &vec.x);
			vec.z = vec.z * zsign;//turn head
			vec.z = vec.z - 2.0f * zsign;//move down 
			vec.y = vec.y * ysign;
			vec.y = vec.y + 0.5f * ysign;
			vecs.push_back(vec);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf_s(file, "%f %f %fn", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
			//cout << "push back" << endl;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%dn", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other optionsn");
				return false;
			}
			//a unit of vertexIndices = a triangle
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			tri.p[0] = vecs[vertexIndex[0] - 1]; //obj index start from 1
			tri.p[1] = vecs[vertexIndex[1] - 1];
			tri.p[2] = vecs[vertexIndex[2] - 1];
			meshCube.tris.push_back(tri);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]); //3 points have same normal line
			//normalIndices.push_back(normalIndex[1]);
			//normalIndices.push_back(normalIndex[2]);
		}

	}
	cout << "normal size" << normals.size() << endl;
	return false;
}

Uint32 Triangle::changeData(Uint32 interval, void* param) {

	Triangle* t = (Triangle*)param;

	if (t->time != 0)
	{
		//squeeze
		if (t->startsqueeze) {
			t->setstartrotate(false);

			if (t->squeezesign == true) {
				t->squeeze -= 0.05;
				if (t->squeeze <= 0.4) {
					t->setsqueezesign(false);
				}
			}
			else {
				t->squeeze += 0.05;
				if (t->squeeze >= 1) {
					t->setsqueezesign(true);
				}
			}
		}

		//rotate
		if (t->startrotate) {
			t->anglev = -1;
			if (t->angle >= 0)
			{
				t->angle += t->anglev;
				t->angle %= 360;
			}
			else if ((t->angle) + (t->anglev) < 0)
			{
				t->angle += 360 + (t->anglev);
			}
		}
		else {
			t->angle = -M_PI / 2.0;
		}


		t->radian = (double)(t->angle) * M_PI / 180.0;
		//cout << t->radian << endl;
		return interval;
	}
	else
		return 0;

}
//§âxyz³]0 0 0
Uint32 Triangle::framechanging(Uint32 interval, void* param) {

	Triangle* tri = (Triangle*)param;
	if (!tri->startgame)
		return interval;
	else {
		if (tri->time != 0) {
			static int flag = 1;
			if (tri->getjumpflag())
			{
				if ((((tri->gety()) < (tri->getdistance()) || (tri->getz()) > 0))) //flying
				{
					if ((tri->gety()) + (tri->getvely()) < (tri->getdistance())) //not over target
					{
						cout << "flying\n";
						//j->y += (triangle->getvely());
						tri->sety(tri->gety() + tri->getvely());

						//j->z += (triangle->getvelz());
						tri->setz(tri->getz() + tri->getvelz());

						tri->setvelz(tri->getvelz() - tri->getaz());

						//j->x += (triangle->getvelwind()) + (triangle->getflyx());
						tri->setx(tri->getx() + tri->getvelwind() + tri->getflyx());
					}
					else //over target
					{
						tri->sety(tri->getdistance());
						tri->setz(0);
						tri->setfallflag(true);
					}
				}
			}
			else if (!(tri->getfallflag())) //on the platform
			{
				if ((tri->gety()) > (tri->getnowposition()))//moving with platform
				{
					cout << "moving left" << endl;
					if ((tri->gety()) - 23 < (tri->getnowposition()))
					{
						//j->y = (triangle->getnowposition());
						tri->sety(tri->getnowposition());
						tri->setdistance(0);
						flag = 1;
						tri->setstartrotate(true);
					}
					else {
						//j->y -= 10;
						tri->sety(tri->gety() - 23);
					}
					tri->setz(0);
				}
				else //finish moving
				{
					//cout << "ready to jump" << endl;
					tri->sety(tri->getnowposition());
					tri->setz(0);
					tri->setdistance(tri->getnowposition());
				}
			}
			else if (tri->getfallflag()) //into water
			{
				cout << "fall into water" << endl;
				if (tri->getz() > platdownz)
				{
					tri->setz(tri->getz() + tri->getvelz());
				}
				else
				{
					tri->setfallflag(0);
					tri->sety(tri->getnowposition());
					tri->setz(0);
					tri->setdistance(tri->getnowposition());
				}
			}
			return interval;
		}
		else
			return 0;
	}
}

void Triangle::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);
}

void Triangle::startTimer2(Uint32 t)
{
	time2 = t;
	timerID2 = SDL_AddTimer(time2, framechanging, this);
}

void Triangle::stopTimer()
{
	time = 0;
}

void Triangle::stopTimer2()
{
	time2 = 0;
}

void Triangle::setposition(double xx, double yy, double zz, double theta)
{
	Jump::setposition(xx, yy, zz, theta);
}

