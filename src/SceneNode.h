#pragma once

#include "ariespch.h"

namespace aries
{
	class SceneNode : public sf::Transformable, public sf::Drawable,
		              private sf::NonCopyable
	{
	public:
		SceneNode();

	public:
		typedef std::unique_ptr<SceneNode> Ptr;

		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

		void update(sf::Time dt);

		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;
		
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void updateChildren(sf::Time dt);
		void updateCurrent(sf::Time dt);
		

		
	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;

	};
}