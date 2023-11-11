#include "ariespch.h"
#include "SceneNode.h"
namespace aries
{
	class Entity : public SceneNode
	{
	public:
		void setVelocity(sf::Vector2f);
		void setVelocity(float vx, float vy);
		sf::Vector2f getVelocity() const;
		
	private:
		sf::Vector2f mVelocity;
	};
}