#pragma once

#include "Constants.h"
#include <GL/gl.h>

using namespace Constants;

class Hook
{
public:
	Hook();
	Hook(double x, double y, double z);
	double getX();
	double getY();
	double getZ();
	double getRadius();
	void calculatePosition();
	HookStates getHookState();
	void pullHook();
	void grabMineral(MineralTypes mineral);
	GLfloat* getColor();


private:
	int direction;
	GLfloat * color;
	double ANGLE_STEP = 2.5;
	int DEFAULT_ANGLE = 300;
	int MIN_ANGLE = 190;
	int MAX_ANGLE = 350;
	double SPEED = 0.03;
	double RADIUS = 0.007;
	double LENGTH = 0.05;
	double x0;
	double y0;
	double z0;
	double x;
	double y;
	double z;
	double angle;
	HookStates hookState;
	void calculate(double c);
	MineralTypes mineral;
};

