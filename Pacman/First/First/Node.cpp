#include "Node.h"


Node::Node()
{
	value = SPACE;
	parent = nullptr;
	line = 0;
	column = 0;
	g = 0;
	h = 0;
	f = 0;
}


Node::Node( Node *other)
{
	value = other->GetValue();
	line = other->GetLine();
	column = other->GetColumn();
	g = other->g;
	if (other->GetParent() == nullptr)
		parent = nullptr;
	else
		parent = new Node(other->GetParent());

}

int Node::ManhattanDistance(Node* end)  // distance to end
{
	double x1, x2, y1, y2;

	x1 = this->GetColumn();
	y1 = this->GetLine();
	x2 = end->GetColumn();
	y2 = end->GetLine();


	return fabs(x2 - x1) + fabs(y2 - y1);
}


Node::~Node()
{
}


void Node::SetParent(Node* p)
{
	parent = p;
}


void Node::SetValue( int value)
{
	this->value = value;
}

void Node::SetLine(int line)
{
	this->line = line;
}


void Node::SetColumn(int col)
{
	this->column = col;
}

int Node::GetValue()
{
	return value;
}


int Node::GetLine()
{
	return line;
}


int Node::GetColumn()
{
	return column;
}

Node* Node::GetParent()
{
	return parent;
}

int Node::getG()
{
	return g;
}

void Node::SetG(int g)
{
	this->g = g;
}

void Node::SetH(Node* end)
{
	this->h = ManhattanDistance(end);
}

double Node::GetH()
{
	return h;
}

double Node::GetF()
{
	return f;
}

void Node::SetF()
{
	f = h + g;
}
