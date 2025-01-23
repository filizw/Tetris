#pragma once

#include "GameWindow.h"
#include <unordered_map>
#include <thread>
#include <chrono>

class Game
{
public:
	/*
	* Default constructor
	* 
	* REMARKS: sets width and height of window to 600
	*/
	Game();

	/*
	* Runs game
	*/
	void run();

private:
	using Key = sf::Keyboard::Key;

	// States game can be in
	enum class State
	{
		START,
		PLAY,
		GAME_OVER
	};

	static const unsigned int normaltimePerTick{ 400 };	// Normal figure falling time
	static const unsigned int fasTimePerTick{ 25 };		// Faster figure falling time, used when appropriate key is pressed

	Tetris tetris;
	GameWindow window;
	State currentState{}; // Current state of game
	sf::Clock clock; // Object used to measure time
	unsigned int timePerTick{ normaltimePerTick }; // Variable containing current figure falling time
	bool readyToDraw{ true }; // Flag indicating if there is something new to draw

	std::unordered_map<Key, bool> wasKeyPressed; // Map containing information about key presses

	/*
	* Handles input from keyboard
	*/
	void handleKeyboard();

	/*
	* Updates current game state and moves figure down every timePerTick
	*/
	void update();

	/*
	* Handles drawing to window
	*/
	void handleWindow();
};
