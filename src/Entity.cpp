#include "Entity.h"
#include "Entity.h"

void aries::Entity::setVelocity(sf::Vector2f vec)
{
	mVelocity = vec;
}

void aries::Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}




