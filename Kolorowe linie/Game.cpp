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
	mainWindow.setFramerateLimit(30);
	//Mapka 
	Board mainBoard(mainWindow.getSize());
	//Test one of method detection colision
	sf::Texture obrazek;
	obrazek.create(mainWindow.getSize().x, mainWindow.getSize().y);
	sf::Image img;

	//Second way to detecion colision TY Pioter for idea :D
	bool isPixelThere[640][480];		//Array of our pixel


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
		//Screen generation
		//mainWindow.clear();
		

		mainBoard.go();
		mainWindow.draw(mainBoard);
		view = mainWindow.getView();
		//obrazek = (mainWindow.capture());
		obrazek.update(mainWindow);
		img = obrazek.copyToImage();
		mainBoard.test(img);
		
		//std::cout << "NEXT TICK 	";
		mainWindow.display();

		
	}




	return 0;
}