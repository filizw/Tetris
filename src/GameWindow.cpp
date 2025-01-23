#include "GameWindow.h"

GameWindow::GameWindow(unsigned int width, unsigned int height, const std::string& title) : width(width), height(height),
	blockSize((float)height / 20), window(sf::VideoMode({ width, height }), title), font("font/Arial.ttf")
{
	window.setVerticalSyncEnabled(true);
}

unsigned int GameWindow::getWidth() const
{
	return width;
}

unsigned int GameWindow::getHeight() const
{
	return height;
}

bool GameWindow::isOpen() const
{
	return window.isOpen();
}

void GameWindow::handleEvents()
{
	while (auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
	}
}

void GameWindow::clear()
{
	window.clear(sf::Color::Black); // Clear screen with black color
}

void GameWindow::drawBackground()
{
	// Draw side panel
	sf::RectangleShape rect({ width / 2.0f, height * 1.0f });
	rect.setFillColor(sf::Color(20, 20, 20));
	rect.setPosition({ width / 2.0f, 0.0f });
	window.draw(rect);

	// Draw place for next figure
	rect.setSize({ blockSize,blockSize });
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(-blockSize * 0.02);
	rect.setOutlineColor(sf::Color(20, 20, 20));

	for (unsigned int y{11}; y < 15; y++)
	{
		for (unsigned int x{13}; x < 17; x++)
		{
			rect.setPosition({ x * blockSize, y * blockSize });

			window.draw(rect);
		}
	}
}

void GameWindow::drawBoard(const Board& board)
{
	auto boardWidth = board.getWidth();
	auto boardHeight = board.getHeight();

	sf::RectangleShape rect({ blockSize, blockSize });
	rect.setOutlineThickness(-blockSize * 0.02);
	rect.setOutlineColor(sf::Color(20, 20, 20));

	// Draw each block of board
	for (unsigned int y{}; y < boardHeight; y++)
	{
		for (unsigned int x{}; x < boardWidth; x++)
		{
			rect.setPosition({ x * blockSize,y * blockSize });
			rect.setFillColor(getColor(board.getBlockColor({ (int)x, (int)y })));

			window.draw(rect);
		}
	}
}

void GameWindow::drawNextFigure(const Figure& figure)
{
	sf::RectangleShape rect({ blockSize, blockSize });
	rect.setFillColor(getColor(figure.getColor()));
	rect.setOutlineThickness(-blockSize * 0.02);
	rect.setOutlineColor(sf::Color(20, 20, 20));

	// Draw each block of next figure
	for (const auto& pos : figure.getBlockPositions())
	{
		rect.setPosition({ (pos.x + 10) * blockSize,(pos.y + 12) * blockSize });

		window.draw(rect);
	}
}

void GameWindow::drawScore(unsigned int score)
{
	// Convert score to string
	std::stringstream ss;
	ss << score;

	sf::Text text(font);
	text.setString("Score: " + ss.str());
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(blockSize);
	text.setPosition({ blockSize * 13,blockSize * 1 });
	window.draw(text);
}

void GameWindow::drawStart()
{
	sf::Text text(font);
	text.setString("Press Space to Start");
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(blockSize * 0.8);
	text.setPosition({ blockSize * 11,blockSize * 6 });
	window.draw(text);
}

void GameWindow::drawGameOver()
{
	sf::Text text(font);
	text.setString("GAME OVER!");
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(blockSize * 1.2);
	text.setPosition({ blockSize * 11,blockSize * 4 });
	window.draw(text);

	text.setString("Press Space to Start Again");
	text.setCharacterSize(blockSize * 0.6);
	text.setPosition({ blockSize * 11,blockSize * 6 });
	window.draw(text);
}

void GameWindow::display()
{
	window.display();
}

sf::Color GameWindow::getColor(BlockColor color) const
{
	sf::Color c;

	switch (color)
	{
	case BlockColor::NONE:
		c = sf::Color::Black;
		break;
	case BlockColor::RED:
		c = sf::Color::Red;
		break;
	case BlockColor::GREEN:
		c = sf::Color::Green;
		break;
	case BlockColor::BLUE:
		c = sf::Color::Blue;
		break;
	case BlockColor::YELLOW:
		c = sf::Color::Yellow;
		break;
	case BlockColor::CYAN:
		c = sf::Color::Cyan;
		break;
	case BlockColor::MAGENTA:
		c = sf::Color::Magenta;
		break;
	default:
		break;
	}

	return c;
}
