#include "Game.h"

aries::Game::Game()
	: mWindow(sf::VideoMode(640, 480), "ARIES")
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Magenta);
}

void aries::Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);

		}
		render();
	}
}

void aries::Game::processEvents()
{
	sf::Event e;
	while(mWindow.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(e.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(e.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void aries::Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
		if (mIsMovingUp) movement.y -= 10.f;
		if (mIsMovingDown) movement.y += 10.f;
		if (mIsMovingLeft) movement.x -= 10.f;
		if (mIsMovingRight) movement.x += 10.f;

		mPlayer.move(movement * deltaTime.asSeconds());
}

void aries::Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void aries::Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A) mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D) mIsMovingRight = isPressed;

}




