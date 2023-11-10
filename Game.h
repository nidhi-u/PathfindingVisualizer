#pragma once

#include "BFS.h"
#include "Dijkstra.h"
#include "AStar.h"

class Game
{
private:
	int numRows;
	int numCols;
	int cellSize;

	int windowWidth;
	int windowHeight;
	sf::RenderWindow window;

	vector<vector<Node>> grid;
	Node* start;
	Node* end;

	vector<Node*> path;

	sf::Font font;
	sf::RectangleShape guiBackground;

	sf::RectangleShape generateMapButton;
	sf::Text generateMapButtonText;

	sf::RectangleShape BFSButton;
	sf::Text BFSButtonText;
	sf::Text BFSTimeText;

	sf::RectangleShape DijkstraButton;
	sf::Text DijkstraButtonText;
	sf::Text DijkstraTimeText;

	sf::RectangleShape aStarButton;
	sf::Text aStarButtonText;
	sf::Text aStarTimeText;

	sf::Text legendText;
	sf::RectangleShape green;
	sf::RectangleShape red;
	sf::RectangleShape cyan;
	sf::RectangleShape blue;

public:
	Game();
	vector<vector<Node>> createGrid();
	void initGridWindow();
	void initGUI();
	void setRandomWalls();
	void clearGrid(bool clearWalls);
	void runGame();
	void visualizeGrid();
	void drawGUI();
	void render();
};

