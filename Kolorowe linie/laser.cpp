#include "stdafx.h"
#include "laser.h"
const float Laser::basicSpeed = 6;
static const double PI = 3.14159265359;

Laser::Laser(std::vector<Player>::iterator &itr)
{
	elipse.setFillColor(itr->getColor());
	elipse.setScale(2, 1);
	elipse.setRadius(5);
	elipse.setOrigin(10, 10);
	elipse.setPosition(itr->getPossition());
	elipse.setRotation(itr->getRotation());
}

Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::move()
{
	elipse.move(sf::Vector2f(std::cos(elipse.getRotation()*PI / 180) * 10 , std::sin(elipse.getRotation()*PI / 180) * 10 ));
}
