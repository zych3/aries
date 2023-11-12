#pragma once
#include <array>

#include "ariespch.h"
#include "Player.h"
#include "SceneNode.h"

namespace aries
{
	class World : private sf::NonCopyable
	{
	public:
		explicit World(sf::RenderWindow& window);
		void update(sf::Time dt);
		void draw();

	private:
		void loadTextures();
		void buildScene();

	private:
		enum Layer
		{
			Background,
			Gameplay,
			Counter
		};

	private:
		sf::RenderWindow& mWindow;
		sf::View mWorldView;
		TextureHolder mTextures;
		SceneNode mSceneGraph;

		std::array<SceneNode*, Counter> mSceneLayers;

		sf::FloatRect mWorldBounds;
		sf::Vector2f mSpawnPosition;
		float mScrollSpeed;
		Player* mPlayer;
	};
}
