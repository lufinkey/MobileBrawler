
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	using namespace BrawlerLibrary;
	
	class MenuData
	{
	private:
		AssetManager* assetManager;
		
	public:
		MenuData(AssetManager*assetManager);
		~MenuData();
		
		MenuData& operator=(const MenuData&);

		AssetManager* getAssetManager() const;
	};
	
	class SmashData
	{
	private:
		MenuData menuData;
		Window* window;
		CharacterLoader*characterLoader;
		
	public:
		SmashData(Window*window, CharacterLoader*characterLoader, const MenuData&menuData);
		SmashData(const SmashData&);
		~SmashData();
		
		SmashData& operator=(const SmashData&);
		
		Vector2f getScreenCoords(float ratX, float ratY) const;
		Vector2f getScreenCoords(const Vector2f&rat) const;
		
		const MenuData& getMenuData() const;
		Window* getWindow() const;
		CharacterLoader* getCharacterLoader() const;
	};
}
