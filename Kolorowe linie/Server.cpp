#include "stdafx.h"
#include "Server.h"
#include "ServerPlayer.h"

Server::Server(sf::Vector2f boardSize_, mode mode_, size_t numberOfPlayers_) :
	state(mode_),
	numberOfPlayers(numberOfPlayers_),
	mainBoard(sf::Vector2u(boardSize))
{
	boardSize =sf::Vector2u(boardSize_);
	
	//playerArr.fill(Player())
	for (std::size_t i = 0; i < numberOfPlayers; i++){
		playerArr[i].score = 0;
		playerArr[i].id = i;
	}



	}

bool Server::run()
{
	std::vector<int> playersWhoDead;
	int temp=-1;
	while (true)
	{
		//All players are live in this round
		for (auto i = 0; i < playersWhoDead.size(); i++)
			playerArr[i].isLive = true;
		
		new(&mainBoard) Board(sf::Vector2u(boardSize.x *0.8, boardSize.y));
		//U¿ycie goto by³oby bardziej wydajne pewnie
		while (numberOfPlayers - playersWhoDead.size() < 2)
		{ 
			//Change move direction
			if (!steringConteiner.empty());
			{
				mainBoard.changePlayerDirection(steringConteiner.front().id_, steringConteiner.front().rotate_);
				steringConteiner.pop();
			}
			//Next tick in board
			if (temp = mainBoard.go() && temp != -1)
			{
				playersWhoDead.push_back(temp);
				playerArr[temp].isLive = false;
			}


		}

		//Sum score 
		for (auto i = 0; i < playersWhoDead.size(); i++)
			this->playerArr[playersWhoDead[i]].score += i;
		playersWhoDead.clear();
		
		
		
	}

	return false;
}


Server::~Server()
{
}

void Server::rotatePLayer(size_t ID, Board::rotate rotationMode)
{
	if (ID <numberOfPlayers)
		if (playerArr[ID].isLive)
			steringConteiner.push(Event(rotationMode, ID));
}

ServerPlayer::ServerPlayer()
{
	//ip = sf::IpAddress("123.123.123.123");
}

ServerPlayer::~ServerPlayer()
{
}

Server::Event::Event(Board::rotate rotate, std::size_t id):
	rotate_(rotate),
	id_(id)
{}
