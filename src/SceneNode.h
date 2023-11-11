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

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;

	};
}