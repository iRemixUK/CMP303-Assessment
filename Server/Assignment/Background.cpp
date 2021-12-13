#include "Background.h"

Background::Background()
{
	setSize(sf::Vector2f(1200, 675));
	setPosition(0, 0);
}

void Background::initWalls()
{
	// Set size and position of walls 
	wall.setSize(sf::Vector2f(40, 150));
	wall.setPosition(sf::Vector2f(850, 50));
	wall.setCollisionBox(sf::FloatRect(0, 0, 50, 150));

	wall2.setSize(sf::Vector2f(40, 150));
	wall2.setPosition(sf::Vector2f(850, 475));
	wall2.setCollisionBox(sf::FloatRect(0, 0, 50, 150));

	wall3.setSize(sf::Vector2f(40, 150));
	wall3.setPosition(sf::Vector2f(250, 50));
	wall3.setCollisionBox(sf::FloatRect(0, 0, 50, 150));

	wall4.setSize(sf::Vector2f(40, 150));
	wall4.setPosition(sf::Vector2f(250, 475));
	wall4.setCollisionBox(sf::FloatRect(0, 0, 50, 150));

	// Set the colour of walls 
	wall.setFillColor(sf::Color(0, 0, 0, 255));
	wall2.setFillColor(sf::Color(0, 0, 0, 255));
	wall3.setFillColor(sf::Color(0, 0, 0, 255));
	wall4.setFillColor(sf::Color(0, 0, 0, 255));

	wall.setOutlineThickness(3.f);
	wall.setOutlineColor(sf::Color(0, 0, 255, 255));
	wall2.setOutlineThickness(3.f);
	wall2.setOutlineColor(sf::Color(0, 0, 255, 255));

	wall3.setOutlineThickness(3.f);
	wall3.setOutlineColor(sf::Color(255, 0, 0, 255));
	wall4.setOutlineThickness(3.f);
	wall4.setOutlineColor(sf::Color(255, 0, 0, 255));
}

void Background::playerCollision(GameObject wall, Player* player)
{
	// Checks for player collision against the wall
	if (Collision::checkBoundingBox(&wall, player))
	{
		if (player->getPosition().x > wall.getPosition().x)
		{
			player->zeroSpeed();
			player->setPosition(wall.getPosition().x + wall.getSize().x + 10.f, player->getPosition().y);
			
		}
		
		if (player->getPosition().x < wall.getPosition().x)
		{
			player->zeroSpeed();
			player->setPosition(wall.getPosition().x - player->getSize().x, player->getPosition().y);
		}
	}
}

void Background::bulletCollision(Bullet* bullet)
{
	// Checks for bullet collision against the wall
	if (Collision::checkBoundingBox(&wall, bullet))
	{
		bullet->setAlive(false);
	}

	if (Collision::checkBoundingBox(&wall2, bullet))
	{
		bullet->setAlive(false);
	}
	
	if (Collision::checkBoundingBox(&wall3, bullet))
	{
		bullet->setAlive(false);
	}
	
	if (Collision::checkBoundingBox(&wall4, bullet))
	{
		bullet->setAlive(false);
	}
}

void Background::update(Player* player)
{
	playerCollision(wall, player);
	playerCollision(wall2, player);
	playerCollision(wall3, player);
	playerCollision(wall4, player);
}

void Background::render()
{
	window->draw(wall);
	window->draw(wall2);
	window->draw(wall3);
	window->draw(wall4);
}

Background::~Background()
{

}