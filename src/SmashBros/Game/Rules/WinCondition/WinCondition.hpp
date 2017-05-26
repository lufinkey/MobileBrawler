
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
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
