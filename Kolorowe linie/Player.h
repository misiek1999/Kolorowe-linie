#pragma once

#include <SFML\Graphics.hpp>
#include <cmath>

class Player
{
	sf::CircleShape head;
	sf::Color color;
	static const float basicSize;
	static const float basicSpeed;
	static int curretID;
	int id;
	int points;
	float speedMod;
public:
	Player(sf::Vector2f startPos, sf::Color m_color);
	~Player();
	void move();
	void test();
	float getHeadSize();
	const sf::Color getColor() const;
	const sf::Vector2f getPossition() const ;
	friend class Board;

};

