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
	const int laserTime = 300;
	const int noBodyTime = 60;
	size_t durationTime;
	int beginTick;
	Boost::type effect;
	Laser laser;
public:
	Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick);
	//To delete
	//Effect(int ID, int tick, Boost::type eff);
	//Copy constructor
	Effect(const Effect & effect);
	~Effect();
	//deafult 
	Effect& operator=(const Effect &);
	//return player ID
	unsigned int getPlayerID() const;
	//test that event has benn expiries
	bool isEnd(int);
	//remove effect from player
	void remove(std::vector<Player>::iterator &itr);
	//test colision with laser
	bool collisionWithLaser(std::vector<Player>::iterator &itr);
	// return time to end this event
	int getTimeToEnd(int);
	//return type of effect
	Boost::type getType()const;
	//		== to std:: sort
	bool operator< (const Effect& toCompare) const;
	//Flag to disable laser in game
	const static bool LASER_ON = true;
	friend class Board;
};

