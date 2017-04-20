
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashLib
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
