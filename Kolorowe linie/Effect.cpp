#include "stdafx.h"
#include "Effect.h"

Effect::Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick):
	beginTick(tick)
{
	playerID = itr->id;
	effect = Boost::type(type);
	durationTime = standardDurationTick;
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
		durationTime = noBodyTime;
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
		//durationTime = 3000;// laserTime;
		break;
	default:
		break;
	}
}
/*
Effect::Effect(int ID, int tick, Boost::type eff)
{
	playerID = ID;
	this->effect = eff;
	beginTick = tick;
}
*/

Effect::Effect(const Effect & effect)
{
	this->playerID = effect.playerID;
	this->effect = effect.effect;
	this->beginTick = effect.beginTick;
	this->durationTime = effect.durationTime;
	this->laser = effect.laser;
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
	durationTime = temp.durationTime;
	return *this; 
}

unsigned int Effect::getPlayerID() const
{
	return playerID;
}

bool Effect::isEnd(int curretTick)
{
	if (curretTick - beginTick > durationTime)
		return true;
	return false;
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
	//lag reduce
	//if (!Effect::LASER_ON)
	//	return false;
	if (this->effect !=Boost::laser)
		return false;
	if (this->playerID == itr->id)
		return false;
	if(!itr->head.getGlobalBounds().intersects(this->laser.elipse.getGlobalBounds()))
		return false;
	return true;
}
int Effect::getTimeToEnd(int tick)
{
	return durationTime - (tick - beginTick);
}
Boost::type Effect::getType() const
{
	return effect;
}

bool Effect::operator<(const Effect & toCompare) const
{
	if (this->beginTick + this->durationTime < toCompare.durationTime + toCompare.beginTick)
		return true;
	return false;
}
