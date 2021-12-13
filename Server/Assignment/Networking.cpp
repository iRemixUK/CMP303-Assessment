#include "Networking.h"

Networking::Networking()
{
	// Initialising received message
	receivedMessage.x = 1000.f;
	receivedMessage.y = 310.f;
	receivedMessage.time = 0.f;
	messages.push_back(receivedMessage);
}

void Networking::initSockets(
	std::string thisPlayerAddress, unsigned short thisPlayersPort, 
	std::string thisBulletAddress, unsigned short otherBulletsPort, 
	std::string thisStartIP, unsigned short thisStartPort)
{
	// Current player
	playerIP = thisPlayerAddress;
	thisPort = thisPlayersPort;

	// Current bullet
	bulletIP = thisBulletAddress;
	playerBulletPort = otherBulletsPort;
	
	// Start message IP
	startIP = thisStartIP;
	startPort = thisStartPort;

	// Initalise the TCP listeners
	initListeners();
	
	// Set to non-blocking so receive function always returns instantly, also does not block game execution
	clientBullet.setBlocking(false);
	clientPosition.setBlocking(false);
}

void Networking::sendTCP(float positionX, float positionY, float gameTime)
{
	sf::Packet packet;
	packet << positionX << positionY << gameTime;
	clientPosition.send(packet);
}

void Networking::receiveTCP()
{
	sf::Packet packet;
	clientPosition.receive(packet);
	
	if (packet >> receivedMessage.x >> receivedMessage.y >> receivedMessage.time)
	{
		addMessage(receivedMessage);
	}
}

void Networking::addMessage(const receivedPositionMessage& msg)
{
	// Adds other player's position and local game time to a vector which will be used for prediction
	if (msg.time != messages.back().time)
	{
		messages.push_back(msg);
	}
}

void Networking::sendBulletTCP(int targetX, int targetY)
{
	// Sends the bullet target position
	sf::Packet packet;
	packet << targetX << targetY;

	clientBullet.send(packet);
}

receivedBulletMessage Networking::receiveBulletTCP()
{
	// Receives bullet using TCP
	sf::Packet packet;

	if (clientBullet.receive(packet)!= sf::Socket::Done)
	{
		//std::cout << "Receive Failed!\n";
		bulletMessage.flag = false;
		return bulletMessage;
	}

	if (packet >> bulletMessage.x >> bulletMessage.y)
	{
		bulletMessage.flag = true;
		return bulletMessage;
		//std::cout << receiveBulletTargetX << ", " << receiveBulletTargetY << "\n";
	}
	else 
	{
		bulletMessage.flag = false;
		bulletMessage.x = 0;
		bulletMessage.y = 0;
		return bulletMessage;
	}
}

Networking::~Networking()
{

}

void Networking::sendStart()
{
	// Blocks program execution until it sends a message to the client
	// This means that both the programs will start at the same time
	bool startFlag = true;
	sf::Packet packet;
	packet << startFlag;
	clientStart.send(packet);
}

void Networking::initListeners()
{
	// Bind listener to a port
	if (listener.listen(startPort) != sf::Socket::Done)
	{
		std::cout << "Listen failed!\n";
	}

	// Accept client start socket
	if (listener.accept(clientStart) != sf::Socket::Done)
	{
		std::cout << "Accept failed!\n";
	}

	// Bind bullet listener
	if (listener.listen(playerBulletPort) != sf::Socket::Done)
	{
		std::cout << "Listen failed!\n";
	}

	// Accept client socket
	if (listener.accept(clientBullet) != sf::Socket::Done)
	{
		std::cout << "Accept failed!\n";
	}

	// Bind position listener
	if (listener.listen(thisPort) != sf::Socket::Done)
	{
		std::cout << "Listen failed!\n";
	}

	// Accept position socket
	if (listener.accept(clientPosition) != sf::Socket::Done)
	{
		std::cout << "Accept failed!\n";
	}
}
