#pragma once
#include "CommandQueue.h"
#include "Entity.h"
namespace aries
{


	class Player : public Entity
	{
	public:
		enum Action
		{
			movingLeft,
			movingRight,
			jumping,
			crouching,
			attacking
		};

		void assignKey(Action action, sf::Keyboard::Key key);

		sf::Keyboard::Key getAssignedKey(Action action) const;

	public:
		explicit Player(const TextureHolder& textures);
		

		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned getCategory() const override;

		void handleEvent(const sf::Event& event,
			CommandQueue& commands);

		void handleRealTimeInput(CommandQueue& commands);

	private:
		static bool isRealTimeAction(Action action);

		std::map<sf::Keyboard::Key, Action> mKeyBindings;
		std::map<Action, Command> mActionBinding;

		sf::Sprite mSprite;
		
	};

	struct PlayerMover
	{
		PlayerMover(float vx, float vy)
		{
			
		}

		void operator() (Player& player, sf::Time) const
		{
			player.setVelocity(velocity);
		}

		sf::Vector2f velocity;
	};
}