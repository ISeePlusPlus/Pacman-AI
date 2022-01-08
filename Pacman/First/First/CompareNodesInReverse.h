#pragma once
#include "Node.h"
class CompareNodesInReverse
{
public:
	CompareNodesInReverse() {}
	~CompareNodesInReverse() {}

	bool operator () (Node* pn1, Node* pn2)
	{
			return pn1->GetF() < pn2->GetF();
	}

};