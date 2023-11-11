#include "Entity.h"

void aries::Entity::setVelocity(sf::Vector2f vec)
{
	mVelocity = vec;
}

void aries::Entity::setVelocity(float vx, flot vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}
