#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <sfml/OpenGL.hpp>
Game::Game()
{
}


Game::~Game()
{
}


int Game::run()
{
	//Okno g³owne
	sf::ContextSettings windowSetting;
	windowSetting.antialiasingLevel = 8;
	sf::RenderWindow mainWindow (sf::VideoMode(640, 480), "      VIRUS 2.0.3.456  :D ",sf::Style::Close ,windowSetting);
	mainWindow.clear(sf::Color::Black);
	//Speeed of game
	mainWindow.setFramerateLimit(60);
	//Mapka 
	Board mainBoard(mainWindow.getSize());





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

		mainWindow.draw(mainBoard);
		//std::cout << "NEXT TICK 	";
		mainWindow.display();

		
	}




	return 0;
}