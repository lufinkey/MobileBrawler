
#include "SmashData.hpp"

namespace SmashBros
{
	SmashData::SmashData(Window*win, MenuLoad*menuDat, ModuleLoad*moduleDat)
	{
		window = win;
		menuData = menuDat;
		moduleData = moduleDat;
	}
	
	SmashData::SmashData(const SmashData&smashData)
	{
		window = smashData.window;
		menuData = smashData.menuData;
		moduleData = smashData.moduleData;
	}
	
	SmashData::~SmashData()
	{
		//
	}
	
	SmashData& SmashData::operator=(const SmashData&smashData)
	{
		window = smashData.window;
		menuData = smashData.menuData;
		moduleData = smashData.moduleData;
		return *this;
	}
	
	Vector2d SmashData::getScreenCoords(double ratX, double ratY) const
	{
		if(window == nullptr)
		{
			return Vector2d(0,0);
		}
		Vector2d viewSize = window->getViewport()->getSize();
		return Vector2d(ratX*viewSize.x, ratY*viewSize.y);
	}
	
	Vector2d SmashData::getScreenCoords(const Vector2d&rat) const
	{
		if(window == nullptr)
		{
			return Vector2d(0,0);
		}
		Vector2d viewSize = window->getViewport()->getSize();
		return Vector2d(rat.x*viewSize.x, rat.y*viewSize.y);
	}
	
	Window* SmashData::getWindow() const
	{
		return window;
	}
	
	MenuLoad* SmashData::getMenuData() const
	{
		return menuData;
	}
	
	ModuleLoad* SmashData::getModuleData() const
	{
		return moduleData;
	}
}
