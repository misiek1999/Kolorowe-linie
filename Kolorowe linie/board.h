#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "Player.h"
//Board where players fights 
class Board : public sf::Drawable
{

	sf::Vector2f sizeBoard;
	static const float wallSize;
	//Info about players
	int numberOfPlayers;
	std::vector <Player> players;
	
	//Second way to detecion colision TY Pioter for idea :D
	mutable sf::Image imageOfBoard;
	mutable sf::Texture textureOfBoard;
	mutable sf::Sprite spiriteOfBoard;
public:
	Board(sf::Vector2u m_size);
	~Board();
	//I know its terrible mechanic...
	void go();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void turnLeft();
	void turnRight();
	bool collisionWithOtherPlayers(std::vector<Player>::iterator &itr);

};

