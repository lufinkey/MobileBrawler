
#pragma once

#include "../Application/ApplicationData.h"

namespace GameLibrary
{
	class Updateable
	{
	public:
		/*! virtual destructor*/
		virtual ~Updateable(){}
		
		/*! Updates any properties of the Updateable subclass.
			\param appData specifies information about the Application updating the Updateable, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void update(ApplicationData appData) = 0;
	};
}
