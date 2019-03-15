#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <array>

#include "Player.h"
#include "Boost.h"
#include "Effect.h"
#include "laser.h"
//Board where players fights 
class Board : public sf::Drawable
{
	const static unsigned int wallSize = 5;
	const sf::Color wallColor = sf::Color::Yellow;
	//sf::RectangleShape wall;
	std::array <sf::RectangleShape, 4> walls;
	static const int distanceFromWall = 15;
	//Our board size
	sf::Vector2f sizeBoard;
	//Info about players
	int numberOfPlayers;
	//std::<Player, 0> play;
	//using players = std::array<Player, 0> play;
	//Brakuje mi dobrego kontenera na to...
	std::vector <Player> players;
	//Time in game
	std::chrono::time_point<std::chrono::system_clock> StartTime;
	std::chrono::time_point<std::chrono::system_clock> ActualTime;
	//Ticks
	unsigned mutable int tick;
	//Second way to detecion colision TY Pioter for idea :D
	mutable sf::Image imageOfBoard;
	mutable sf::Texture textureOfBoard;
	mutable sf::Sprite spiriteOfBoard;
	//Method to random position
	sf::Vector2f randomPosition();
	//Counter of boosters
	int unsigned const MAX_ELEMENTS = 10;
	std::vector <Boost> boosters;
	//Game effect
	std::vector <Effect> effects;
	void addNewEffect(std::vector<Player>::iterator &itr, unsigned int type);
	void setupWalls();
public:
	Board(sf::Vector2u m_size);
	~Board();
	//I know its terrible mechanic...
	void go();
	//Draw our board
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//Tempolary stering
	void turnLeft();
	void turnRight();
	void turnLeft2();
	void turnRight2();
	//Colision with other players
	bool collisionWithOtherPlayers(std::vector<Player>::iterator &itr);
	//The game is end
	bool gameOver();
	//Get size of gameBoard
	sf::Vector2f getBoardSize();
};

