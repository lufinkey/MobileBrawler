
#include "TimeLimitWinCondition.hpp"

namespace BrawlerLibrary
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
