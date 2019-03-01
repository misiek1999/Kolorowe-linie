#pragma once
#include "Boost.h"
#include "Player.h"
#include <vector>
class Effect
{
	const int speedDown= 0.5;
	const int speedUp = 2.0;
	const int sizeUp = 2.0;
	const int sizeDown = 0.5;
	int playerID;
	const int durationTick = 200;
	int beginTick;
	Boost::type effect;
public:
	Effect(std::vector<Player>::iterator &itr, unsigned int type, int tick);
	Effect(int ID, int tick, Boost::type eff);
	~Effect();
	Effect& operator=(const Effect &);
	unsigned int getPlayerID() const;
	bool endOfEffect(int);
	void remove(std::vector<Player>::iterator &itr);
};

