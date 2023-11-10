#include "AStar.h"

// Comparing nodes
bool AStar::compareNodes::operator()(const Node* a, const Node* b) const
{
    return a->f > b->f; // Using f value for comparison where f = g + h
}

// Calculating the Manhattan distance heuristic
int AStar::calculateManhattanDistance(Node* a, Node* b)
{
    return abs(a->x - b->x) + abs(a->y - b->y);
}

// A* algorithm
vector<Node*> AStar::runAStarAlgorithm(int numRows, int numCols, vector<vector<Node>>& grid, Node* start, Node* end)
{
    vector<Node*> path;

    start->g = 0;

    // Creating a priority queue for nodes to visit
    priority_queue<Node*, vector<Node*>, compareNodes > pq;
    pq.push(start);


    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (current == end) {
            // Path found - reconstruct and return
            while (current) {
                current->isPath = true;
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());

            return path;
        }

        // Marking node as visisted
        current->isVisited = true;

        // Defining movement directions {up, down, left, right}
        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };

        // Exploring neighbors
        for (int i = 0; i < 4; ++i) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            // Checking if new (x,y) are in grid bounds
            if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
                Node* neighbor = &grid[newX][newY];

                // Checking if the neighbor is a wall or has already been visited
                if (!neighbor->isWall && !neighbor->isVisited) {

                    int temp_g = current->g + 1;    // Calculating tentative distance from start node

                    if (temp_g < neighbor->g || !neighbor->isVisited) 
                    {
                        // Updating cost, total cost and parent when shorter path is found
                        neighbor->g = temp_g;
                        neighbor->h = calculateManhattanDistance(neighbor, end);
                        neighbor->f = neighbor->g + neighbor->h;
                        neighbor->parent = current;
                        pq.push(neighbor);
                    }
                }
            }
        }
    }

    return path;
}

