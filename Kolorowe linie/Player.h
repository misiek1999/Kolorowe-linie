#pragma once

#include <SFML\Graphics.hpp>
#include <cmath>

class Player
{
	sf::CircleShape head;
	sf::Color color;
	static const float basicSize;
	static const float basicSpeed;
	float speedMod;
public:
	Player(sf::Vector2f startPos, sf::Color m_color);
	~Player();
	void move();
	void test();
	friend class Board;
};

