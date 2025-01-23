#include "Game.h"

Game::Game() : window(600, 600, "Tetris")
{
	wasKeyPressed[Key::W] = false;
	wasKeyPressed[Key::A] = false;
	wasKeyPressed[Key::S] = false;
	wasKeyPressed[Key::D] = false;
	wasKeyPressed[Key::Space] = false;
}

void Game::run()
{
	while (window.isOpen()) // Run if window is open
	{
		handleKeyboard();
		update();
		handleWindow();

		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Small delay
	}
}

void Game::handleKeyboard()
{
	// Check current and previous state of key
	if (sf::Keyboard::isKeyPressed(Key::W) && !wasKeyPressed[Key::W])
	{
		wasKeyPressed[Key::W] = true;

		if (currentState == State::PLAY)
		{
			tetris.rotate();
			readyToDraw = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(Key::A) && !wasKeyPressed[Key::A])
	{
		wasKeyPressed[Key::A] = true;

		if (currentState == State::PLAY)
		{
			tetris.moveLeft();
			readyToDraw = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(Key::S) && !wasKeyPressed[Key::S])
	{
		wasKeyPressed[Key::S] = true;

		if (currentState == State::PLAY)
			timePerTick = fasTimePerTick;
	}

	if (sf::Keyboard::isKeyPressed(Key::D) && !wasKeyPressed[Key::D])
	{
		wasKeyPressed[Key::D] = true;

		if (currentState == State::PLAY)
		{
			tetris.moveRight();
			readyToDraw = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(Key::Space) && !wasKeyPressed[Key::Space])
	{
		if (currentState == State::START)
		{
			currentState = State::PLAY;
			readyToDraw = true;
		}

		if (currentState == State::GAME_OVER)
		{
			currentState = State::PLAY;
			tetris = Tetris();
			clock.restart();
			timePerTick = normaltimePerTick;
			readyToDraw = true;
		}

		wasKeyPressed[Key::Space] = true;
	}

	if (!sf::Keyboard::isKeyPressed(Key::W) && wasKeyPressed[Key::W])
		wasKeyPressed[Key::W] = false;

	if (!sf::Keyboard::isKeyPressed(Key::A) && wasKeyPressed[Key::A])
		wasKeyPressed[Key::A] = false;

	if (!sf::Keyboard::isKeyPressed(Key::S) && wasKeyPressed[Key::S])
	{
		wasKeyPressed[Key::S] = false;

		if (currentState == State::PLAY)
			timePerTick = normaltimePerTick;
	}

	if (!sf::Keyboard::isKeyPressed(Key::D) && wasKeyPressed[Key::D])
		wasKeyPressed[Key::D] = false;

	if (!sf::Keyboard::isKeyPressed(Key::Space) && wasKeyPressed[Key::Space])
		wasKeyPressed[Key::Space] = false;
}

void Game::update()
{
	// Check if game is ready to move to GAME OVER state
	if (currentState == State::PLAY && tetris.isGameOver())
	{
		currentState = State::GAME_OVER;
		readyToDraw = true;
	}

	// If timePerTick elapsed then move figure down
	if (currentState == State::PLAY && clock.getElapsedTime().asMilliseconds() >= timePerTick)
	{
		clock.restart();
		tetris.moveDown();
		readyToDraw = true;
	}
}

void Game::handleWindow()
{
	window.handleEvents();

	if (readyToDraw) // Check if there is something new to draw
	{
		window.clear();

		window.drawBackground();
		window.drawBoard(tetris.getBoard());
		window.drawScore(tetris.getScore());

		if (currentState == State::START)
			window.drawStart();

		if (currentState == State::GAME_OVER)
			window.drawGameOver();

		window.drawNextFigure(tetris.getNextFigure());

		window.display();

		readyToDraw = false;
	}
}
