#include "Game.h"

Game::Game()
{
	// Initializing grid and sfml window
	initGridWindow();

	// Initializing GUI elements
	initGUI();

	// Running the application
	runGame();
}



vector<vector<Node>> Game::createGrid()
{
	// Creating an empty grid and initializing it with nodes
	vector<vector<Node>> grid(numRows, vector<Node>(numCols));
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			grid[i][j] = Node(i, j);
		}
	}
	return grid;
}

void Game::initGridWindow()
{
	// Defining the grid and window dimensions
	numRows = 30;
	numCols = 30;
	cellSize = 25;
	windowWidth = numCols * cellSize;
	windowHeight = numRows * cellSize;

	// Creating the window
	window.create(sf::VideoMode(windowWidth + 500, windowHeight), "Pathfinding Visualizer");

	// Creating a grid and setting start and end nodes.
	grid = createGrid();

	start = &grid[0][0];
	end = &grid[numRows - 1][numCols - 1];
	start->isWall = false;
	start->isStart = true;
	end->isWall = false;
	end->isEnd = true;
	
}

void Game::initGUI()
{
	// Loading font for text
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "ERROR::GAME::Font not found." << "\n";
	}
	
	// Creating a white background for the UI 
	guiBackground.setSize(sf::Vector2f(400, 698));
	guiBackground.setPosition(800, 28);
	guiBackground.setFillColor(sf::Color::White);

	int x_pos = 850;
	int y_pos = 80;
	
	// Initialzing the buttons and the texts associated with them
	// Generate Map Button and Text
	generateMapButton.setSize(sf::Vector2f(300, 40));
	generateMapButton.setPosition(x_pos, y_pos);
	generateMapButton.setFillColor(sf::Color::Yellow);
	generateMapButton.setOutlineThickness(3);
	generateMapButton.setOutlineColor(sf::Color::Black);

	generateMapButtonText.setFont(font);
	generateMapButtonText.setString("Generate Map");
	generateMapButtonText.setFillColor(sf::Color::Black);
	generateMapButtonText.setPosition(x_pos + 70, y_pos + 5);
	generateMapButtonText.setCharacterSize(24);

	y_pos += 100;

	// BFS Algorithm Button, Text and Execution Time Text
	BFSButton = generateMapButton;
	BFSButton.setPosition(x_pos, y_pos);

	BFSButtonText = generateMapButtonText;
	BFSButtonText.setPosition(x_pos + 70, y_pos + 5);
	BFSButtonText.setString("BFS Algorithm");

	BFSTimeText = generateMapButtonText;
	BFSTimeText.setPosition(x_pos, y_pos + 50);
	BFSTimeText.setString("Execution Time:  \nPath Length: ");
	BFSTimeText.setCharacterSize(18);

	y_pos += 120;

	// Dijkstra's Algorithm Button, Text and Execution Time Text
	DijkstraButton = BFSButton;
	DijkstraButton.setPosition(x_pos, y_pos);

	DijkstraButtonText = BFSButtonText;
	DijkstraButtonText.setPosition(x_pos + 50, y_pos + 5);
	DijkstraButtonText.setString("Dijkstra's Algorithm");

	DijkstraTimeText = BFSTimeText;
	DijkstraTimeText.setPosition(x_pos, y_pos + 50);

	y_pos += 120;

	// A* Algorithm Button, Text and Execution Time Text
	aStarButton = BFSButton;
	aStarButton.setPosition(x_pos, y_pos);

	aStarButtonText = BFSButtonText;
	aStarButtonText.setPosition(x_pos + 80, y_pos + 5);
	aStarButtonText.setString("A* Algorithm");

	aStarTimeText = BFSTimeText;
	aStarTimeText.setPosition(x_pos, y_pos + 50);

	y_pos += 150;

	// Initializing the legend to explain what each color represents in a cell
	// Green -> Start node; Red -> End node; Cyan -> Visited Nodes; Blue -> Path 
	legendText = BFSTimeText;
	legendText.setPosition(x_pos, y_pos);
	legendText.setString("Legend: \n\n\t\tStart Node \t\t\t\t\tEnd Node \n\n\t\tVisited Nodes \t\t\t   Path");

	y_pos += 42;

	green.setPosition(x_pos, y_pos);
	green.setFillColor(sf::Color::Green);
	green.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
	green.setOutlineColor(sf::Color::Black);
	green.setOutlineThickness(2);

	red = green;
	red.setPosition(x_pos + 185, y_pos);
	red.setFillColor(sf::Color::Red);

	y_pos += 42;

	cyan = green;
	cyan.setPosition(x_pos, y_pos);
	cyan.setFillColor(sf::Color::Cyan);

	blue = green;
	blue.setPosition(x_pos + 185, y_pos);
	blue.setFillColor(sf::Color::Blue);
	
}

void Game::setRandomWalls()
{
	// Randomly setting walls on the grid
	for (int i = 0; i < 250; ++i) {
		int x = rand() % numRows;
		int y = rand() % numCols;
		if (!grid[x][y].isStart && !grid[x][y].isEnd)
		{
			grid[x][y].isWall = true;
		}
	}
}

void Game::clearGrid(bool clearWalls)
{
	// Resetting all the values of the nodes in the grid
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			grid[i][j].isVisited = false;
			grid[i][j].isPath = false;
			grid[i][j].g = 999;
			grid[i][j].h = 0;
			grid[i][j].f = 0;

			if (clearWalls)
			{
				// Clearing old walls when new map is generated
				grid[i][j].isWall = false;
			}
		}
	}
}


void Game::runGame()
{
	srand(static_cast<unsigned>(time(0)));

	// Generating a random map
	setRandomWalls();
	
	BFS bfs;
	Dijkstra dijkstra;
	AStar aStar;

	bool isButtonPressed;
	bool changeWalls;

	// Getting the bounds of the buttons
	sf::FloatRect generateMapButtonBounds = generateMapButton.getGlobalBounds();
	sf::FloatRect BFSButtonBounds = BFSButton.getGlobalBounds();
	sf::FloatRect DijkstraButtonBounds = DijkstraButton.getGlobalBounds();
	sf::FloatRect aStarButtonBounds = aStarButton.getGlobalBounds();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					// Checking if user clicked on the generate map button
					if (generateMapButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
						isButtonPressed = true;
						generateMapButton.setFillColor(sf::Color::Green);

						changeWalls = true;
						clearGrid(changeWalls);

						setRandomWalls();

						// Resetting the execution times when map is changed
						BFSTimeText.setString("Execution Time: \nPath Length: ");
						DijkstraTimeText.setString("Execution Time:  \nPath Length: ");
						aStarTimeText.setString("Execution Time:  \nPath Length: ");

					}
					// Checking if user clicked on the BFS algorithm button
					else if (BFSButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
						isButtonPressed = true;
						BFSButton.setFillColor(sf::Color::Green);

						changeWalls = false;
						clearGrid(changeWalls);

						// Starting the timer and running the selected algorithm
						auto startTime = chrono::high_resolution_clock::now();
						path = bfs.runBFSAlgorithm(numRows, numCols, grid, start, end);
						auto endTime = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

						// Setting the execution time string 
						BFSTimeText.setString("Execution Time: " + std::to_string(duration.count()) + " microseconds" + "\nPath Length: " + to_string(path.size()) + " cells");

					}
					// Checking if user clicked on the Dijkstra's algorithm button
					else if (DijkstraButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
						isButtonPressed = true;
						DijkstraButton.setFillColor(sf::Color::Green);

						changeWalls = false;
						clearGrid(changeWalls);

						// Starting the timer and running the selected algorithm
						auto startTime = chrono::high_resolution_clock::now();
						path = dijkstra.runDijkstraAlgorithm(numRows, numCols, grid, start, end);
						auto endTime = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

						// Setting the execution time string 
						DijkstraTimeText.setString("Execution Time: " + std::to_string(duration.count()) + " microseconds" + "\nPath Length: " + to_string(path.size()) + " cells");

					}
					// Checking if user clicked on the A* algorithm button
					else if (aStarButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
						isButtonPressed = true;
						aStarButton.setFillColor(sf::Color::Green);

						changeWalls = false;
						clearGrid(changeWalls);
						
						// Starting the timer and running the selected algorithm
						auto startTime = chrono::high_resolution_clock::now();
						path = aStar.runAStarAlgorithm(numRows, numCols, grid, start, end);
						auto endTime = chrono::high_resolution_clock::now();
						auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

						// Setting the execution time string 
						aStarTimeText.setString("Execution Time: " + to_string(duration.count()) + " microseconds" + "\nPath Length: " + to_string(path.size()) + " cells");

					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					isButtonPressed = false;

					generateMapButton.setFillColor(sf::Color::Yellow);
					BFSButton.setFillColor(sf::Color::Yellow);
					aStarButton.setFillColor(sf::Color::Yellow);
					DijkstraButton.setFillColor(sf::Color::Yellow);
				}
			}
		}

		render();
	}
}

void Game::visualizeGrid()
{
	// Visualizing the grid, setting cell color based on node parameters
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			sf::RectangleShape cellRect(sf::Vector2f(cellSize - 2, cellSize - 2));
			cellRect.setPosition(j * cellSize, i * cellSize);
			if (grid[i][j].isWall) {
				cellRect.setFillColor(sf::Color::Black);
			}
			else if (grid[i][j].isStart) {
				cellRect.setFillColor(sf::Color::Green);
			}
			else if (grid[i][j].isEnd) {
				cellRect.setFillColor(sf::Color::Red);
			}
			else if (grid[i][j].isPath) {
				cellRect.setFillColor(sf::Color::Blue);
			}
			else if (grid[i][j].isVisited) {
				cellRect.setFillColor(sf::Color::Cyan);
			}
			else {
				cellRect.setFillColor(sf::Color::White);
			}
			// Drawing the cell on the window
			window.draw(cellRect);

		}
	}
	
}

void Game::drawGUI()
{
	// Drawing the UI elements on the window
	window.draw(guiBackground);

	window.draw(generateMapButton);
	window.draw(generateMapButtonText);

	window.draw(BFSButton);
	window.draw(BFSButtonText);
	window.draw(BFSTimeText);

	window.draw(DijkstraButton);
	window.draw(DijkstraButtonText);
	window.draw(DijkstraTimeText);

	window.draw(aStarButton);
	window.draw(aStarButtonText);
	window.draw(aStarTimeText);

	window.draw(legendText);
	window.draw(green);
	window.draw(red);
	window.draw(cyan);
	window.draw(blue);

}


void Game::render()
{
	// Clearing the window
	window.clear();

	// Drawing the UI
	drawGUI();

	// Drawing the grid
	visualizeGrid();

	// Rendering everything
	window.display();
}


