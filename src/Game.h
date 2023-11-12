#pragma once
#include "ariespch.h"
#include "World.h"
#include "ResourceHolder.h"
namespace aries
{
	class Game
	{
	public:
		Game();
		void run();
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();
		void handlePlayerInput(sf::Keyboard::Key,
			bool isPressed);
	private:
		
		sf::RenderWindow mWindow;
		sf::Texture mTexture;
		sf::Sprite mPlayer;
		aries::World mWorld;
		bool mIsMovingUp = false,
			mIsMovingDown = false,
			mIsMovingLeft = false,
			mIsMovingRight = false;

	};
}