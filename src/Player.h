#pragma once
#include "Entity.h"
namespace aries
{
	class Player : Entity
	{
	public:
		explicit Player(const TextureHolder& textures);

		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite mSprite;
		
	};
}