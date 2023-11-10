#pragma once

#include "Node.h"

class BFS
{
public:
	vector<Node*> runBFSAlgorithm(int numRows, int numCols, vector<vector<Node>>& grid, Node* start, Node* end);
};

