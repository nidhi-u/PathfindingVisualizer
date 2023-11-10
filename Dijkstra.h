#pragma once

#include "Node.h"

class Dijkstra
{
public:
	struct compareNodes { bool operator()(const Node* a, const Node* b) const; };
	vector<Node*> runDijkstraAlgorithm(int numRows, int numCols, vector<vector<Node>>& grid, Node* start, Node* end);
};

