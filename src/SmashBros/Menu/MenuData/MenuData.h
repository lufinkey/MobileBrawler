
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	class MenuData
	{
	private:
		AssetManager* assetManager;
		Dictionary menuBarPlacement;
		Dictionary rulesBarPlacement;
		
	public:
		MenuData(const MenuData&);
		MenuData(AssetManager*assetManager, const Dictionary&menuBarPlacement, const Dictionary&rulesBarPlacement);
		~MenuData();
		
		MenuData& operator=(const MenuData&);
		
		AssetManager* getAssetManager() const;
		const Dictionary& getMenuBarPlacement() const;
		const Dictionary& getRulesBarPlacement() const;
	};
}
