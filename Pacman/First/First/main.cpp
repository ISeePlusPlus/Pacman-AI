#include "GLUT.h"
#include <time.h>
#include "Node.h"
#include <vector>
#include "ghost.h"
#include <stack>
#include "Coin.h"
#include "CompareNodesInReverse.h"

// For pause
#include <Windows.h>

// hyper parameters
const int W = 900; // window width
const int H = 900; // window height
const int MSZ = 25;
Node* maze[MSZ][MSZ];
Coin* coin[MSZ][MSZ];
bool run_AStar = false;
int flag = 0;

// monster parameters
Node* ghost1, * ghost2, * ghost3;
GLdouble ghostColor[3][3] = { {1.0, 0.0, 0.0}, {1.0, 0.72, 1.0}, {0.0, 1.0, 1.0} };
priority_queue <Node*, vector<Node*>, CompareNodes> pq1;
stack <Node*> path1;
priority_queue <Node*, vector<Node*>, CompareNodes> pq2;
stack <Node*> path2;
priority_queue <Node*, vector<Node*>, CompareNodes> pq3;
stack <Node*> path3;


//pacman consts
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

Node* nextCoin;

// calculate coins distance
priority_queue <Node*, vector<Node*>, CompareNodesInReverse> pq;


//for coins
priority_queue <Node*, vector<Node*>, CompareNodes> coinsQ;

//calculate distance from monsters
priority_queue <Node*, vector<Node*>, CompareNodes> monsters;

//priority_queue <Node*, vector<Node*>, CompareNodes> gray;
Node* pacman;
stack <Node*> path;

void SetupMaze();
void display();
//Node* BfsIteration();

void drawPacman(GLfloat cx, GLfloat cy, GLfloat r, const int direction = RIGHT)
{
	double circle_points = 100.f;
	GLfloat angle;
	glBegin(GL_POLYGON);
	glVertex2d(cx, cy);

	if (direction == RIGHT)
	{
		for (int i = 10; i < circle_points; i++)
		{
			angle = 1.80 * PI * i / circle_points;
			glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
		}
		glEnd();
	}

	else if (direction == DOWN)
	{
		for (int i = -20; i < circle_points; i++)
		{
			angle = 1.30 * PI * i / circle_points;
			glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
		}
		glEnd();

	}

	else if (direction == LEFT)
	{
		for (int i = -100; i < circle_points; i++)
		{
			angle = 0.7 * PI * i / circle_points;
			glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
		}
		glEnd();

	}
	//TODO
	else if (direction == UP)
	{
		for (int i = 10; i < circle_points; i++)
		{
			angle = 1.80 * PI * i / circle_points;
			glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
		}
		glEnd();

	}

	/*

	///////////////////////////////////
	double alpha, delta = PI / 20;
	double x, y;
	glColor3d(1, 0, 1);
	glBegin(GL_POLYGON);
	for (alpha = 0; alpha <= 2 * PI; alpha += delta)
	{
		x = cx + r * cos(alpha) * 2/25 ;
		y = cy + r * sin(alpha) * 2/25 ;
		glVertex2d(x+0.9, y+ 0.7);
	}
	glEnd();s
	*/
}

void drawGhosts(GLfloat cx, GLfloat cy, GLfloat r, GLdouble color[])
{
	glColor3d(color[0], color[1], color[2]);
	double circle_points = 100.f;
	GLfloat angle;
	glBegin(GL_POLYGON);
	glVertex2d(cx, cy);

	for (int i = 0; i <= circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(cx - r, cy);
	glVertex2d(cx - r, cy - r / 2);
	glVertex2d(cx + r, cy - r / 2);
	glVertex2d(cx + r, cy);
	glEnd();

	GLfloat sz = r;
	for (int i = 0; i < 4; i++)
	{

		int index = i % 4;
		if (index > 1)
		{
			sz = sz / 3;
		}
		if (index % 2 == 1)
		{
			sz = -sz;
		}
		glBegin(GL_POLYGON);
		glVertex2d(cx + sz, cy);
		for (int i = 10; i <= circle_points; i++)
		{
			angle = 1 * PI * i / circle_points;
			glVertex2d((cx - sz + cos(angle) * r / 4), (cy - r - sin(angle) * r / 4));
		}
		glEnd();
	}


	/*
	glBegin(GL_POLYGON);
	glVertex2d(cx - r, cy);
	for (int i = 10; i <= circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex2d((cx - r + cos(angle) * r/4), (cy - r - sin(angle) * r/4));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(cx - r/3 , cy);
	for (int i = 10; i <= circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex2d((cx - r/3 + cos(angle) * r / 4), (cy - r - sin(angle) * r / 4));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(cx + r/3 , cy);
	for (int i = 10; i <= circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex2d((cx +r/3 + cos(angle) * r / 4), (cy - r - sin(angle) * r / 4));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(cx + r , cy);
	for (int i = 10; i <= circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex2d((cx + r  + cos(angle) * r / 4), (cy - r - sin(angle) * r / 4));
	}
	glEnd();
	*/

}

void drawCoin(GLfloat cx, GLfloat cy, GLfloat r)
{
	glColor3d(0.81, 0.71, 0.23);

	double circle_points = 100.f;
	GLfloat angle;
	glBegin(GL_POLYGON);
	glVertex2d(cx, cy);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 2.1 * PI * i / circle_points;
		glVertex2d((cx + cos(angle) * r), (cy + sin(angle) * r));
	}
	glEnd();
}


void init()
{
	int i, j;

	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			maze[i][j] = new Node();
			coin[i][j] = new Coin();
		}


	srand(time(0)); // pseudo randomizer

	glClearColor(0.7, 0.7, 0.7, 0);

	SetupMaze();

	glOrtho(-1, 1, -1, 1, -1, 1);

}

Node* setPosNoneWall()
{

	int RowPos, ColPos;

	do {
		RowPos = rand() % MSZ;
		ColPos = rand() % MSZ;

	} while (RowPos == 0 || RowPos == MSZ - 1 || ColPos == 0 || ColPos == MSZ - 1);

	return maze[RowPos][ColPos];

}

void setCoinAtPositionEaten(Node* entity, bool eaten)
{
	int row = entity->GetLine();
	int col = entity->GetColumn();
	coin[row][col]->setEaten(eaten);
}

void calcDistanceToTarget(Node* pos, Node* target, priority_queue <Node*, vector<Node*>, CompareNodes>& pq)
{
	pos->SetH(target);
	pos->SetG(pos->ManhattanDistance(target));
	pos->SetF();
	pq.push(pos);
}

void calcDistanceFromTarget(Node* pos, Node* target, priority_queue <Node*, vector<Node*>, CompareNodesInReverse>& pq, int newG)
{
	pos->SetH(target);
	pos->SetG(newG);
	pos->SetF();
	pq.push(pos);
	/*
	int value = target->GetValue();

	if (value != WALL)
	{
		if (value != BLACK_PACMAN)
		{
			if (value == SPACE || value == PAC_MAN)
			{
				//coin[pos->GetLine()][pos->GetColumn()]->getEaten == false
				// Add next to PQ only if next was WHITE
				target->SetH(target);
				target->SetG(newG);
				target->SetF();
				value == SPACE ? target->SetValue(GRAY_PACMAN) : 0;  //do nothing if target
				target->SetParent(pos);
				pq.push(target);
			}
			/*
			else if (down->GetValue() == SPACE || down->GetValue() == COIN)
			{
				//maze[current->GetLine() - 1][current->GetColumn()]->SetValue(GRAY); // paint it gray
				//maze[current->GetLine() - 1][current->GetColumn()]->SetParent(current);
				gray.push_back(down);
				pq1.push(down);
			}
			
			//TODO RETHINK THIS
			else // compare it to its actual G
			{
			if (newG < target->getG())
			{
				target->SetG(newG);
				target->SetF();
				target->SetParent(pos);
			}
			}
}
	}
	*/
}

void SetupMaze()
{
	int i, j;

	// setup borders
	for (i = 0; i < MSZ; i++)
	{
		maze[0][i]->SetValue(WALL);
		maze[MSZ - 1][i]->SetValue(WALL);
		maze[i][0]->SetValue(WALL);
		maze[i][MSZ - 1]->SetValue(WALL);
	}

	// add pacman
	pacman = setPosNoneWall();
	pacman->SetValue(PAC_MAN);
	setCoinAtPositionEaten(pacman, true);
	pq.push(pacman);

	// add inner space
	for (i = 1; i < MSZ - 1; i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			maze[i][j]->SetLine(i);
			maze[i][j]->SetColumn(j);
			if (maze[i][j]->GetValue() != PAC_MAN)
			{
				if (i % 2 == 0) // more walls
				{
					if (rand() % 20 > 12)
						maze[i][j]->SetValue(WALL);
				}
				else // more spaces
					if (rand() % 20 > 15)
						maze[i][j]->SetValue(WALL);

				if (maze[i][j]->GetValue() != WALL)
				{
					coin[i][j]->setX(i);
					coin[i][j]->setY(j);
					coin[i][j]->setEaten(false);
				}
			}
		}

	//Create ghosts and add them to pq

	ghost1 = setPosNoneWall();
	ghost1->SetValue(GHOST1);
	setCoinAtPositionEaten(ghost1, true);
	ghost2 = setPosNoneWall();
	ghost2->SetValue(GHOST2);
	setCoinAtPositionEaten(ghost2, true);
	ghost3 = setPosNoneWall();
	ghost3->SetValue(GHOST3);
	setCoinAtPositionEaten(ghost3, true);
	pq1.push(ghost1);
	pq2.push(ghost2);
	pq3.push(ghost3);

	//this adds ghosts to monsters pq to calculate distance from pacman
	calcDistanceToTarget(ghost1, pacman, monsters);
	calcDistanceToTarget(ghost2, pacman, monsters);
	calcDistanceToTarget(ghost3, pacman, monsters);
}

void drawBackground(double x, double y, double sz)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + sz, y);
	glVertex2d(x + sz, y + sz);
	glVertex2d(x, y + sz);
	glEnd();
}

void DrawMaze()
{
	int i, j;
	double sz, x, y;

	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			// set color

			// draw rectangle
			sz = 2.0 / MSZ;
			x = j * sz - 1;
			y = i * sz - 1;

			int value = maze[i][j]->GetValue();

			if (value == WALL)
			{
				glColor3d(0.13, 0.13, 0.87);
				drawBackground(x, y, sz);
			}

			if (value == SPACE || value == GRAY_GHOST || value == BLACK_GHOST || value == GRAY_PACMAN || value == BLACK_PACMAN)
			{
				glColor3d(0, 0, 0);
				drawBackground(x, y, sz);
				if (coin[i][j]->getEaten() == false)
				{
					drawCoin((x + sz / 2), (y + sz / 2), sz / 6);
				}
			}

			else if (maze[i][j]->GetValue() == PAC_MAN)
			{
				glColor3d(0, 0, 0);
				drawBackground(x, y, sz);
				glColor3d(1.0, 1.0, 0.0);
				drawPacman((x + sz / 2), (y + sz / 2), sz / 3);
			}

			else if (maze[i][j]->GetValue() == GHOST1)
			{
				glColor3d(0, 0, 0);
				drawBackground(x, y, sz);
				drawGhosts((x + sz / 2), (y + sz / 2), sz / 4.f, ghostColor[0]);
			}
			else if (maze[i][j]->GetValue() == GHOST2)
			{
				glColor3d(0, 0, 0);
				drawBackground(x, y, sz);
				drawGhosts((x + sz / 2), (y + sz / 2), sz / 4.f, ghostColor[1]);
			}
			else if (maze[i][j]->GetValue() == GHOST3)
			{
				glColor3d(0, 0, 0);
				drawBackground(x, y, sz);
				drawGhosts((x + sz / 2), (y + sz / 2), sz / 4.f, ghostColor[2]);
			}
		}
}

void cleanBoard()
{
	int i, j;
	for (i = 1; i < MSZ - 1; i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			int value = maze[i][j]->GetValue();
			if (value == GRAY_PACMAN || value == BLACK_PACMAN || value == GRAY_GHOST || value == BLACK_GHOST)
			{
				maze[i][j]->SetValue(SPACE);
				maze[i][j]->SetG(0);
				maze[i][j]->SetH(maze[i][j]);
				maze[i][j]->SetF();
				maze[i][j]->SetParent(nullptr);
			}

		}
}

//1. pass correct pq into the method (depending on who is activating the method)
void checkDirection(Node* current, Node* next, Node* target, int newG, priority_queue <Node*, vector<Node*>, CompareNodes>& pq)
{
	int value = next->GetValue();

	if (value != WALL)
	{
		if (value != BLACK_GHOST)
		{
			if (value == PAC_MAN || value == SPACE)
			{
				// Add next to PQ only if next was WHITE
				next->SetH(target);
				next->SetG(newG);
				next->SetF();
				value == SPACE ? next->SetValue(GRAY_GHOST) : 0;  //do nothing if target
				next->SetParent(current);
				pq.push(next);
			}
			/*
			else if (down->GetValue() == SPACE || down->GetValue() == COIN)
			{
				//maze[current->GetLine() - 1][current->GetColumn()]->SetValue(GRAY); // paint it gray
				//maze[current->GetLine() - 1][current->GetColumn()]->SetParent(current);
				gray.push_back(down);
				pq1.push(down);
			}
			*/
			//TODO RETHINK THIS
			else // compare it to its actual G
			{
				if (newG < next->getG())
				{
					next->SetG(newG);
					next->SetF();
					next->SetParent(current);
				}
			}
		}
	}
}

void RestorePathInMaze(Node* first, stack <Node*>& path, int origin, priority_queue <Node*, vector<Node*>, CompareNodes>& pq)
{
	Node* current = first;
	while (current->GetValue() != origin)
	{
		// paint it to PATH color
		path.push(current);
		current = current->GetParent();
	}

	Node* down = maze[current->GetLine() - 1][current->GetColumn()];
	Node* up = maze[current->GetLine() + 1][current->GetColumn()];
	Node* left = maze[current->GetLine()][current->GetColumn() - 1];
	Node* right = maze[current->GetLine()][current->GetColumn() + 1];

	if (!path.empty())
	{
		current->SetValue(SPACE);
		current = path.top();
		if (current->GetValue() == PAC_MAN)
			run_AStar = false;
		current->SetValue(origin);
		switch (origin)
		{
		case(GHOST1):
			ghost1 = current;
			break;

		case(GHOST2):
			ghost2 = current;
			break;

		case(GHOST3):
			ghost3 = current;
			break;
		default:
			break;
		}
		if (current == pacman)
			run_AStar = false;
		path.pop();
		Sleep(100);
		display();
	}
	while (!path.empty())
		path.pop();
	while (!pq.empty())
		pq.pop();
	cleanBoard();
	pq.push(current);

}

void pacmanMove(Node* pos)
{
	double x, y, sz;
	sz = 2.0 / MSZ;
	x = pos->GetColumn() * sz - 1;
	y = pos->GetLine() * sz - 1;

	drawPacman((x + sz / 2), (y + sz / 2), sz / 3);
}


void RestorePathInMazePacman(Node* first, int origin, priority_queue <Node*, vector<Node*>, CompareNodesInReverse>& pq)
{

	Node* current = first;

	pacman = current;
	if (pacman == ghost1 || pacman == ghost2 || pacman == ghost3)
	{
		run_AStar = false;
		return;
	}
	pacman->SetValue(PAC_MAN);
	setCoinAtPositionEaten(pacman, true);
	pacmanMove(current);
	Sleep(100);
	display();

	while (!pq.empty())
		pq.pop();

	cleanBoard();
	pq.push(pacman);

}

Node* AStarIteration(Node* target, priority_queue <Node*, vector<Node*>, CompareNodes>& pq, const int ghostValue, stack <Node*>& path)
{
	Node* current;

	//if (pq.empty())
	//{
	//	cout << "Ghost got pacman" << endl;
		//run_AStar = false;
	//	return current;
//	}

	current = pq.top();
	pq.pop();

	Node* down = maze[current->GetLine() - 1][current->GetColumn()];
	Node* up = maze[current->GetLine() + 1][current->GetColumn()];
	Node* left = maze[current->GetLine()][current->GetColumn() - 1];
	Node* right = maze[current->GetLine()][current->GetColumn() + 1];

	if (current->GetValue() == target->GetValue())
	{
		//if(current->GetValue() != ghostValue)
		return current;
	}

	int newG = current->getG() + 1;

	// check all non-black neighbors of current
	checkDirection(current, down, target, newG, pq);
	checkDirection(current, up, target, newG, pq);
	checkDirection(current, left, target, newG, pq);
	checkDirection(current, right, target, newG, pq);

	if (current->GetValue() != ghostValue)
		current->SetValue(BLACK_GHOST);

	return nullptr;
}

//
Node* pacmanFindNearestCoin()
{
	return maze[2][2];
}

//
Node* findNearestGhost()
{
	return monsters.top();
}

Node* pacmanAI()
{
	Node* current;

	current = pq.top();
	pq.pop();

	if (current->GetValue() != PAC_MAN)
		current->SetValue(BLACK_PACMAN);

	while (!monsters.empty())
		monsters.pop();

	calcDistanceToTarget(ghost1, pacman, monsters);
	calcDistanceToTarget(ghost2, pacman, monsters);
	calcDistanceToTarget(ghost3, pacman, monsters);

	Node* ghostPos = findNearestGhost();
	Node* coinPos = pacmanFindNearestCoin();

	int distanceToGhost = current->ManhattanDistance(ghostPos);

	Node* down = maze[current->GetLine() - 1][current->GetColumn()];
	Node* up = maze[current->GetLine() + 1][current->GetColumn()];
	Node* left = maze[current->GetLine()][current->GetColumn() - 1];
	Node* right = maze[current->GetLine()][current->GetColumn() + 1];

	int newG = current->getG() + 1;
	// check all non-black neighbors of current
	calcDistanceFromTarget(down, ghostPos, pq, newG);
	calcDistanceFromTarget(up, ghostPos, pq, newG);
	calcDistanceFromTarget(left, ghostPos, pq, newG);
	calcDistanceFromTarget(right, ghostPos, pq, newG);


	setCoinAtPositionEaten(pacman, true);
	current->SetValue(SPACE);

	Node* tmp;
	do {
		if (!pq.empty())
		{
			tmp = pq.top();
			pq.pop();
		}
		else return nullptr;
	} while (tmp->GetValue() == WALL);

	return tmp;

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawMaze();

	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	if (run_AStar)
	{

		Node* step;
		do
		{
			step = pacmanAI();
		} while (step == nullptr);
		RestorePathInMazePacman(step, PAC_MAN, pq);
		cout << "one step" << endl;

		do
		{
			step = AStarIteration(pacman, pq1, GHOST1, path1);
		} while (step == nullptr);
		RestorePathInMaze(step, path1, GHOST1, pq1);
		cout << "one step" << endl;
		step = nullptr;
		do
		{
			step = AStarIteration(pacman, pq2, GHOST2, path2);
		} while (step == nullptr);
		RestorePathInMaze(step, path2, GHOST2, pq2);
		cout << "one step 2" << endl;
		step = nullptr;
		do
		{
			step = AStarIteration(pacman, pq3, GHOST3, path3);
		} while (step == nullptr);
		RestorePathInMaze(step, path3, GHOST3, pq3);
		cout << "one step 3" << endl;
		step = nullptr;

	}
	//glutPostRedisplay();// calls indirectly to display
}

void Menu(int choice)
{
	try {

	switch (choice) {
	case 1: // ghost AStar
		run_AStar = true;
		break;
	}
	}
	catch (exception e1) {
		// catch block
	}
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("AI Example ");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // idle: when nothing happens

	// menu
	glutCreateMenu(Menu);
	glutAddMenuEntry("Start Game", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	init();

	glutMainLoop();
}