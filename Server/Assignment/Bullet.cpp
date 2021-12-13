#include "Bullet.h"

Bullet::Bullet()
{
	damage = 25;
}

Bullet::~Bullet()
{

}

int Bullet::Get_Damage()
{
	return damage;
}

void Bullet::update(float dt)
{
	move(velocity * dt);
}
