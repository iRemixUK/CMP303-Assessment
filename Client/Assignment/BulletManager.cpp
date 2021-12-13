#include "BulletManager.h"
#include <iostream>

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::init(sf::Texture bulletTex)
{
	texture = bulletTex;
	for (int i = 0; i < 40; i++)
	{
		bullets.push_back(Bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&texture);
		bullets[i].setSize(sf::Vector2f(50, 50));
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 50, 50));
	}
}
void BulletManager::handleInput(int posx, int posy)
{
	target = sf::Vector2f(posx, posy);
}

void BulletManager::spawn(float posx, float posy)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].isAlive())
		{
			spawnPoint = sf::Vector2f(posx, posy);
			bullets[i].setAlive(true);
			bullets[i].setPosition(spawnPoint);
			direction = target - spawnPoint;
			direction = Vector::normalise(direction);
			bullets[i].setVelocity(200 * direction.x, 200 * direction.y);
			return;
		}
	}
}

void BulletManager::deathCheck()
{

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < 0 - bullets[i].getSize().x)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > 1200)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < 0 - bullets[i].getSize().y)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > 675)
			{
				bullets[i].setAlive(false);
			}
		}
	}
}

void BulletManager::update(float dt)
{
	// call update on all ALIVE balls
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt);
		}
	}
	deathCheck();
}

void BulletManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
}