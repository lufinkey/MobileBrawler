
#pragma once

#include <BrawlerLibrary/BrawlerLibrary.hpp>
#include "../../Load/MenuLoad.hpp"
#include "../../Load/ModuleLoad.hpp"

using namespace BrawlerLibrary;

namespace SmashBros
{
	class SmashData
	{
	private:
		Window* window;
		MenuLoad* menuData;
		ModuleLoad* moduleData;
		
	public:
		SmashData(Window*window, MenuLoad*menuData, ModuleLoad*moduleData);
		SmashData(const SmashData&);
		~SmashData();
		
		SmashData& operator=(const SmashData&);
		
		Vector2d getScreenCoords(double ratX, double ratY) const;
		Vector2d getScreenCoords(const Vector2d&rat) const;
		
		Window* getWindow() const;
		MenuLoad* getMenuData() const;
		ModuleLoad* getModuleData() const;
		
		void setRules(Rules*);
	};
}
