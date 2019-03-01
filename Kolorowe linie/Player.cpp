#include "stdafx.h"
#include "Player.h"
// SOme static const 
const float Player::basicSize = 3.0;
const float Player::basicSpeed = 1.5;
static const double pi = 3.14159265359;
//Basic constructor 
Player::Player(sf::Vector2f startPos, int rotation, sf::Color m_color, int m_id) :
	color(m_color)
{
	speedMod = 1;
	head.setPosition(startPos);
	head.setRadius(basicSize);
	head.setFillColor(color);
	head.setOrigin(basicSize * 1, basicSize * 1);
	head.setRotation(rotation);
	id = m_id;
	bodyOff = false;
	wrongDirection = false;

}

Player::~Player()
{
}
void Player::move()
{
	head.move(sf::Vector2f(cos(head.getRotation()*pi / 180) * basicSpeed * speedMod, sin(head.getRotation()*pi / 180) * basicSpeed * speedMod));
}


void Player::test() {
	// I dont know why i create this...
}

float Player::getHeadSize()
{
	return head.getRadius();
}

inline const sf::Color Player::getColor() const
{
	return color;
}

const sf::Vector2f Player::getPossition() const
{
	return this->getPossition();
}

const float Player::getRadius() const
{
	return head.getRadius();
}

void Player::changeRadius(unsigned int multiple)
{
	head.setRadius(basicSize * multiple);
}

const void Player::changeSpeed(const float multiple)
{
	if (multiple > 0)
		speedMod = multiple;
}
