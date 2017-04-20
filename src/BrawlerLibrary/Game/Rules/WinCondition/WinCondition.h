
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace BrawlerLibrary
{
	class WinCondition
	{
	protected:
		fgl::Dictionary properties;
	public:
		WinCondition();
		virtual ~WinCondition();
	};
}
