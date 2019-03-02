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
	case 1: color = sf::Color(252, 216, 245); break;	//pink
	case 2: color = sf::Color::Yellow;		break;
	case 3: color = sf::Color::Cyan;		break;
	case 4: color = sf::Color::Green;		break;
	case 5: color = sf::Color(252, 12, 93);break;		//light red
	case 6: color = sf::Color(106, 34, 129); break;		//purple
	default:
		color = sf::Color::Black;
		break;
	}
	return color;
}
