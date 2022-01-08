#pragma once
class GameObject
{
public: 
	GameObject(int x, int y);
	GameObject();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

private:
	int x;
	int y;
};

