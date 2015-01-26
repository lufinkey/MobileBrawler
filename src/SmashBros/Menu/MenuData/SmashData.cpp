
#include "SmashData.h"

namespace SmashBros
{
	SmashData::SmashData(Window*win, CharacterLoader*charLoader, Rules*ruls, const MenuData&menuData) : menuData(menuData)
	{
		window = win;
		characterLoader = charLoader;
		rules = ruls;
	}
	
	SmashData::SmashData(const SmashData&smashData) : menuData(smashData.menuData)
	{
		window = smashData.window;
		characterLoader = smashData.characterLoader;
		rules = smashData.rules;
	}
	
	SmashData::~SmashData()
	{
		//
	}
	
	SmashData& SmashData::operator=(const SmashData&smashData)
	{
		menuData = smashData.menuData;
		window = smashData.window;
		characterLoader = smashData.characterLoader;
		rules = smashData.rules;
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
	
	const MenuData& SmashData::getMenuData() const
	{
		return menuData;
	}
	
	Window* SmashData::getWindow() const
	{
		return window;
	}
	
	CharacterLoader* SmashData::getCharacterLoader() const
	{
		return characterLoader;
	}
	
	Rules* SmashData::getRules() const
	{
		return rules;
	}
	
	void SmashData::setRules(Rules*ruls)
	{
		rules = ruls;
	}
}
