#pragma once

#include <SFML\Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
class Player
{
	sf::CircleShape head;
	sf::Color color;
	static const float basicSize;
	static const float basicSpeed;
	int id;
	int points;
	float speedMod;
	bool bodyOff;
	bool wrongDirection;
	

	void changeRadius(float );
	const void changeSpeed(const float multiple);
public:
	Player(sf::Vector2f startPos, int rotation, sf::Color m_color, int m_id);
	~Player();
	void move();
	void test();
	float getHeadSize();
	const sf::Color getColor() const;
	const sf::Vector2f getPossition() const ;
	const float getRadius() const;
	const float getRotation() const;
	friend class Board;
	friend class Effect;
};

