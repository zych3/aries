#include "Player.h"
#include "ResourceHolder.h"

aries::Player::Player(const TextureHolder& textures)
	: mSprite(textures.get(Texture::ID::hero))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void aries::Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
