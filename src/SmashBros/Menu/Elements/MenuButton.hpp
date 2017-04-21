
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	class MenuButton : public fgl::ButtonElement
	{
	public:
		MenuButton();
		MenuButton(fgl::AssetManager* assetManager, const fgl::String& imagePath);
		
		virtual void update(fgl::ApplicationData appData) override;
		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
		void setHoverPulsingEnabled(bool enabled);
		bool isHoverPulsingEnabled() const;
		
	private:
		bool hoverPulsingEnabled;
		bool hoverPulseGrowing;
		float hoverPulseScale;
	};
}
