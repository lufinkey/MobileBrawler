
#include "Global.h"

namespace SmashBros
{
	Vector2f getScreenCoords(float ratX, float ratY)
	{
		return Vector2f(ratX*SMASHBROS_WINDOWWIDTH, ratY*SMASHBROS_WINDOWHEIGHT);
	}
	
	Vector2f getScreenCoords(const Vector2f&rat)
	{
		return getScreenCoords(rat.x, rat.y);
	}
}
