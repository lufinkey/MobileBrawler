
#include "../Utilities/Geometry/Vector2.h"

#pragma once

namespace GameLibrary
{
	class View
	{
	private:
		Vector2f size;
		Vector2f position;
		bool matchWindow;
		bool letterboxed;
		
	public:
		View();
		View(const Vector2i& size);
		View(float width, float height);
		~View();
		
		void translate(float x, float y);
		void translate(const Vector2f&delta);
		
		void setPosition(float x, float y);
		void setPosition(const Vector2f&position);
		const Vector2f& getPosition();
		
		void setSize(float width, float height);
		void setSize(const Vector2f& size);
		const Vector2f& getSize();

		void setMatchesWindow(bool toggle);
		bool matchesWindow();

		void setLetterboxed(bool toggle);
		bool isLetterboxed();
	};
}
