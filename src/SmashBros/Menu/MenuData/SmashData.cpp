
#include "SmashData.h"

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
	
	Vector2f SmashData::getScreenCoords(float ratX, float ratY) const
	{
		if(window == nullptr)
		{
			return Vector2f(0,0);
		}
		Vector2f viewSize = window->getView()->getSize();
		return Vector2f(ratX*viewSize.x, ratY*viewSize.y);
	}
	
	Vector2f SmashData::getScreenCoords(const Vector2f&rat) const
	{
		if(window == nullptr)
		{
			return Vector2f(0,0);
		}
		Vector2f viewSize = window->getView()->getSize();
		return Vector2f(rat.x*viewSize.x, rat.y*viewSize.y);
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
