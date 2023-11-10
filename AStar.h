#pragma once

#include "Node.h"

class AStar
{
public:
	struct compareNodes { bool operator()(const Node* a, const Node* b) const; };
	int calculateManhattanDistance(Node* a, Node* b);
	vector<Node*> runAStarAlgorithm(int numRows, int numCols, vector<vector<Node>>& grid, Node* start, Node* end);
};

