#pragma once

#include "ariespch.h"


namespace aries
{
	struct Command;

	namespace Category
	{
		enum Type
		{
			None = 0,		//those bit shifts allow
			Scene = 1 << 0, //to combine different categories
			Player = 1 << 1,//using bitwise OR operator 
			Enemy = 1 << 3  // :D 

		};
	}



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

		virtual unsigned int getCategory() const { return Category::Scene; }
		void onCommand(const Command& command, sf::Time dt);
		
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void updateChildren(sf::Time dt);
		void updateCurrent(sf::Time dt);
		
		

		
	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;

	};

	struct Command
	{
		std::function<void(aries::SceneNode&, sf::Time)> action;
		
		unsigned int category;
	};



	

	
}
