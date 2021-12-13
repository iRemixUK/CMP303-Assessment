#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Player.h"
#include "Bullet.h"
class Background :
	public GameObject
{
public:
	Background();
	~Background();

	void initWalls();
	void playerCollision(GameObject wall, Player* player);
	void bulletCollision(Bullet* bullet);
	void update(Player* player);
	void render();
	void setWindow(sf::RenderWindow* hwnd) { window = hwnd; }

private:
	sf::RenderWindow* window;
	GameObject wall;
	GameObject wall2;
	GameObject wall3;
	GameObject wall4;
};
 