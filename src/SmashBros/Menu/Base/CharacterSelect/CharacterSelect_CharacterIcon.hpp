
#pragma once

#include "../../MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class CharacterIcon : public fgl::ScreenElement
			{
				friend class ::SmashBros::Menu::CharacterSelectScreen;
			public:
				CharacterIcon(MenuData* menuData, CharacterInfo info);
				virtual ~CharacterIcon();

				virtual void layoutChildElements() override;

				fgl::RectangleD getChipFrame() const;
				
				const CharacterInfo& getCharacterInfo() const;

			private:
				CharacterInfo characterInfo;

				fgl::ImageElement* iconFrameElement;
				fgl::ImageElement* iconElement;
			};
		}
	}
}
