#pragma once
//Specjalnie dla Mateusza
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cmath>
class Laser
{
	static const float basicSpeed;
	sf::CircleShape elipse;
public:
	Laser();
	Laser(std::vector<Player>::iterator &itr);
	~Laser();
	void move();
	friend class Effect;
	friend class Board;
};

