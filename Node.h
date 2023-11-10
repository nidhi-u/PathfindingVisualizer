#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>h
#include <chrono>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

// Each node represents a cell on the grid
class Node
{
public:
    int x, y; // Represents position of cell in grid[row][col]
    bool isWall;
    bool isVisited;
    bool isStart;
    bool isEnd;
    bool isPath;
    Node* parent;
    int g; // Cost from start node
    int h; // Heuristic (Manhattan distance to end node)
    int f; // Total cost (g + h)

    Node(); 
    Node(int x, int y); 

};

