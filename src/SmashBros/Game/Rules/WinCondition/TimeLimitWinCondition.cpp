
#include "TimeLimitWinCondition.hpp"

namespace SmashBros
{
	TimeLimitWinCondition::TimeLimitWinCondition()
	{
		timeLimit = 2;
	}
	
	TimeLimitWinCondition::~TimeLimitWinCondition()
	{
		//
	}
	
	void TimeLimitWinCondition::setTimeLimit(unsigned int minutes)
	{
		timeLimit = minutes;
	}
	
	unsigned int TimeLimitWinCondition::getTimeLimit() const
	{
		return timeLimit;
	}
}
