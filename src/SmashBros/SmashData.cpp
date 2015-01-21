
#include "SmashData.h"

namespace SmashBros
{
	MenuData::MenuData(AssetManager*assetMgr)
	{
		assetManager = assetMgr;
	}
	
	MenuData::~MenuData()
	{
		//
	}
	
	MenuData& MenuData::operator=(const MenuData&menuData)
	{
		assetManager = menuData.assetManager;
		return *this;
	}
	
	AssetManager* MenuData::getAssetManager() const
	{
		return assetManager;
	}
	
	SmashData::SmashData(Window*window, CharacterLoader*characterLoader, const MenuData&menuData) : window(window), characterLoader(characterLoader), menuData(menuData)
	{
		//
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
}
