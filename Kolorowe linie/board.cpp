#include "stdafx.h"
#include "board.h"
#include <iostream>
// Some static const 
const float Board::wallSize = 6;
static const int  ROTATE = 4;
//Main constructor
//
Board::Board(sf::Vector2u m_size):
	sizeBoard(m_size)
{
	//First all players = 2
	numberOfPlayers = 2;
	players.push_back(Player(sf::Vector2f(100, 100), sf::Color::Red));
	players.push_back(Player(sf::Vector2f(200, 200), sf::Color::Blue));
	
	//Now we create our background
	imageOfBoard.create(640, 480, sf::Color::Black);

}


Board::~Board()
{
	players.clear();
}
// Its basic funtion in our game
void Board::go()
{
	for (auto itr = players.begin(); itr != players.end(); itr++)
		itr->move();


	// When player out of board 
	for (auto itr = players.begin(); itr != players.end(); )
	{
		float posX = itr->head.getPosition().x;
		float posY = itr->head.getPosition().y;
		if (posX < 0 || posY < 0 || posX > sizeBoard.x || posY > sizeBoard.y)
			itr = players.erase(itr);
		else			
			itr++;
		
	}
	//Colision with other player
	for (auto itr = players.begin(); itr != players.end(); )
		if (this->collisionWithOtherPlayers(itr))
			itr = players.erase(itr);
		else
			itr++;
}

using std::pow;
void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw all heads
	for ( auto itr : players)
		target.draw(itr.head);

	for (auto itr : players)
	{
		float posX = itr.head.getPosition().x;
		float posY = itr.head.getPosition().y;
		float radius = itr.head.getRadius();
		//Now some drawing pixel
		for (float x = posX - radius; x != posX + radius ; x++)
			for (float y = posY - radius; y != posY + radius ; y++)
				if (x > 0 && y > 0)		//Exception 
					if ((pow(x - posX, 2) * pow(y - posY, 2)) <= pow(radius, 2))
						this->imageOfBoard.setPixel(x, y, itr.head.getFillColor());

	}
	textureOfBoard.loadFromImage(imageOfBoard);
	spiriteOfBoard.setTexture(textureOfBoard, true);
	target.draw(spiriteOfBoard);
//		imageOfBoard.saveToFile("test.bmp");

}

void Board::turnLeft()
{
	for (auto itr : players)
		if (itr.id == 0)
			players.begin()->head.rotate(-ROTATE);
}

void Board::turnRight()
{
	for (auto itr : players)
		if (itr.id == 0)
			players.begin()->head.rotate(ROTATE);
}

//Now we test colision with other players
using std::cos;
using std::sin;
static const double pi = 3.14159265359;
bool Board::collisionWithOtherPlayers(std::vector<Player>::iterator &itr)
{
	float radius = itr->head.getRadius();
	float x = itr->head.getPosition().x;
	float y = itr->head.getPosition().y;
	float posX = (cos(itr->head.getRotation()*pi / 180) * radius) + x ;
	float posY = (sin(itr->head.getRotation()*pi / 180)  *radius) + y ;
	if (sf::Color::Black != imageOfBoard.getPixel(posX, posY))
		return true;
	return false;
}



