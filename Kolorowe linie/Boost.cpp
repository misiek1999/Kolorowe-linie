#include "stdafx.h"
#include "Boost.h"


Boost::Boost(const int id, sf::Vector2f pos):
	myID(id)
{
	//sprite.setFillColor(sf::Color(id));

	sprite.setFillColor(getColorByID(myID));
	sprite.setPosition(pos);
	sprite.setRadius(10);
}


Boost::~Boost()
{
}

sf::Color Boost::getColorByID(const unsigned int id)
{
	sf::Color color;
	switch (id)
	{
	case 0: color = sf::Color::White;		break;
	case 1: color = sf::Color::Magenta;		break;
	case 2: color = sf::Color::Yellow;		break;
	case 3: color = sf::Color::Cyan;		break;
	case 4: color = sf::Color::Green;		break;
	case 5: color = sf::Color(188, 160, 169);break;	//light red
	default:
		color = sf::Color::Black;
		break;
	}
	return color;
}
