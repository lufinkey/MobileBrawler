
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "../../MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class PlayerPanel : public fgl::TouchElement
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			public:
				PlayerPanel(CharacterSelectScreen* charSelectScreen, MenuData* menuData, size_t playerIndex);
				PlayerPanel(CharacterSelectScreen* charSelectScreen, MenuData* menuData, size_t playerIndex, const fgl::Dictionary& properties);
				virtual ~PlayerPanel();
				
				virtual void update(fgl::ApplicationData appData) override;
				
				size_t getPlayerIndex() const;
				
				void applyCharacterInfo(const CharacterInfo* characterInfo);

				static fgl::Dictionary getDefaultProperties(fgl::AssetManager* assetManager);

			protected:
				virtual void onTouchUpInside(const TouchEvent& event) override;

			private:
				void applyProperties(const fgl::Dictionary& dict);

				CharacterSelectScreen* charSelectScreen;
				MenuData* menuData;
				size_t playerIndex;

				fgl::TextureImage* humanBackground;
				fgl::TextureImage* cpuBackground;
				fgl::TextureImage* offBackground;

				fgl::TextureImage* humanOverlay;
				fgl::TextureImage* cpuOverlay;
				fgl::TextureImage* offOverlay;

				fgl::ImageElement* backgroundElement;
				fgl::ImageElement* portraitElement;
				fgl::ImageElement* overlayElement;
				fgl::TextElement* nameLabel;
			};
		}
	}
}
