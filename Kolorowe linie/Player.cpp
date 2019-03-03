#include "stdafx.h"
#include "Player.h"
// SOme static const 
const float Player::basicSize = 3.0;
const float Player::basicSpeed = 2;
static const double PI = 3.14159265359;
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
	head.move(sf::Vector2f(cos(head.getRotation()*PI / 180) * basicSpeed * speedMod, sin(head.getRotation()*PI / 180) * basicSpeed * speedMod));
}

float Player::getHeadSize()
{
	return head.getRadius();
}

const sf::Color Player::getColor() const
{
	return color;
}

const sf::Vector2f Player::getPossition() const
{
	return this->head.getPosition();
}

const float Player::getRadius() const
{
	return head.getRadius();
}

const float Player::getRotation() const
{
	return head.getRotation();
}

void Player::changeRadius(float multiple)
{
	if (multiple * this->getRadius()<= 0)
		return;
	head.setRadius(basicSize * multiple);
	head.setOrigin(head.getRadius() , head.getRadius() );
}

const void Player::changeSpeed(const float multiple)
{
	if (multiple  * speedMod >= 0.3)
		speedMod = multiple;
}
