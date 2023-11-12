#include "SpriteNode.h"

aries::SpriteNode::SpriteNode(const sf::Texture texture)
	: mSprite(texture)
{
}

aries::SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	:mSprite(texture, rect)
{
	mSprite.setTextureRect(rect);
	mSprite.setTextureRect(rect);
}

void aries::SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
