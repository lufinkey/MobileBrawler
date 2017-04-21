
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	class MenuButton : public fgl::ButtonElement
	{
	public:
		MenuButton();
		
		virtual void update(fgl::ApplicationData appData) override;
		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
	private:
		bool hoverPulsingEnabled;
		bool hoverPulseGrowing;
		float hoverPulseScale;
	};
}
