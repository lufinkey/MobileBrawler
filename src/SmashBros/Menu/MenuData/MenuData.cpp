
#include "MenuData.h"

namespace SmashBros
{
	MenuData::MenuData(const MenuData&menuData)
	{
		assetManager = menuData.assetManager;
		menuBarPlacement = menuData.menuBarPlacement;
		rulesBarPlacement = menuData.rulesBarPlacement;
	}
	
	MenuData::MenuData(AssetManager*assetMgr, const Dictionary&menuBarPlace, const Dictionary&rulesBarPlace)
	{
		assetManager = assetMgr;
		menuBarPlacement = menuBarPlace;
		rulesBarPlacement = rulesBarPlace;
	}
	
	MenuData::~MenuData()
	{
		//
	}
	
	MenuData& MenuData::operator=(const MenuData&menuData)
	{
		assetManager = menuData.assetManager;
		menuBarPlacement = menuData.menuBarPlacement;
		rulesBarPlacement = menuData.rulesBarPlacement;
		return *this;
	}
	
	AssetManager* MenuData::getAssetManager() const
	{
		return assetManager;
	}
	
	const Dictionary& MenuData::getMenuBarPlacement() const
	{
		return menuBarPlacement;
	}
	
	const Dictionary& MenuData::getRulesBarPlacement() const
	{
		return rulesBarPlacement;
	}
}
