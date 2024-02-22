#pragma once
#include<vector>
#include <SDL.h>
#include "constants.h"
#include<math.h>
#include "Jump.h"
using namespace std;
class Triangle : Jump
{
private:

	struct vec3d {
		float x, y, z; //x:²`«× y:¼e z:°ª
	};

	struct triangle { //each triangle
		vec3d p[3];
	}tri;

	struct mesh { //gather the triangles
		vector<triangle> tris;
	}meshCube, meshNormal;

	struct mat4x4 {	//project function
		float m[4][4] = { 0 }; //4D matrix
	};

	//static time_t fElapsedTime; // the time since execution
	int angle;
	int ysign;
	int zsign;
	int anglev;
	double anglex;
	double anglez;
	double angley;
	double radian;
	double squeeze;
	bool squeezesign;
	bool fall;
	bool startgame;
	bool startjump;
	bool startrotate;
	bool startsqueeze;
	SDL_TimerID timerID, timerID2;
	Uint32 time, time2;
	mat4x4 matProj, matRotX, matRotY, matRotZ;
	int vertexIndex[3] = { 0 }, uvIndex[3] = { 0 }, normalIndex[3] = { 0 };
	vector<int>vertexIndices, uvIndices, normalIndices;
	vector<vec3d> vecs;
	vector<vec3d> normals;
	float fNear, fFar, fFov, fAspectRatio, fFovRad;
	void MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m);
	static Uint32 changeData(Uint32 interval, void* param);
	static Uint32 framechanging(Uint32 interval, void* param);

	Jump jj;
	char* p = new char[128];

public:
	Triangle(const char* path, SDL_Renderer* renderer);
	bool objLoad(const char* path);
	double*** projected();
	void setAngle(Uint64);
	void draw(SDL_Renderer* renderer);
	void startTimer(Uint32 t);
	void startTimer2(Uint32 t);
	void stopTimer();
	void stopTimer2();
	void setposition(double xx, double yy, double zz, double theta);
	void setstartgame(bool sg);
	void setstartjump(bool sj);
	void setstartsqueeze(bool sq);
	void setsqueezesign(bool sz);
	void setstartrotate(bool sr);
	void setflyback(double flyxx);
	void setdistance(double d);
	void setvelocity(double velxx, double azz);
	void setnowposition(double pos);
	void setwindvelocity(double vwind);
	double getsqueeze();
	double gety();
	double getdistance();
	double gettarget();

	void setvlift(double vl);
	void setjumpflag(bool f);
	void setfallflag(bool f);
};

