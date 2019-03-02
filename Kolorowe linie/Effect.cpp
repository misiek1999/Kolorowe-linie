#include "stdafx.h"
#include "Effect.h"
//Flag to disable laser in game


Effect::Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick):
	beginTick(tick)
{
	playerID = itr->id;
	effect = Boost::type(type);
	switch (effect)
	{
	case Boost::type::slowDown:
		itr->changeSpeed(speedDown);
		break;
	case Boost::type::speedUp:
		itr->changeSpeed(speedUp);		
		break;
	case Boost::type::noBody:
		itr->bodyOff = true;
		break;
	case Boost::type::wrongDirection:
		itr->wrongDirection = true;
		break;
	case Boost::type::sizeUp:			
		itr->changeRadius(sizeUp);
		break;
	case Boost::type::sizeDown:
		itr->changeRadius(sizeDown);
		break;
	case Boost::type::laser:
		laser = Laser(itr);
		//Use special constructor
		break;
	default:
		break;
	}
}
/*
Effect::Effect(std::vector<Player>::iterator & itr, unsigned int type, int tick, sf::Vector2f boardSize):
	beginTick(tick)
{
	playerID = itr->id;
	effect = Boost::type(type);
	if (!LASER_ON)
	{
		if (effect == Boost::type::laser)
		{
			laser = Laser(itr, boardSize);
		}
	}
	else
	{
		//TODO

	}
			
}
*/
Effect::Effect(int ID, int tick, Boost::type eff)
{
	playerID = ID;
	this->effect = eff;
	beginTick = tick;
}


Effect::~Effect()
{
}

Effect& Effect::operator=(const Effect & temp)
{
	if (this == &temp)
		return *this;
	playerID = temp.playerID;
	beginTick = temp.beginTick;
	effect = temp.effect;
	return *this; 
}

unsigned int Effect::getPlayerID() const
{
	return playerID;
}

bool Effect::endOfEffect(int curretTick)
{
	if (LASER_ON && effect == Boost::type::laser && curretTick - beginTick > laserTime)
		return true;
	if (curretTick - beginTick < durationTick)
		return false;
	return true;;
}

void Effect::remove(std::vector<Player>::iterator & itr)
{
	switch (effect)
	{
	case Boost::type::slowDown:
		itr->changeSpeed(1);
		break;
	case Boost::type::speedUp:
		itr->changeSpeed(1);
		break;
	case Boost::type::noBody:
		itr->bodyOff = false;
		break;
	case Boost::type::wrongDirection:
		itr->wrongDirection = false;
		break;
	case Boost::type::sizeUp:	
		itr->changeRadius(1);
		break;
	case Boost::type::sizeDown:
		itr->changeRadius(1);
		break;
	default:
		break;
	}
}
bool Effect::collisionWithLaser(std::vector<Player>::iterator & itr)
{
	if (!Effect::LASER_ON)
		return false;
	if (this->effect !=Boost::laser)
		return false;
	if (this->playerID == itr->id)
		return false;
	if(!itr->head.getGlobalBounds().intersects(this->laser.elipse.getGlobalBounds()))
		return false;
	return true;
}
Boost::type Effect::getType() const
{
	return effect;
}
