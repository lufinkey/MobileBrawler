
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	namespace Menu
	{
		class MenuBar : public fgl::ScreenElement
		{
		public:
			MenuBar(fgl::AssetManager* assetManager, const fgl::String& label);
			MenuBar(fgl::AssetManager* assetManager, const fgl::String& label, const fgl::Dictionary& properties);
			virtual ~MenuBar();
			
			fgl::ImageElement* getBackgroundElement() const;
			fgl::TextElement* getLabelElement() const;

			static fgl::Dictionary getDefaultProperties(fgl::AssetManager* assetManager);
			
		private:
			void applyProperties(const fgl::Dictionary& properties);
			
			fgl::ImageElement* backgroundElement;
			fgl::TextElement* labelElement;
		};
	}
}
