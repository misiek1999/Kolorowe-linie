#include "stdafx.h"
#include "Player.h"
// SOme static const 
const float Player::basicSize = 2.0;
const float Player::basicSpeed = 1.5;
static const double pi = 3.14159265359;

//Basic constructor 
Player::Player(sf::Vector2f startPos, sf::Color m_color):
	color(m_color)
{
	head.setPosition(startPos);
	head.setRadius(basicSize);
	head.setFillColor(color);
	head.setOrigin(basicSize * 0.5, basicSize * 0.5);
	head.setRotation(0);
	

}

Player::~Player()
{
}
void Player::move()
{
	head.move(sf::Vector2f(cos(head.getRotation()*pi / 180) * basicSpeed, sin(head.getRotation()*pi / 180) * basicSpeed));
}


void Player::test() {





}