#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <array>
#include <queue>
#include "board.h"
#include "ServerPlayer.h"


class Server
{
public : enum mode { singlePlayer, multiPLayer };
private:
	//Board mainBoard;

	sf::Vector2u boardSize;
	//const std::size_t maxClients = 8;
	#define MAX 8		//A teraz dzia³a...
	size_t numberOfPlayers;
	std::array<ServerPlayer, MAX> playerArr;
	mode state;
	class Event {
		Board::rotate rotate_;
		std::size_t id_;
	public:
		Event(Board::rotate rotate, std::size_t id);
		friend class Server;
	};
	std::queue<Server::Event> steringConteiner;

	//Multithreading
	std::thread in;
	std::thread out;
	std::mutex lockMainBoard;
public:
	Server(sf::Vector2f boardSize_, mode mode_, size_t numberOfPlayers_);
	bool run();
	~Server();
	//Only for single player
	void rotatePLayer(size_t ID, Board::rotate rotationMode);
private:
	Board mainBoard;
};

