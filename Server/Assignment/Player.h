#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void CollisionResponse();
	void zeroSpeed();
	float getSpeedX();
	float getSpeedY();
	int GetHealth();


private:
	float speedx;
	float speedy;
	float health;
};

