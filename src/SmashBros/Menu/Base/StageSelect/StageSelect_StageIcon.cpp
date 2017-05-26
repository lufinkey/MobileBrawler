
#include "StageSelect_StageIcon.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			StageIcon::StageIcon(MenuData* menuData, StageInfo stageInfo)
				: stageInfo(stageInfo)
			{
				auto assetManager = menuData->getAssetManager();

				auto texture = menuData->getModuleManager()->getStageIcon(stageInfo.getIdentifier());
				setBackgroundImage(texture, fgl::ButtonElement::BUTTONSTATE_NORMAL);

				overlayElement = new fgl::ImageElement(assetManager->loadTexture("stageselect/icon_frame.png"), fgl::ImageElement::DISPLAY_FIT_CENTER);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
				addChildElement(overlayElement);
			}
			
			StageIcon::~StageIcon()
			{
				delete overlayElement;
			}
			
			const StageInfo& StageIcon::getStageInfo() const
			{
				return stageInfo;
			}
		}
	}
}
