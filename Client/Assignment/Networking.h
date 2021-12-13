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
		unsigned short thisBulletsPort, std::string thisStartIP,
		unsigned short thisStartPort);
	
	void sendTCP(float positionX, float positionY, float gameTime);
	void receiveTCP();

	void sendBulletTCP(int targetX, int targetY);
	receivedBulletMessage receiveBulletTCP();

	void addMessage(const receivedPositionMessage& msg);
	bool receiveStart();
	std::vector<receivedPositionMessage> messages;

private:
	// UDP
	sf::UdpSocket udpServerSocket;
	sf::UdpSocket udpBulletSocket;

	// TCP start socket
	sf::TcpSocket startSocket;
	sf::Socket::Status status;

	// TCP bullet socket
	sf::TcpSocket bulletSocket;
	sf::Socket::Status statusBullet;

	// TCP start socket
	sf::TcpSocket postionSocket;
	sf::Socket::Status statusPosition;

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

	int i = 0;
};