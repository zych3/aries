#include "Game.h"

#include <iostream>
#include <fmt/core.h>

aries::Game::Game()
	: mWindow(sf::VideoMode(600, 400), "ARIES"),
	mWorld(mWindow), mPlayer(mWorld.getPlayer()), mIsPaused(false)
{
	
}

void aries::Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		//processEvents();
		if (!mIsPaused)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				update(TimePerFrame);

			}
		}
		
		
		render();
	}
}

void aries::Game::processEvents()
{
	sf::Event e;
	while(mWindow.pollEvent(e))
	{
		
		

	}
}

void aries::Game::update(sf::Time deltaTime)
{

	processInput();

}

void aries::Game::render()
{
	mWindow.clear();
	mWorld.draw();
	mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(mStatisticsText);
	mWindow.display();
}

/*void aries::Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A) mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D) mIsMovingRight = isPressed;

}*/

void aries::Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event event;

	
	while(mWindow.pollEvent(event))
	{
		
		

		
		mPlayer->handleEvent(event, commands);

		if (event.type == sf::Event::Closed)
			mWindow.close();
		if (event.type == sf::Event::GainedFocus)
			mIsPaused = false;
		else if (event.type == sf::Event::LostFocus)
			mIsPaused = true;

	}
	mPlayer->handleRealTimeInput(commands);
}




