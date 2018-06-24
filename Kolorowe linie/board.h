#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Player.h"
//Board where players fights 
class Board : public sf::Drawable
{
	sf::Vector2f sizeBoard;
	static const float wallSize;
	int numberOfPlayers;
	std::vector <Player> players;

public:
	Board(sf::Vector2u m_size);
	~Board();
	//I know its terrible mechanic...
	void go();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void turnLeft();
	void turnRight();
	void test(sf::Image &obrazek);

};

