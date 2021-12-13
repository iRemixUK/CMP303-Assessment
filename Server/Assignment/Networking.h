#pragma once
#include <SFML/Network.hpp>
#include "receivedPositionMessage.h"
#include "receivedBulletMessage.h"
#include <iostream>

class Networking
{
public:
	Networking();
	~Networking();
	void initSockets(std::string thisPlayerAddress, unsigned short thisPlayersPort, 
		std::string thisBulletAddress,
		unsigned short otherBulletsPort, std::string thisStartIP, 
		unsigned short thisStartPort);

	void sendTCP(float positionX, float positionY, float gameTime);
	void receiveTCP();

	void sendBulletTCP(int targetX, int targetY);
	receivedBulletMessage receiveBulletTCP();

	void addMessage(const receivedPositionMessage& msg);
	void sendStart();
	std::vector<receivedPositionMessage> messages;

private:
	void initListeners();

	// TCP
	sf::TcpSocket clientStart;
	sf::TcpListener listener;
	sf::TcpSocket clientBullet;
	sf::TcpSocket clientPosition;

	// Networking variables
	receivedPositionMessage receivedMessage;
	receivedBulletMessage bulletMessage;
	bool receivedBulletFlag;

	// IP addresses and ports
	// Player IP and ports
	sf::IpAddress playerIP;
	unsigned short thisPort;

	// Bullet IP and ports
	sf::IpAddress bulletIP;
	unsigned short bulletPort;
	unsigned short playerBulletPort;

	// Start IP and port
	sf::IpAddress startIP;
	unsigned short startPort;
};