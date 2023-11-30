#pragma once
#include <queue>
#include "SceneNode.h"

namespace aries
{
	class CommandQueue
	{
	public:
		void push(const Command& command);
		bool isEmpty() const;
		Command pop();

	private:
		std::queue<Command> mQueue;
		
	};
}






































