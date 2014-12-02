
#include "View.h"

namespace GameLibrary
{
	View::View() : View(640,480)
	{
		//
	}

	View::View(const Vector2f& size) : View(size.x,size.y)
	{
		//
	}

	View::View(float width, float height)
	{
		size.x = width;
		size.y = height;
		position.x = 0;
		position.y = 0;
		matchWindow = false;
		letterboxed = true;
	}

	View::~View()
	{
		//
	}
		
	void View::translate(float x, float y)
	{
		position.x += x;
		position.y += y;
	}

	void View::translate(const Vector2f&delta)
	{
		translate(delta.x, delta.y);
	}
		
	void View::setTranslation(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void View::setTranslation(const Vector2f&translation)
	{
		setTranslation(translation.x, translation.y);
	}

	const Vector2f& View::getTranslation()
	{
		return position;
	}
		
	void View::setSize(float width, float height)
	{
		size.x = width;
		size.y = height;
	}

	void View::setSize(const Vector2f& size)
	{
		setSize(size.x, size.y);
	}

	const Vector2f& View::getSize()
	{
		return size;
	}

	void View::setMatchesWindow(bool toggle)
	{
		matchWindow = toggle;
	}

	bool View::matchesWindow()
	{
		return matchWindow;
	}

	void View::setLetterboxed(bool toggle)
	{
		letterboxed = toggle;
	}

	bool View::isLetterboxed()
	{
		return letterboxed;
	}
}