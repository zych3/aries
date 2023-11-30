#include "ariespch.h"
#include "SceneNode.h"
namespace aries
{
	class Entity : public SceneNode
	{
	public:
		 void setVelocity(sf::Vector2f);
		 void setVelocity(float vx, float vy);
		 sf::Vector2f getVelocity() const { return mVelocity; }


	private:

		sf::Vector2f mVelocity;
	};

	inline void Entity::setVelocity(sf::Vector2f vec)
	{
		mVelocity = vec;
	}

	inline void Entity::setVelocity(float vx, float vy)
	{
		mVelocity = sf::Vector2f(vx, vy);
	}

	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)>
		derivedAction(Function fn)
	{
		return[=](SceneNode& node, sf::Time dt)
		{
			//check if ok to cast
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			//call function with downcasted node as arg
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}
