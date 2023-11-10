#include "BFS.h"

// BFS algorithm
vector<Node*> BFS::runBFSAlgorithm(int numRows, int numCols, vector<vector<Node>>& grid, Node* start, Node* end)
{
    vector<Node*> path;

    // Creating a queue for nodes to visit
    queue<Node*> q;
    q.push(start);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

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
            int newRow = current->x + dx[i];
            int newCol = current->y + dy[i];

            // Checking if new (x,y) are in grid bounds
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                Node* neighbor = &grid[newRow][newCol];

                // Checking if the neighbor is a wall or has already been visited
                if (!neighbor->isWall && !neighbor->isVisited) {

                    // Updating cost and parent
                    q.push(neighbor);
                    neighbor->isVisited = true;
                    neighbor->parent = current;
                }
            }
        }
    }

    return path;
}
