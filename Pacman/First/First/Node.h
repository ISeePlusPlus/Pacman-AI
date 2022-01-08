#pragma once
#include <math.h> 
#include <stdio.h>


const int SPACE = 0;
const int WALL = 1;
const int PAC_MAN = 2;
const int PATH_PACMAN = 3; 
const int GRAY_PACMAN = 4;
const int BLACK_PACMAN = 5; 

const int GHOST1 = 7;
const int GHOST2 = 8;
const int GHOST3 = 9;
const int PATH_GHOST = 10;
const int GRAY_GHOST = 11;
const int BLACK_GHOST = 12;




class Node
{
public:
	Node();
	Node( Node *other);
	~Node();

private:
	int value;
	Node* parent;
	int line, column, g; // g = distance from start - num nodes
	double h; // direct distance from current node to end node
	double f;

public:
	void SetParent(Node * p);
	void SetValue(int value);
	void SetLine(int line);
	void SetColumn(int col);
	int GetValue();
	int GetLine();
	int GetColumn();
	Node * GetParent();
	int ManhattanDistance(Node* end);
	int getG();
	void SetG(int g);
	void SetH(Node* end);
	double GetH();
	double GetF();
	void SetF();
};

