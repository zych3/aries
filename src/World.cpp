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
	, mScrollSpeed(20.f)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

	

	mPlayer = new Player(mTextures);

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
	mPlayer->setVelocity(mScrollSpeed, 40.f);
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

	mPlayer->setVelocity(0.f, 0.f);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);


	mSceneGraph.update(dt);

	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize()
	);
	const float borderDistance = 40.f;

	sf::Vector2f pos = mPlayer->getPosition();
	pos.x = std::max(pos.x, viewBounds.left + borderDistance);

	pos.x = std::min(pos.x, viewBounds.left +
		viewBounds.width - borderDistance);
	mPlayer->setPosition(pos);
}
