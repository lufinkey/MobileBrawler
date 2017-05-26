
#include "CharacterSelect_CharacterIcon.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			CharacterIcon::CharacterIcon(MenuData* menuData, CharacterInfo characterInfo)
				: characterInfo(characterInfo)
			{
				auto assetManager = menuData->getAssetManager();
				auto iconImg = menuData->getModuleManager()->getCharacterIcon(characterInfo.getIdentifier());
				auto iconFrameImg = assetManager->loadTexture("characterselect/icon_frame.png");

				iconFrameElement = new fgl::ImageElement(iconFrameImg, fgl::ImageElement::DISPLAY_FIT_CENTER);
				iconFrameElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				iconFrameElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				iconFrameElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				iconFrameElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

				iconElement = new fgl::ImageElement(iconImg);

				addChildElement(iconElement);
				addChildElement(iconFrameElement);
			}
			
			CharacterIcon::~CharacterIcon()
			{
				delete iconElement;
				delete iconFrameElement;
			}

			void CharacterIcon::layoutChildElements()
			{
				ScreenElement::layoutChildElements();
				auto iconFrame = iconFrameElement->getImageDisplayFrame();
				iconElement->setFrame(iconFrame);
			}

			fgl::RectangleD CharacterIcon::getChipFrame() const
			{
				auto frame = getFrame();
				auto iconFrame = iconFrameElement->getImageDisplayFrame();
				iconFrame.x += frame.x;
				iconFrame.y += frame.y;
				return iconFrame;
			}
			
			const CharacterInfo& CharacterIcon::getCharacterInfo() const
			{
				return characterInfo;
			}
		}
	}
}
