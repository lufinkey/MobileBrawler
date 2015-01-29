
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class WinCondition
	{
	protected:
		GameLibrary::Dictionary properties;
	public:
		WinCondition();
		virtual ~WinCondition();
	};
}
