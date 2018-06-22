#include "stdafx.h"
#include "Game.h"


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
	sf::RenderWindow mainWindow (sf::VideoMode(640, 480), "LOL TO JESZCZE  :D ",sf::Style::Default ,windowSetting);

	//Wunsze


	//Zdjecie mapy
	sf::Image screen;
	



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
		//Screen generation
		mainWindow.clear();
		screen = mainWindow.capture();







		mainWindow.display();


	}





}