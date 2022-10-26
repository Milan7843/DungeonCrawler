#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::start()
{
}

void Bullet::update()
{
	transform->movePosition(transform->getLocalRightVector() * Time::getDeltaTime() * 0.2f);
}
