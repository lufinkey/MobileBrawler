
#include "Global.h"

namespace SmashBros
{
	Vector2f Global::getScreenCoords(float ratX, float ratY)
	{
		return Vector2f(ratX*SMASHBROS_WINDOWWIDTH, ratY*SMASHBROS_WINDOWHEIGHT);
	}
	
	Vector2f Global::getScreenCoords(const Vector2f&rat)
	{
		return getScreenCoords(rat.x, rat.y);
	}
}
