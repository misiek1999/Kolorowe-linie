#pragma once
#include "Boost.h"
#include "Player.h"
#include "laser.h"
#include <vector>
class Effect
{
	const float speedDown= 0.7;
	const float speedUp = 2.0;
	const float sizeUp = 2.0;
	const float sizeDown = 0.5;
	int playerID;
	const int standardDurationTick = 200;
	const int laserTime = 3000;
	const int noBodyTime = 60;
	size_t durationTime;
	int beginTick;
	Boost::type effect;
	Laser laser;
public:
	Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick);
	//To copy
	Effect(int ID, int tick, Boost::type eff);
	//Copy constructor
	Effect(const Effect & effect);
	~Effect();
	Effect& operator=(const Effect &);
	unsigned int getPlayerID() const;
	bool isEnd(int);
	void remove(std::vector<Player>::iterator &itr);
	bool collisionWithLaser(std::vector<Player>::iterator &itr);
	int getTimeToEnd(int);
	Boost::type getType()const;
	//		== to std:: sort
	bool operator< (const Effect& toCompare) const;
	const static bool LASER_ON = true;
	friend class Board;
};

