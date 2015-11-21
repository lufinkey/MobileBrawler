
#pragma once

#include "Updateable.h"
#include "Drawable.h"

namespace GameLibrary
{
	/*! An interface class representing an entity that can be updated every frame and drawn to a Window using a Graphics object*/
	class UpdateDrawable : public Updateable, public Drawable
	{
		//Just a combination of the parent classes
	};
}
