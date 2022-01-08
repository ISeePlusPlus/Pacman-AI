#pragma once
#include "Node.h"
#include <vector>
#include <queue>
#include "CompareNodes.h"
#include <iostream>

using namespace std;

class Ghost: public Node
{
private:
	priority_queue <Node*, vector<Node*>, CompareNodes> pq;

public:
	//bool AStarIteration(Node* target);

};