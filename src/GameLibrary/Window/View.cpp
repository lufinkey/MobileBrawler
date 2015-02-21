
#include "View.h"

namespace GameLibrary
{
	View::View() : View(640,480)
	{
		//
	}

	View::View(const View&view)
	{
		size = view.size;
		zoom = view.zoom;
		matchWindow = view.matchWindow;
		letterboxed = view.letterboxed;
	}

	View::View(const Vector2d& size) : View(size.x,size.y)
	{
		//
	}

	View::View(double width, double height)
	{
		size.x = width;
		size.y = height;
		zoom = 1;
		matchWindow = false;
		letterboxed = true;
	}

	View::~View()
	{
		//
	}
	
	void View::setSize(double width, double height)
	{
		size.x = width;
		size.y = height;
	}

	void View::setSize(const Vector2d& size)
	{
		setSize(size.x, size.y);
	}

	const Vector2d& View::getSize() const
	{
		return size;
	}

	void View::setZoom(double z)
	{
		zoom = z;
	}

	double View::getZoom() const
	{
		return zoom;
	}

	void View::setMatchesWindow(bool toggle)
	{
		matchWindow = toggle;
	}

	bool View::matchesWindow() const
	{
		return matchWindow;
	}

	void View::setLetterboxed(bool toggle)
	{
		letterboxed = toggle;
	}

	bool View::isLetterboxed() const
	{
		return letterboxed;
	}
}