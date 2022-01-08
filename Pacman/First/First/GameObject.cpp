#include "GameObject.h"

GameObject::GameObject(int x, int y)
{
	this->x = x;
	this->y = y;
}

GameObject::GameObject()
{
}

void GameObject::setX(int x)
{
	this->x = x;
}

void GameObject::setY(int y)
{
	this->y = y;
}

int GameObject::getX()
{
	return x;
}

int GameObject::getY()
{
	return y;
}
