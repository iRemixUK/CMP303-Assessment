#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Level.h"
#include "WinScreen.h"

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 675), "CMP303 - Player 2");
	window.setFramerateLimit(144);
	// Initialise input and level objects.
	Input input;
	Level level(&window, &input);
	
	std::string thisPlayerAddress;
	unsigned short thisPlayersPort;

	std::string thisBulletAddress;
	unsigned short otherBulletsPort;

	std::string thisStartIP;
	unsigned short thisStartPort;

	std::cout << "The other player's application must be run first to allow the other player to connect \n";
	std::cout << "Please enter this player's IP and port. Must match the other's player's IP, IP and Port used for testing was 127.0.0.2 and 4444 \n";
	std::cin >> thisPlayerAddress >> thisPlayersPort;


	std::cout << "Please enter this player's IP address and port for the bullet socket. Must match the other's player's bullet socket IP and port. IP and Port used for testing was 127.0.0.1 and 54003 \n";
	std::cin >> thisBulletAddress >> otherBulletsPort;

	std::cout << "Please enter the IP and port to send the start message. Both IP and Port must match the other player. IP and Port used for testing was 127.0.0.3 and 53000 \n";
	std::cin >> thisStartIP >> thisStartPort;

	level.network.initSockets(thisPlayerAddress, thisPlayersPort, thisBulletAddress, otherBulletsPort, thisStartIP, thisStartPort);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	
	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)
		if (level.state == 0)
		{
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();
		}

		if (level.state == 1 || level.state == 2)
		{
			WinScreen winScreen(&window, &input, level.state);
			winScreen.handleInput(deltaTime);
			winScreen.update(deltaTime);
			winScreen.render();
		}

	}
}


