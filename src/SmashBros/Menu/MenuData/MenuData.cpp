
#include "MenuData.h"

namespace SmashBros
{
	MenuData::MenuData(const MenuData&menuData)
	{
		assetManager = menuData.assetManager;
		menuBarProperties = menuData.menuBarProperties;
		rulesBarProperties = menuData.rulesBarProperties;
	}
	
	MenuData::MenuData(AssetManager*assetMgr, const Dictionary&menuBarProps, const Dictionary&rulesBarProps)
	{
		assetManager = assetMgr;
		menuBarProperties = menuBarProps;
		rulesBarProperties = rulesBarProps;
	}
	
	MenuData::~MenuData()
	{
		//
	}
	
	MenuData& MenuData::operator=(const MenuData&menuData)
	{
		assetManager = menuData.assetManager;
		menuBarProperties = menuData.menuBarProperties;
		rulesBarProperties = menuData.rulesBarProperties;
		return *this;
	}
	
	AssetManager* MenuData::getAssetManager() const
	{
		return assetManager;
	}
	
	const Dictionary& MenuData::getMenuBarProperties() const
	{
		return menuBarProperties;
	}
	
	const Dictionary& MenuData::getRulesBarProperties() const
	{
		return rulesBarProperties;
	}
}
