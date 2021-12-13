#pragma once
#include "Bullet.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "Framework/Vector.h"
#include "Framework/Input.h"
#include "Framework/GameObject.h"
class BulletManager :
	public GameObject
{
public:
	BulletManager();
	~BulletManager();
	void init(sf::Texture bulletTex);
	void spawn(float posx, float posy);
	void handleInput(int posx, int posy);
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);
	std::vector<Bullet> bullets;
	

private:
	sf::Vector2f spawnPoint;
	sf::Texture texture;
	sf::Vector2f target;
	sf::Vector2f direction;
};

