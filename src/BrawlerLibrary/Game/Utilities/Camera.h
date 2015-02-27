
#pragma once

#include "../Elements/GameObject.h"

namespace BrawlerLibrary
{
	class Camera
	{
	public:
		Camera();
		virtual ~Camera();

		virtual void update(GameLibrary::ApplicationData appData);
		virtual void updateGraphics(GameLibrary::Graphics*graphics) const;

	private:
		double x;
		double y;
		double zoom;

		GameLibrary::ArrayList<GameObject*> objects;
	};
}
