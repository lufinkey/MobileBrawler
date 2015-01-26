
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	class WinCondition
	{
	protected:
		Dictionary properties;
	public:
		WinCondition();
		virtual ~WinCondition();
	};
}
