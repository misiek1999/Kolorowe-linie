#include "stdafx.h"
#include "board.h"


Board::Board(sf::Vector2u m_size):
	sizeBoard(m_size)
{
	//First all players =2
	numberOfPlayers = 2;
	players.push_back(Player(sf::Vector2f(100, 100), sf::Color::Red));
	players.push_back(Player(sf::Vector2f(200, 200), sf::Color::Blue));

}


Board::~Board()
{
	players.clear();
}

void Board::go()
{
	for (auto itr = players.begin(); itr != players.end(); itr++)
		itr->move();
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw all heads
	for ( auto itr : players)
		target.draw(itr.head);


}

void Board::turnLeft()
{
	players.begin()->head.rotate(-10);
}

void Board::turnRight()
{
	players.begin()->head.rotate(10);
	
}
#include <iostream>


void Board::test(sf::Image &obrazek)
{
	for (auto itr : players)
		if (obrazek.getPixel(itr.head.getPosition().x, (itr.head.getPosition().y-(itr.head.getRadius()/2)-10)) != sf::Color::Black);
			std::cout << "KONIEC";

}
