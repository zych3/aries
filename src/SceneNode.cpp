#include "SceneNode.h"

#include <iostream>

aries::SceneNode::SceneNode()
	: mChildren()
{
}

void aries::SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

aries::SceneNode::Ptr aries::SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::ranges::find_if(mChildren,
	                                  [&](Ptr& p)->bool {return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void aries::SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (const auto& child : mChildren)
	{
		child->draw(target, states);
	}
}

void aries::SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}


void aries::SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void aries::SceneNode::updateChildren(sf::Time dt)
{
	
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) (*iter)->update(dt);
}

void aries::SceneNode::updateCurrent(sf::Time dt)
{
	
}


sf::Transform aries::SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for(const SceneNode* node = this;
		node != nullptr;
		node = node->mParent)
			transform = node->getTransform() * transform;

	return transform;
}

sf::Vector2f aries::SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void aries::SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);

	for(int i = 0; i < mChildren.size(); ++i)
	{
		mChildren[i]->onCommand(command, dt);
	}
}
