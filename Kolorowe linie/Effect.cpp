#include "stdafx.h"
#include "Effect.h"


Effect::Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick):
	beginTick(tick)
{
	playerID = itr->id;
	effect = Boost::type(type);
	switch (playerID)
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
	default:
		break;
	}
}

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
	if (curretTick - beginTick < durationTick)
		return false;
	return true;;
}

void Effect::remove(std::vector<Player>::iterator & itr)
{
	switch (playerID)
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
