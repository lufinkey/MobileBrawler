
#pragma once

#include <GameLibrary/GameLibrary.h>

#define SMASHBROS_WINDOWWIDTH 900
#define SMASHBROS_WINDOWHEIGHT 600

namespace SmashBros
{
	using namespace GameLibrary;
	
	class Global
	{
	public:
		static Vector2f getScreenCoords(float ratX, float ratY);
		static Vector2f getScreenCoords(const Vector2f&rat);
	};
}
