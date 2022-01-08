#pragma once
#include "GameObject.h"
#include "GLUT.h"
#include <math.h>

const int PI = 3.14;

class Coin : public GameObject
{
public:
	Coin(int x, int y);
	Coin();
	~Coin();
	void setEaten(bool eaten);
	bool getEaten();
	void drawCoin(GLfloat cx, GLfloat cy, GLfloat r);

private:
	bool eaten;

};