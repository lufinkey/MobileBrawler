
#pragma once

#include "WinCondition.hpp"

namespace SmashBros
{
	class TimeLimitWinCondition : public WinCondition
	{
	public:
		TimeLimitWinCondition();
		virtual ~TimeLimitWinCondition();
		
		void setTimeLimit(unsigned int minutes);
		unsigned int getTimeLimit() const;

	private:
		unsigned int timeLimit; //in minutes;
	};
}
