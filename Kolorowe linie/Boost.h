#pragma once
#include <SFML/Graphics.hpp>
class Boost
{
	sf::Texture texture;
	sf::CircleShape sprite;
	sf::Vector2f pos;
	unsigned int myID;
public:
	enum type {
		slowDown = 0, speedUp = 1, noBody = 2, wrongDirection = 3, sizeUp = 4, sizeDown = 5
	};

	Boost(const int, sf::Vector2f);
	~Boost();
	sf::Color getColorByID(const unsigned int);
	friend class  Board;
};