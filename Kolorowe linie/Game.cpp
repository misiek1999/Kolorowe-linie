#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <sfml/OpenGL.hpp>
bool Game::nextRound(sf::RenderWindow &window, Board board)
{
	sf::Text message;
	message.setString("Do you want continue? Y/N");
	message.setFont(font);
	message.setFillColor(sf::Color::White);
	message.setCharacterSize(24);
	window.draw(board);
	window.draw(message);
	window.display();
	sf::Event mainEvent;
	while (window.isOpen())
	{
		while (window.pollEvent(mainEvent))
		{
			switch (mainEvent.type)
			{
			case sf::Event::Closed:
				return false;
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			return false;
	}
	return false;
}

Game::Game():
	videoSize(900, 600)
{
	font.loadFromFile("arial.otf");
}

Game::~Game()
{
}

int Game::run()
{
	//Okno g³owne
	sf::ContextSettings windowSetting;
	windowSetting.antialiasingLevel = 8;
	sf::RenderWindow mainWindow (videoSize, "      VIRUS 2.0.3.456  :D ",sf::Style::Close ,windowSetting);
	mainWindow.clear(sf::Color::Black);
	//Speeed of game
	mainWindow.setFramerateLimit(60);
	//Mapka 
	//Board mainBoard(sf::Vector2u(mainWindow.getSize().x , mainWindow.getSize().y ));
	Board mainBoard (sf::Vector2u(mainWindow.getSize().x - 200, mainWindow.getSize().y));
	sf::Event mainEvent;
	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent(mainEvent))
		{
			switch (mainEvent.type)
			{
				case sf::Event::Closed :
					mainWindow.close();
					break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			mainBoard.turnLeft();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mainBoard.turnRight();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mainBoard.turnLeft2();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mainBoard.turnRight2();
		//Screen generation
		mainWindow.clear();
		
		mainBoard.go();
		if (mainBoard.gameOver())
			if (nextRound(mainWindow, mainBoard))
				new(&mainBoard) Board(sf::Vector2u(mainWindow.getSize().x - 200, mainWindow.getSize().y));
			else
				return 0;
		mainWindow.draw(mainBoard);
		mainWindow.display();
	}
	return 0;
}