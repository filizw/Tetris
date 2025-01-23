#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "Tetris.h"

class GameWindow
{
public:
	/*
	* Constructor
	* 
	* INPUT: width, height and title of window
	*/
	GameWindow(unsigned int width, unsigned int height, const std::string& title);

	/*
	* Returns width of window
	*
	* OUTPUT: width
	*/
	unsigned int getWidth() const;

	/*
	* Returns height of window
	*
	* OUTPUT: height
	*/
	unsigned int getHeight() const;

	/*
	* Checks if window is open
	* 
	* OUTPUT: true if window is open, false otherwise
	*/
	bool isOpen() const;

	/*
	* Handles window events such as closing
	*/
	void handleEvents();

	/*
	* Clears window
	*/
	void clear();

	/*
	* Draws background
	*/
	void drawBackground();

	/*
	* Draws given board
	* 
	* INPUT: reference to board
	*/
	void drawBoard(const Board& board);

	/*
	* Draws given figure on side panel
	* 
	* INPUT: reference to next figure
	*/
	void drawNextFigure(const Figure& figure);

	/*
	* Prints score on side panel
	* 
	* INPUT: score
	*/
	void drawScore(unsigned int score);

	/*
	* Prints start communicate on side panel
	*/
	void drawStart();

	/*
	* Prints game over communicate on side panel
	*/
	void drawGameOver();

	/*
	* Displays buffered screen
	*/
	void display();

private:
	unsigned int width{};
	unsigned int height{};
	float blockSize{}; // Size of one block to be displayed
	sf::RenderWindow window;
	sf::Font font; // Font used for drawing text

	/*
	* Maps symbolic color to SFML color
	* 
	* INPUT: symbolic color
	* 
	* OUTPUT: SFML color
	*/
	sf::Color getColor(BlockColor color) const;
};