#include "Coin.h"

Coin::Coin(int x, int y) : GameObject(x, y)
{
	eaten = false;
}

Coin::Coin() : GameObject()
{
	eaten = false;
}

Coin::~Coin()
{
}

void Coin::setEaten(bool eaten)
{
	this->eaten = eaten;
}

bool Coin::getEaten()
{
	return eaten;
}

void Coin::drawCoin(GLfloat cx, GLfloat cy, GLfloat r)
{
	double alpha, delta = PI / 20;
	double x, y;
	glColor3d(0.81, 0.71, 0.23);
	glBegin(GL_POLYGON);
	for (alpha = 0; alpha <= 2 * PI; alpha += delta)
	{
		x = r * cos(alpha) + cx;
		y = r * sin(alpha) + cy;
		glVertex2d(x, y);
	}
	glEnd();
}


