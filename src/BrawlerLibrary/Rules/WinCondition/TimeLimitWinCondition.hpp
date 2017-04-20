
#pragma once

#include "WinCondition.hpp"

namespace BrawlerLibrary
{
	class TimeLimitWinCondition : public WinCondition
	{
	private:
		unsigned int timeLimit; //in minutes;
	public:
		TimeLimitWinCondition();
		virtual ~TimeLimitWinCondition();
		
		void setTimeLimit(unsigned int minutes);
		unsigned int getTimeLimit() const;
	};
}
