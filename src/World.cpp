#include "World.h"
#include "SpriteNode.h"
#include "SFML/Graphics/Transform.hpp"
aries::World::World(sf::RenderWindow& window)
	: mWindow(window), mWorldView(window.getDefaultView())
	, mWorldBounds(
		0.f - mWorldView.getSize().x/2,
		0.f,
		2000.f,
		//mWorldView.getSize().y
		2000.f)
	, mSpawnPosition(
		mWorldBounds.width - mWorldView.getSize().x,
		mWorldView.getSize().y / 2.f)
	, mPlayer(nullptr), mScrollSpeed(20.f)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

 void aries::World::loadTextures()
{
	 mTextures.load(Texture::ID::hero,
		 TEXTURE_PATH"/test_hero.png");
	 mTextures.load(Texture::ID::background,
		 TEXTURE_PATH"/bcg.png");
}

void aries::World::buildScene()
{
	for(std::size_t i=0; i < Counter; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(Texture::ID::background);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(
		new SpriteNode(texture, textureRect)
	);
	backgroundSprite->setPosition(
		mWorldBounds.left,
		mWorldBounds.top
	);
	mSceneLayers[Background]
		->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Player> player(
		new Player(mTextures));
	mPlayer = player.get();

	mPlayer->setPosition(mSpawnPosition);
	//mPlayer->setVelocity(mScrollSpeed, 40.f);
	mSceneLayers[Gameplay]->attachChild(std::move(player));
	
	
}

void aries::World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}


void aries::World::update(sf::Time dt)
{
	mWorldView.move(mScrollSpeed * dt.asSeconds(), 0.f);

	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();

	/*if (position.y <= mWorldBounds.top + 150 
		|| position.y >= mWorldBounds.top + mWorldBounds.height - 150)
	{
		velocity.y = -velocity.y;
		mPlayer->setVelocity(velocity);
	}*/
	mSceneGraph.update(dt);
}
