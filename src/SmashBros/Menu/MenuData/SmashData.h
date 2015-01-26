
#pragma once

#include "MenuData.h"
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace BrawlerLibrary;
	
	class SmashData
	{
	private:
		MenuData menuData;
		Window* window;
		CharacterLoader*characterLoader;
		Rules* rules;
		
	public:
		SmashData(Window*window, CharacterLoader*characterLoader, Rules*rules, const MenuData&menuData);
		SmashData(const SmashData&);
		~SmashData();
		
		SmashData& operator=(const SmashData&);
		
		Vector2f getScreenCoords(float ratX, float ratY) const;
		Vector2f getScreenCoords(const Vector2f&rat) const;
		
		const MenuData& getMenuData() const;
		Window* getWindow() const;
		CharacterLoader* getCharacterLoader() const;
		Rules* getRules() const;
		
		void setRules(Rules*);
	};
}
