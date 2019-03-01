#pragma once
// Include some libs 
#include <SFML\Graphics.hpp>
#include "board.h"

class Game
{
	bool nextRound(sf::RenderWindow&, Board);
	sf::VideoMode videoSize;
	sf::Font font;
public:
	Game();
	~Game();
	int run();
};

