#include "stdafx.h"
#include "board.h"
#include <iostream>
// Some static const 
static const int  ROTATE = 3;
void Board::addNewEffect(std::vector<Player>::iterator & itr, unsigned int type)
{
	effects.push_back(Effect(itr, type, tick));
	std::sort(effects.begin(), effects.end());
}

void Board::setupWalls()
{
	for (auto &itr : walls)
	{
		itr.setFillColor(sf::Color::Yellow);
	}
	//1
	walls[0].setSize(sf::Vector2f(wallSize, sizeBoard.y));
	//2
	walls[1].setSize(sf::Vector2f(sizeBoard.x, wallSize));
	//3
	walls[2].setSize(sf::Vector2f(wallSize, sizeBoard.y));
	walls[2].setPosition(sf::Vector2f(sizeBoard.x - wallSize, 0));
	//4
	walls[3].setSize(sf::Vector2f(sizeBoard.x, wallSize));
	walls[3].setPosition(sf::Vector2f(0, sizeBoard.y - wallSize));
}

//Main constructor
Board::Board(sf::Vector2u m_size, std::size_t numberOfPlayer_ ):
	sizeBoard(m_size),
	numberOfPlayer(numberOfPlayer_)
{
	std::srand(time(nullptr));

	//Player ID
	//int i = 0;
	//temp
	//players.push_back(Player(randomPosition(),rand() % 360, sf::Color::Red,i++));
	//players.push_back(Player(randomPosition(),rand() % 360 ,sf::Color::Blue,i++));
	for (std::size_t i=0; i< numberOfPlayer_; i++ )
		players.push_back(Player(randomPosition(), rand() % 360, this->getPlayerColorByID(i), i));
	//Now we create our background
	imageOfBoard.create(1000,1000, sf::Color::Black);
	//
	this->setupWalls();
		/*
	wall.setSize(sizeBoard);
	wall.setSize(sf::Vector2f(sizeBoard.x - 2 * wallSize, sizeBoard.y - 2 * wallSize));
	wall.setFillColor(sf::Color::Black);
	//wall.setOutlineColor(sf::Color::Yellow);
	wall.setOutlineThickness(wallSize);
	wall.setPosition(wallSize, wallSize);
	*/
	//And finaly we start our clock //Maybe no
	//StartTime = std::chrono::system_clock::now();
	tick = 0;
}

Board::~Board()
{
	players.clear();
	boosters.clear();
	effects.clear();
}
// Its basic funtion in our game
int Board::go()
{
	//ID of dead player
	int deadPlayerID = -1;

	//move players
	for (auto itr = players.begin(); itr != players.end(); itr++)
		itr->move();

	// Lasers!
	if (Effect::LASER_ON)
	{
		//move lasers...
		for (auto &eff : effects)
		{
			if (eff.getType() == Boost::type::laser)
				eff.laser.move();
		}
		//Laser out of Board
		for (auto itr = effects.begin(); itr != effects.end(); )
		{
			if (itr->getType() == Boost::laser)
			{
				float posX = itr->laser.elipse.getPosition().x;
				float posY = itr->laser.elipse.getPosition().y;
				float radius = (itr->laser.elipse.getRadius());
				if (posX <(0 + radius) || posY <(0 + radius) || posX >(sizeBoard.x + radius) || posY >(sizeBoard.y + radius))
					itr = effects.erase(itr);
				else
					itr++;
			}
			else
				itr++;
		}
	}


	// When player out of board 
	for (auto itr = players.begin(); itr != players.end(); )
	{
		float posX = itr->head.getPosition().x;
		float posY = itr->head.getPosition().y;
		float radius = (itr->getRadius());
		if (posX <(0 + radius) || posY <(0 + radius) || posX >(sizeBoard.x + radius) || posY >(sizeBoard.y + radius)) {
			deadPlayerID = itr->id;
			itr = players.erase(itr);
		}
		else
			itr++;
	}
	if(deadPlayerID==-1)
	//Colision with other player
	for (auto itr = players.begin(); itr != players.end(); )
		if (this->collisionWithOtherPlayers(itr)) {
			deadPlayerID = itr->id;
			itr = players.erase(itr);
		}
		else
			itr++;
	if (deadPlayerID == -1)
	//Colision with laser
	if(Effect::LASER_ON)
		for (auto &eff : effects)
			for (auto itr = players.begin(); itr != players.end(); )
				if (eff.collisionWithLaser(itr)){
					deadPlayerID = itr->id;
					itr = players.erase(itr);
				}
				else
					itr++;
	//PickUp booster
	for (auto plr = players.begin(); plr!=players.end(); plr++)
		for (auto bos = boosters.begin(); bos!= boosters.end(); )
		{
			//Colision
			if (plr->head.getGlobalBounds().intersects(bos->sprite.getGlobalBounds()))
			{
				//effects.push_back(Effect(plr, bos->myID, tick));
				addNewEffect(plr, bos->myID);
				bos = boosters.erase(bos);
			}
			else
				bos++;
		} 

	// Add new boost
	if (boosters.size() < MAX_ELEMENTS && tick % 10 == 0)
	{
		int random =rand() % 70;
		if (random < Boost::numberOfBoost)
				boosters.push_back(Boost(random, randomPosition()));

	}
	//End of boosters
	if (tick%5==0)
	{
		auto eff = effects.begin();
			if (eff != effects.end() && eff->isEnd(tick))
			{
				int playerID = eff->getPlayerID();
				auto itr = players.begin();
				for (; itr != players.end(); itr++)
					if (itr->id == playerID)
						break;
				if (itr == players.end())
					eff = effects.erase(eff);
				else
				{
					eff->remove(itr);
					eff = effects.erase(eff);
				}
			}
	}
	tick++;
	return deadPlayerID;
}


using std::pow;
void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	if (tick % 100 <90 )
	for (auto &itr : players)
	{
		if (itr.bodyOff == false)
		{
			float posX = itr.head.getPosition().x;
			float posY = itr.head.getPosition().y;
			float radius = itr.getRadius();
			//Now some drawing pixel
			for (float x = posX - radius; x != posX + radius; x++)
				for (float y = posY - radius; y != posY + radius; y++)
					if (x > 0 && y > 0)		//Exception 
						if ((pow(x - posX, 2) * pow(y - posY, 2)) <= pow(radius, 2))
							this->imageOfBoard.setPixel(x, y, itr.head.getFillColor());
			/* TOFIX
			for (float x = posX - radius; x != posX + radius; x++)
				for (float y = posY - radius; y != posY + radius; y++)
					if (x > 0 && y > 0)
						this->imageOfBoard.setPixel(x, y, itr.head.getFillColor());
						*/
		}
	}
	//Draw board
	textureOfBoard.loadFromImage(imageOfBoard, sf::IntRect(wallSize, wallSize, sizeBoard.x - 2*wallSize, sizeBoard.y - 2*wallSize));
	textureOfBoard.setSmooth(true);
	spiriteOfBoard.setTexture(textureOfBoard, true);
	spiriteOfBoard.setPosition(wallSize, wallSize);
	target.draw(spiriteOfBoard);



	//draw all heads
	for (const auto &itr : players)
		target.draw(itr.head);
	//draw booster
	for (const auto& itr : boosters)
	{
		target.draw(itr.sprite);
	}
	//draw laser shoot
	for (auto const & itr : effects)
		if (Boost::type::laser == itr.getType() && Effect::LASER_ON == true)
			target.draw(itr.laser.elipse);

	//draw walls
	for (auto const & itr : walls)
		target.draw(itr);
}
/*
void Board::turnLeft()
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->wrongDirection == true)
			mod *= -1;
			if (itr->id == 0)
				itr->head.rotate(-ROTATE * itr->speedMod * mod);
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
			itr->head.rotate(ROTATE* itr->speedMod* mod);
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
			itr->head.rotate(-ROTATE * itr->speedMod* mod);
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
			itr->head.rotate(ROTATE* itr->speedMod* mod);
	}
}
*/
//Now we test colision with other players
using std::cos;
using std::sin;
static const double PI = 3.14159265359;
bool Board::collisionWithOtherPlayers(std::vector<Player>::iterator &itr)
{
	float radius = itr->head.getRadius() + 1;
	float x = itr->head.getPosition().x;
	float y = itr->head.getPosition().y;
	float posX = (cos(itr->head.getRotation()*PI / 180) * radius) + x ;
	float posY = (sin(itr->head.getRotation()*PI / 180) * radius) + y ;
	if (posX > 0 && posY > 0 && posX < sizeBoard.x && posY < sizeBoard.y)
		if (sf::Color::Black != imageOfBoard.getPixel(posX, posY))
			return true;
	return false;
}
//Rebuild this method
int Board::gameOver()
{
	return players.size() <= 1;
}

sf::Vector2f Board::getBoardSize()
{
	return sizeBoard;
}

void Board::changePlayerDirection(std::size_t ID, rotate direction)
{
	int mod = 1;
	for (std::vector<Player>::iterator itr = players.begin(); itr != players.end(); itr++)
	{
		if (itr->id == ID)
		{
			if (itr->wrongDirection == true)
				mod *= -1;
			itr->head.rotate(direction*ROTATE* itr->speedMod* mod);
		}
	}
}

sf::Color Board::getPlayerColorByID(const size_t id) const
{
	switch (id)
	{
	case 0: return sf::Color::Red;
	case 1: return sf::Color::Blue;
	case 2: return sf::Color(165, 94, 251);		//
	case 3: return sf::Color(255, 165, 0);		//Orange
	case 4: return sf::Color(87, 128, 170);		//
	case 5: return sf::Color(255, 255, 240);	//Ivory
	case 6: return sf::Color(87, 0, 0);			//
	case 7: return sf::Color(165, 238, 194);	//Mint
	default:
		break;
	}
	return sf::Color(0,12,0);
}

sf::Vector2f Board::randomPosition()
{
	int x = int(rand()) % ((int)sizeBoard.x - 2 * ( wallSize + distanceFromWall)) + wallSize + distanceFromWall;
	int y = int(rand()) % ((int)sizeBoard.y - 2 * ( wallSize + distanceFromWall)) + wallSize + distanceFromWall;
	return sf::Vector2f(x,y);
}


