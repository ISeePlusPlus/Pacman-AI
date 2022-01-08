#include "Ghost.h"

/*
bool Ghost::AStarIteration(Node* target)
{
	Node* current, * next;

	if (pq.empty())
	{
		cout << "There is no path" << endl;
		return false;
	}

	current = pq.top();
	pq.pop();

	if (current->GetValue() == target->GetValue())
	{
		cout << "Target was found" << endl;
		 return false;
		//RestorePathInGraph(current->GetParent(), START);
		//return;
	}

	current->SetValue(BLACK);

	int newG = current->getG() + 1;
	// check all non-black neighbors of current
	for (auto it : current->GetOutgoing())
	{
		// next is the Node that is the secondend of edge it
		next = graph.GetNode(it->GetSecond());
		int value = next->GetValue();
		if (value != BLACK)
		{
			// update G of next
			if (value == SPACE || // white target
				(value == TARGET))
			{
				// Add next  to PQ only if next was WHITE
				next->SetH(graph.GetNode(graph.GetNodes().size() - 1));
				next->SetG(newG);
				next->SetF();
				value == SPACE ? next->SetValue(GRAY) : 0;  //do nothing if target
				next->SetParent(current);
				pq.push(next);
			}

			else // compare it to its actual G
			{
				if (newG < next->GetG())
				{
					next->SetG(newG);
					next->SetF();
					next->SetParent(current);


				}
			}
		}

	}
}
*/
