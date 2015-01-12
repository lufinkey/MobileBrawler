
#pragma once

#include <GameLibraryImport.hpp>

#define SMASHBROS_WINDOWWIDTH 900
#define SMASHBROS_WINDOWHEIGHT 600

namespace SmashBros
{
	Vector2f getScreenCoords(float ratX, float ratY);
	Vector2f getScreenCoords(const Vector2f&rat);
}
