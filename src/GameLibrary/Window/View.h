
#include "../Utilities/Geometry/Vector2.h"

#pragma once

namespace GameLibrary
{
	class View
	{
		friend class Graphics;
	private:
		Vector2f size;
		float zoom;
		bool matchWindow;
		bool letterboxed;
		
	public:
		View();
		View(const View&);
		View(const Vector2f& size);
		View(float width, float height);
		~View();
		
		void setSize(float width, float height);
		void setSize(const Vector2f& size);
		const Vector2f& getSize() const;

		void setZoom(float zoom);
		float getZoom() const;

		void setMatchesWindow(bool toggle);
		bool matchesWindow() const;

		void setLetterboxed(bool toggle);
		bool isLetterboxed() const;
	};
}
