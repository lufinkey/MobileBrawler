
#pragma once

#include <BrawlerLibrary/BrawlerLibrary.h>
#include "../../Load/MenuLoad.h"
#include "../../Load/ModuleLoad.h"

namespace SmashBros
{
	using namespace BrawlerLibrary;
	
	class SmashData
	{
	private:
		Window* window;
		MenuLoad* menuData;
		ModuleLoad* moduleData;
		Rules* rules;
		
	public:
		SmashData(Window*window, Rules*rules, MenuLoad*menuData, ModuleLoad*moduleData);
		SmashData(const SmashData&);
		~SmashData();
		
		SmashData& operator=(const SmashData&);
		
		Vector2f getScreenCoords(float ratX, float ratY) const;
		Vector2f getScreenCoords(const Vector2f&rat) const;
		
		Window* getWindow() const;
		Rules* getRules() const;
		MenuLoad* getMenuData() const;
		ModuleLoad* getModuleData() const;
		
		void setRules(Rules*);
	};
}
