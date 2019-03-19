#pragma once
#include <SFML/Network.hpp>
#include"Server.h"

class ServerPlayer {
	std::size_t score;
	std::size_t id;
	bool isLive;
	sf::IpAddress ip;
public:
	ServerPlayer();
	~ServerPlayer();

	friend class Server;
};

