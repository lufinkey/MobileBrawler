
#include "StageSelectScreen.hpp"
#include "StageSelect_StageIcon.hpp"
#include "StageSelect_StagePreview.hpp"

namespace SmashBros
{
	namespace Menu
	{
		using namespace StageSelect;
		
		StageSelectScreen::StageSelectScreen(MenuData* menuData, Rules* rules)
			: BaseMenuScreen(menuData),
			rules(rules)
		{
			auto headerbarElement = getHeaderbarElement();
			headerbarElement->setVisible(false);

			iconsElement = new fgl::ScreenElement();
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

			previewElement = new StagePreview(menuData);
			previewElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.05, fgl::LAYOUTVALUE_RATIO);
			previewElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.20, fgl::LAYOUTVALUE_RATIO);
			previewElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 0.20, fgl::LAYOUTVALUE_RATIO);
			previewElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.10, fgl::LAYOUTVALUE_RATIO);

			getElement()->addChildElement(iconsElement);
			getElement()->addChildElement(previewElement);
		}
		
		StageSelectScreen::~StageSelectScreen()
		{
			for(auto& icon : icons)
			{
				delete icon;
			}
			delete iconsElement;
			delete previewElement;
		}
		
		Rules* StageSelectScreen::getRules() const
		{
			return rules;
		}
		
		StageSelect::StagePreview* StageSelectScreen::getStagePreviewElement() const
		{
			return previewElement;
		}
		
		const fgl::ArrayList<StageSelect::StageIcon*>& StageSelectScreen::getStageIcons() const
		{
			return icons;
		}
		
		void StageSelectScreen::reloadIcons()
		{
			for(auto& icon : icons)
			{
				icon->removeFromParentElement();
				delete icon;
			}
			icons.clear();

			auto menuData = getMenuData();
			auto stageLoader = menuData->getModuleManager()->getStageLoader();
			
			auto& stages = stageLoader->getStages();
			
			fgl::RectD bounds(0.3, 0.2, 0.9, 0.9);
			double bounds_w = bounds.right - bounds.left;
			double bounds_h = bounds.bottom - bounds.top;
			
			size_t cols = 6;
			size_t rows = 6;
			double icon_width = bounds_w / (double)cols;
			double icon_height = bounds_h / (double)rows;
			
			for(size_t i=0; i<stages.size(); i++)
			{
				auto& info = stages[i];
				StageIcon* icon = new StageIcon(menuData, info);
				size_t col = i%cols;
				size_t row = i/cols;
				double icon_left = bounds.left+(((double)col)*icon_width);
				double icon_top = bounds.top+(((double)row)*icon_height);
				icon->setLayoutRule(fgl::LAYOUTRULE_LEFT, icon_left, fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_TOP, icon_top, fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 1.0-(icon_left+icon_width), fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 1.0-(icon_top+icon_height), fgl::LAYOUTVALUE_RATIO);
				iconsElement->addChildElement(icon);
				icons.add(icon);
			}
		}
		
		void StageSelectScreen::onUpdate(const fgl::ApplicationData& appData)
		{
			BaseMenuScreen::onUpdate(appData);
			previewElement->setImage(nullptr);
			for(auto& icon : icons)
			{
				auto buttonState = icon->getButtonState();
				if(buttonState==fgl::ButtonElement::BUTTONSTATE_HOVERED || buttonState==fgl::ButtonElement::BUTTONSTATE_PRESSED)
				{
					auto& stageInfo = icon->getStageInfo();
					auto texture = getMenuData()->getModuleManager()->getStagePreview(stageInfo.getIdentifier());
					previewElement->setImage(texture);
					break;
				}
			}
		}
	}
}
