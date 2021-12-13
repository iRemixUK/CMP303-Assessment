#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// Initialise game objects
	initPlayers();
	initText();

	// Initialise the background
	Background.setWindow(window);
	Background.initWalls();
	floor_tex.loadFromFile("gfx/Floor_tex.jpg");
	floor.setTexture(&floor_tex);
	floor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

	gameTime = 0.f;
	updateTime = 0.0f;
	state = 0;
}

Level::~Level()
{
}

sf::Vector2f Level::linearPrediction()
{
	float predictedX;
	float predictedY;

	const int msize = network.messages.size();

	// If there is less than 2 messages received just return the starting position of the player
	if (msize < 2) 
	{
		predictedX = 1000.0f;
		predictedY = 310.0f;
		return sf::Vector2f(predictedX, predictedX);
	}

	const receivedPositionMessage& msg0 = network.messages[msize - 1];
	const receivedPositionMessage& msg1 = network.messages[msize - 2];

	// Get distance between the last two positions 
	float distanceX = msg0.x - msg1.x;
	float distanceY = msg0.y - msg1.y;

	// Get time between last two positions
	float time = msg0.time - msg1.time;

	// Get total speed and displacement for each axis 
	float speedX = distanceX / time;
	float speedY = distanceY / time;
	float displacementX = speedX * (gameTime - msg0.time);
	float displacementY = speedY * (gameTime - msg0.time);

	// Set the predicted position to the current position received added to the displacement 
	predictedX = msg0.x + displacementX;
	predictedY = msg0.y + displacementY;

	return sf::Vector2f(predictedX, predictedY);
}

void Level::BulletCollision()
{
	// Check player 1's bullets, hits wall = die or hits player 2 = die
	for (int i = 0; i < player1_bullets.bullets.size(); i++)
	{
		if (player1_bullets.bullets[i].isAlive())
		{
			Background.bulletCollision(&player1_bullets.bullets[i]);

			if (Collision::checkBoundingBox(&player2, &player1_bullets.bullets[i]))
			{
				player1_bullets.bullets[i].setAlive(false);
				player2.CollisionResponse();
			}
		}
	}

	// Check player 2's bullets, hits wall = die or hits player 1 = die
	for (int i = 0; i < player2_bullets.bullets.size(); i++)
	{
		if (player2_bullets.bullets[i].isAlive())
		{
			Background.bulletCollision(&player2_bullets.bullets[i]);

			if (Collision::checkBoundingBox(&player, &player2_bullets.bullets[i]))
			{
				player2_bullets.bullets[i].setAlive(false);
				player.CollisionResponse();
			}
		}
	}
}

void Level::DeathCheck()
{
	// Function to check if any of the player's have been killed
	if (player.GetHealth() <= 0)
	{
		// Player 1 has died so player 2 has won
		state = 2;
	}

	if (player2.GetHealth() <= 0)
	{
		// Player 2 has died so player 1 has won
		state = 1;
	}
}

void Level::handleInput(float dt)
{
	// handle user input
	player1_bullets.handleInput(input->getMouseX(), input->getMouseY());
	player.handleInput(dt);
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		player1_bullets.spawn(player.getPosition().x, player.getPosition().y);
		network.sendBulletTCP(input->getMouseX(), input->getMouseY()); // Send bullet message
		input->setKeyUp(sf::Keyboard::Space);
	}
}

// Update game objects
void Level::update(float dt)
{
	gameTime = gameTime + dt;
	updateTime = updateTime + dt;

	// Moves controllable player
	player.move(player.getSpeedX() * dt, player.getSpeedY() * dt);

	// Send and receive position messages
	if (updateTime >= 0.02)
	{
		// Sends and receives an update every 20 milliseconds
		network.sendTCP(player.getPosition().x, player.getPosition().y, gameTime);
		updateTime = 0.f;
	}

	// Keep calling receive until data has arrived
	network.receiveTCP();

	// Set the players position to the predicted position
	player2.setPosition(linearPrediction());

	// Receive bullet message 
	bulletMessage = network.receiveBulletTCP();
	
	player2.setPosition(linearPrediction());

	if (bulletMessage.flag == true)
	{
		player2_bullets.handleInput(bulletMessage.x, bulletMessage.y);
		player2_bullets.spawn(player2.getPosition().x, player2.getPosition().y);
	}

	// Checks for player collision with a wall
	Background.update(&player);
	Background.update(&player2);

	// Updates bullets being fired 
	player1_bullets.update(dt);
	player2_bullets.update(dt);

	// Checks for bullet collision
	BulletCollision();

	// Checks for any deaths
	DeathCheck();

	// Makes sure that the current health being outputted is correct
	std::string playerHealth = std::to_string(player.GetHealth());
	myCurrentHealth.setString(playerHealth);

	std::string enemyHealth = std::to_string(player2.GetHealth());
	currentEnemyHealth.setString(enemyHealth);
}

// Render level
void Level::render()
{
	// Renders everything to the screen
	beginDraw();
	window->draw(floor);

	window->draw(player);
	window->draw(player2);

	player1_bullets.render(window);
	player2_bullets.render(window);

	Background.render();

	window->draw(myHealth);
	window->draw(myCurrentHealth);
	window->draw(enemyHealth);
	window->draw(currentEnemyHealth);
	endDraw();
}

void Level::initText()
{
	// Initialises all of the text that will be outputted
	if (!font.loadFromFile("font/Pixeled.ttf"))
	{
		std::cout << "Error loading text from file\n";
	}

	myHealth.setFont(font);
	myHealth.setCharacterSize(12);
	myHealth.setPosition(0, 10);
	myHealth.setFillColor(sf::Color::White);
	myHealth.setString("Your health is:");

	enemyHealth.setFont(font);
	enemyHealth.setCharacterSize(12);
	enemyHealth.setPosition(0, 50);
	enemyHealth.setFillColor(sf::Color::White);
	enemyHealth.setString("Enemy health is:");

	myCurrentHealth.setFont(font);
	myCurrentHealth.setCharacterSize(12);
	myCurrentHealth.setPosition(150, 10);
	myCurrentHealth.setFillColor(sf::Color::White);

	currentEnemyHealth.setFont(font);
	currentEnemyHealth.setCharacterSize(12);
	currentEnemyHealth.setPosition(162, 50);
	currentEnemyHealth.setFillColor(sf::Color::White);
}

void Level::initPlayers()
{
	// Initialises both the players and the bullet texture
	player1_tex.loadFromFile("gfx/Player.png");
	player.setTexture(&player1_tex);
	player.setSize(sf::Vector2f(100, 100));
	player.setPosition(100, 310);
	player.setInput(input);
	player.setCollisionBox(sf::FloatRect(0, 0, 100, 100));

	player1_bulletTex.loadFromFile("gfx/Bullet.png");
	player1_bullets.init(player1_bulletTex);

	player2_tex.loadFromFile("gfx/Enemy.png");
	player2.setTexture(&player2_tex);
	player2.setSize(sf::Vector2f(100, 100)); 
	player2.setPosition(1000, 310);
	player2.setInput(input);
	player2.setCollisionBox(sf::FloatRect(0, 0, 100, 100));

	player2_bulletTex.loadFromFile("gfx/Enemy_Bullet.png");
	player2_bullets.init(player2_bulletTex);
}

void Level::beginDraw()
{
	// Begins rendering to the back buffer. Background colour set to light blue.
	window->clear(sf::Color(100, 149, 237));
}

void Level::endDraw()
{
	// Ends rendering to the back buffer, and swaps buffer to the screen.
	window->display();
}

// References for textures
//(123RF, no date) Vector – Animated soldier game character sprites.Available at
//https://www.123rf.com/photo_107336218_stock-vector-animated-soldier-game-charactersprites.html [Accessed 30 October. 2021].

//(123RF, no date) Vector – Animated soldier game character sprites.Available at
//https://www.123rf.com/photo_107336220_stock-vector-animated-soldier-game-charactersprites.html [Accessed 30 October. 2021]

//(Tutt, 2018) Project Atelier Concept Art (University FMP) Textures: Floors, Magic Wallpapers, book pages & logo. Available at 
//https://www.artstation.com/artwork/zAKZ36 [Accessed 30 October. 2021]



