#include "Player.h"

#include <iostream>
#include <ranges>

#include "ResourceHolder.h"

aries::Player::Player(const TextureHolder& textures)
	: mSprite(textures.get(Texture::ID::hero))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	mKeyBindings[sf::Keyboard::Left] = movingLeft;
	mKeyBindings[sf::Keyboard::Right] = movingRight;
	mActionBinding[movingLeft].action =
		[](SceneNode& node, sf::Time dt)
	{
		const float playerSpeed = 30.f;
		node.move(0.f, -playerSpeed * dt.asSeconds());
	};
	mActionBinding[movingRight].action =
		[](SceneNode& node, sf::Time dt)
	{
		const float playerSpeed = 30.f;
		node.move(0.f, playerSpeed * dt.asSeconds());
	};

	for (auto& pair : mActionBinding)
		pair.second.category = Category::Player;
}

void aries::Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned aries::Player::getCategory() const
{
	return Category::Player;
}

void aries::Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	
	if(event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::P)
	{
		Command debug_print;
		debug_print.category = Category::Player;
		debug_print.action = [](SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ", "
				<< s.getPosition().y << "\n";
		};
		commands.push(debug_print);
	}

}

void aries::Player::handleRealTimeInput(CommandQueue& commands)
{
	const float playerSpeed = 30.f;

	for(auto p : mKeyBindings)
	{
		if (sf::Keyboard::isKeyPressed(p.first) &&
			isRealTimeAction(p.second))
			commands.push(mActionBinding[p.second]);
	}
	
}

void aries::Player::assignKey(Action action, sf::Keyboard::Key key)
{
	mKeyBindings[key] = action;
}

sf::Keyboard::Key aries::Player::getAssignedKey(Action action) const
{
	for(auto pair : mKeyBindings)
	{
		if (pair.second == action)
			return pair.first;
	}
}

bool aries::Player::isRealTimeAction(Action action)
{
	return true; 
}
