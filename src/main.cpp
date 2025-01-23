#include "Game.h"
#include <iostream>
#include <conio.h>

static void draw(const Tetris& tetris)
{
	std::cout << "Score: " << tetris.getScore();

	if (tetris.isGameOver())
		std::cout << "\tGAME OVER!";

	std::cout << "\n@@@@@@@@@@@@\n";

	for (const auto& row : tetris.getBoard().getBlockMatrix())
	{
		std::cout << '@';

		for (const auto& elem : row)
			std::cout << (char)elem;

		std::cout << "@\n";
	}

	std::cout << "@@@@@@@@@@@@\n";
}

int main()
{
	Game game;
	game.run();
}
