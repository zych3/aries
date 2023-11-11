#include "SceneNode.h"

aries::SceneNode::SceneNode()
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
