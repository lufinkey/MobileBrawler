
#include "CharacterSelect_ReadyToFightBanner.hpp"
#include "CharacterSelectScreen.hpp"
#include "CharacterSelect_PlayerChip.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			ReadyToFightBanner::ReadyToFightBanner(CharacterSelectScreen* charSelectScreen, fgl::AssetManager* assetManager)
				: charSelectScreen(charSelectScreen)
			{
				auto backgroundImage = assetManager->loadTexture("characterselect/readytofight_banner.png");
				setBackgroundImage(backgroundImage, fgl::ButtonElement::BUTTONSTATE_NORMAL);

				setTintColor(fgl::Color::BLUE, fgl::ButtonElement::BUTTONSTATE_PRESSED);
				setTintColor(fgl::Color::LIGHTBLUE, fgl::ButtonElement::BUTTONSTATE_HOVERED);

				setTapHandler([=]{
					charSelectScreen->proceedToFight();
				});

				if(backgroundImage!=nullptr)
				{
					setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, (double)backgroundImage->getWidth()/(double)backgroundImage->getHeight(), fgl::LAYOUTVALUE_RATIO);
				}
				else
				{
					setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 0);
				}
				setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			}
		}
	}
}
