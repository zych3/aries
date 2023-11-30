#include "CommandQueue.h"

void aries::CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

aries::Command aries::CommandQueue::pop()
{
	auto res = mQueue.back();
	mQueue.pop();
	return res;
	
}

bool aries::CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
