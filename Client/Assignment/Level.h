#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"

#include "BulletManager.h"
#include "Player.h"
#include "Background.h"
#include "receivedPositionMessage.h"
#include "receivedBulletMessage.h"
#include "Networking.h"

#include <string>
#include <iostream>


class Level {
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();
	int state = 0;
	Networking network;

private:

	void BulletCollision();
	void DeathCheck();
	sf::Vector2f linearPrediction();
	void initText();
	void initPlayers();

	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	AudioManager* audio;
	Player player, player2;
	Background Background;
	BulletManager player1_bullets, player2_bullets;
	sf::Texture background, player1_tex, player2_tex, player1_bulletTex, player2_bulletTex, floor_tex;
	sf::RectangleShape floor;
	sf::Vector2f direction;

	// Text
	sf::Font font;
	sf::Text myHealth, myCurrentHealth, enemyHealth, currentEnemyHealth;

	// Networking variables
	receivedPositionMessage receivedMessage;
	receivedBulletMessage bulletMessage;
	std::vector<receivedPositionMessage> messages;
	float gameTime;
	float updateTime; 
}; 
