#include "Networking.h"

Networking::Networking()
{
	// Initialising received message
	receivedMessage.x = 1000.f;
	receivedMessage.y = 310.f;
	receivedMessage.time = 0.f;
	messages.push_back(receivedMessage);
}

void Networking::initSockets(std::string thisPlayerAddress, unsigned short thisPlayersPort,
	std::string thisBulletAddress, unsigned short thisBulletsPort,
	std::string thisStartIP, unsigned short thisStartPort)
{
	// Current player
	playerIP = thisPlayerAddress;
	thisPort = thisPlayersPort;

	// Current bullet
	bulletIP = thisBulletAddress;
	bulletPort = thisBulletsPort;

	// Start message IP
	startIP = thisStartIP;
	startPort = thisStartPort;

	// Binds udp socket
	if (udpServerSocket.bind(thisPort) != sf::Socket::Done)
	{
		std::cout << "UDP bind failed!\n";
	}
	else
	{
		std::cout << "Bind Successful\n";
	}


	// Connect TCP sockets
	status = startSocket.connect(startIP, startPort);
	statusBullet = bulletSocket.connect(bulletIP, bulletPort);
	statusPosition = postionSocket.connect(playerIP, thisPort);

	// Set to non-blocking so receive function always returns instantly, also does not block game execution
	postionSocket.setBlocking(false);
	bulletSocket.setBlocking(false); 
}

void Networking::sendTCP(float positionX, float positionY, float gameTime)
{
	// Create packet
	sf::Packet packet;
	packet << positionX << positionY << gameTime;

	// Send packet
	postionSocket.send(packet);
}

void Networking::receiveTCP()
{
	// Create packet to receive
	 sf::Packet packet;

	 // Receive packet
	 postionSocket.receive(packet);

	 // Add packet to messages 
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
	// Create packet to send
	sf::Packet packet;
	packet << targetX << targetY;

	// Send packet
	bulletSocket.send(packet);
}

receivedBulletMessage Networking::receiveBulletTCP()
{
	// Create packet to receive
	sf::Packet packet;
	packet >> bulletMessage.x >> bulletMessage.y;

	// Receive packet
	bulletSocket.receive(packet);

	// Return the packet received
	if (packet >> bulletMessage.x >> bulletMessage.y)
	{
		bulletMessage.flag = true;
		return bulletMessage;
		//std::cout << receiveBulletTargetX << ", " << receiveBulletTargetY << "\n";
	}
	else {
		bulletMessage.flag = false;
		bulletMessage.x = 1000;
		bulletMessage.y = 1000;
		return bulletMessage;
	}

}

Networking::~Networking()
{

}

bool Networking::receiveStart()
{
	// Blocks program execution until it receives a start message from the server 
	// This means that both the programs will start at the same time
	bool startFlag = false;
	sf::Packet packet;
	startSocket.receive(packet);
	packet >> startFlag;
	return startFlag;
}
