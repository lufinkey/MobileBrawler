
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	class MenuData
	{
	private:
		AssetManager* assetManager;
		Dictionary menuBarProperties;
		Dictionary rulesBarProperties;
		
	public:
		MenuData(const MenuData&);
		MenuData(AssetManager*assetManager, const Dictionary&menuBarProperties, const Dictionary&rulesBarProperties);
		~MenuData();
		
		MenuData& operator=(const MenuData&);
		
		AssetManager* getAssetManager() const;
		const Dictionary& getMenuBarProperties() const;
		const Dictionary& getRulesBarProperties() const;
	};
}
