#include "Node.h"


Node::Node()
{
	x = 0;
	y = 0;
	isWall = false;
	isVisited = false;
	isStart = false;
	isEnd = false;
	isPath = false;
	parent = nullptr;
	g = 999;
	h = 0;
	f = 0;

}

Node::Node(int x, int y)
{
	this->x = x;
	this->y = y;
	isWall = false;
	isVisited = false;
	isStart = false;
	isEnd = false;
	isPath = false;
	parent = nullptr;
	g = 999;
	h = 0;
	f = 0;
}


