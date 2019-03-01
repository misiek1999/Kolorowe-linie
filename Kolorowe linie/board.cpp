#include "stdafx.h"
#include "board.h"
#include <iostream>
// Some static const 
static const int  ROTATE = 4;

//Main constructor
//
Board::Board(sf::Vector2u m_size):
	sizeBoard(m_size)
{
	std::srand(time(nullptr));
	//First all players = 2
	numberOfPlayers = 2;
	//Player ID
	int i = 0;
	//temp
	players.push_back(Player(randomPosition(),rand() % 360, sf::Color::Red,i++));
	players.push_back(Player(randomPosition(),rand() % 360 ,sf::Color::Blue,i++));
	
	//Now we create our background
	imageOfBoard.create(1000,1000, sf::Color::Black);

	//And finaly we start our clock
	StartTime = std::chrono::system_clock::now();
	tick = 0;
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
		float radius = (itr->getRadius());
		if (posX <(0 + radius) || posY <(0 + radius) || posX >(sizeBoard.x + radius) || posY >(sizeBoard.y + radius))
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

	//PickUp booster
	for (auto plr = players.begin(); plr!=players.end(); plr++)
		for (auto bos = boosters.begin(); bos!= boosters.end(); )
		{
			//Colision
			if (plr->head.getGlobalBounds().intersects(bos->sprite.getGlobalBounds()))
			{
				effects.push_back(Effect(plr, bos->myID, tick));
				bos = boosters.erase(bos);
			}
			else
				bos++;
		}
	//New boosters
	if (boosters.size() < MAX_ELEMENTS && tick % 10 == 0)
	{
		
		int random = rand() % 100;
		// To jest na chwile
		/*
		switch (random)
		{
		case Boost::type::slowDown:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		case Boost::type::speedUp:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		case Boost::type::noBody:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		case Boost::type::wrongDirection:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		case Boost::type::sizeUp:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		case Boost::type::sizeDown:
			boosters.push_back(Boost(random, randomPosition()));
			break;
		default:
			break;
		}
		*/
		boosters.push_back(Boost(random, randomPosition()));
	}
	//End of boosters
	for (auto eff= effects.begin(); eff!=effects.end(); )
		if (eff->endOfEffect(tick))
		{
			auto itr = players.begin();
			itr += eff->getPlayerID();
			eff->remove(itr);
			eff = effects.erase(eff);
		}
		else
			eff++;
	tick++;
}


using std::pow;
void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (tick % 100 <80 )
	for (auto itr : players)
	{
		if (itr.bodyOff == false)
		{
			float posX = itr.head.getPosition().x;
			float posY = itr.head.getPosition().y;
			float radius = itr.head.getRadius();
			//Now some drawing pixel
			for (float x = posX - radius; x != posX + radius; x++)
				for (float y = posY - radius; y != posY + radius; y++)
					if (x > 0 && y > 0)		//Exception 
						if ((pow(x - posX, 2) * pow(y - posY, 2)) <= pow(radius, 2))
							this->imageOfBoard.setPixel(x, y, itr.head.getFillColor());
		}
	}

	textureOfBoard.loadFromImage(imageOfBoard);
	spiriteOfBoard.setTexture(textureOfBoard, true);
	target.draw(spiriteOfBoard);
	//draw all heads
	for (auto itr : players)
		target.draw(itr.head);

	for (auto itr : boosters)
	{
		target.draw(itr.sprite);
	}
}

void Board::turnLeft()
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->wrongDirection == true)
			mod *= -1;
			if (itr->id == 0)
				itr->head.rotate(-ROTATE);
	}
}
void Board::turnRight()
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->wrongDirection == true)
			mod *= -1;
		if (itr->id == 0)
			itr->head.rotate(ROTATE);
	}
}

void Board::turnLeft2()
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->wrongDirection == true)
			mod *= -1;
		if (itr->id == 1)
			itr->head.rotate(-ROTATE);
	}
}

void Board::turnRight2()
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->wrongDirection == true)
			mod *= -1;
		if (itr->id == 1)
			itr->head.rotate(ROTATE);
	}
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
	if (posX > 0 && posY > 0 && posX < sizeBoard.x && posY < sizeBoard.y)
		if (sf::Color::Black != imageOfBoard.getPixel(posX, posY))
			return true;
	return false;
}

bool Board::gameOver()
{
	return !(players.size() - 1);
}

sf::Vector2f Board::randomPosition()
{
	int x = int(rand()) %(int)sizeBoard.x;
	int y = int(rand()) %(int)sizeBoard.y;
	return sf::Vector2f(x,y);
}


