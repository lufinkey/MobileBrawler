
#pragma once

#include <SmashLib/SmashLib.hpp>
#include "../../Load/MenuLoad.hpp"
#include "../../Load/ModuleLoad.hpp"

using namespace SmashLib;

namespace SmashBros
{
	class SmashData
	{
	public:
		SmashData(Window* window, MenuLoad*menuData, ModuleLoad*moduleData);
		SmashData(const SmashData&);
		~SmashData();
		
		SmashData& operator=(const SmashData&);
		
		Vector2d getScreenCoords(double ratX, double ratY) const;
		Vector2d getScreenCoords(const Vector2d&rat) const;
		
		Window* getWindow() const;
		MenuLoad* getMenuData() const;
		ModuleLoad* getModuleData() const;
		
		void setRules(Rules*);
		
	private:
		Window* window;
		MenuLoad* menuData;
		ModuleLoad* moduleData;
	};
}
