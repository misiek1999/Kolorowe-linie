#pragma once
#include "Boost.h"
#include "Player.h"
#include "laser.h"
#include <vector>
class Effect
{
	const float speedDown= 0.7;
	const float speedUp = 2.5;
	const float sizeUp = 2.0;
	const float sizeDown = 0.5;
	int playerID;
	const int durationTick = 200;
	const int laserTime = 3000;
	int beginTick;
	Boost::type effect;
	Laser laser;
public:
	Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick);
	//Special constructor for laser mechanic 
	//Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick, sf::Vector2f boardSize);
	Effect(int ID, int tick, Boost::type eff);
	~Effect();
	Effect& operator=(const Effect &);
	unsigned int getPlayerID() const;
	bool endOfEffect(int);
	void remove(std::vector<Player>::iterator &itr);
	bool collisionWithLaser(std::vector<Player>::iterator &itr);
	Boost::type getType()const;
	const static bool LASER_ON = true;
	friend class Board;
};

