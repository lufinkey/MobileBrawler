
#include "StageSelectScreen.h"
#include "StageSelect_StageIcon.h"
#include "StageSelect_StagePreview.h"

namespace SmashBros
{
	namespace Menu
	{
		using namespace StageSelect;
		
		StageSelectScreen::StageSelectScreen(const SmashData&smashData, Rules*ruleData) : BaseMenuScreen(smashData)
		{
			ScreenElement*headerbarElement = getHeaderbarElement();
			headerbarElement->setVisible(false);
			
			rules = ruleData;
			preview = nullptr;
		}
		
		StageSelectScreen::~StageSelectScreen()
		{
			//items are deleted through the MenuScreen already, since they were added to it
		}
		
		void StageSelectScreen::onSizeChange(const Vector2d& oldSize, const Vector2d& newSize)
		{
			BaseMenuScreen::onSizeChange(oldSize, newSize);
			Vector2d size = getSize();
			for(size_t icons_size=icons.size(), i=0; i<icons_size; i++)
			{
				StageIcon* icon = icons.get(i);
				icon->scaleToFit(icon->autoLayoutMgr.calculateFrame(icon->getFrame(), RectangleD(0,0,size.x,size.y)));
			}
		}
		
		Rules* StageSelectScreen::getRules() const
		{
			return rules;
		}
		
		StageLoader* StageSelectScreen::getStageLoader() const
		{
			return stageLoader;
		}
		
		StageSelect::StagePreview* StageSelectScreen::getStagePreview() const
		{
			return preview;
		}
		
		const ArrayList<StageSelect::StageIcon*>& StageSelectScreen::getStageIcons() const
		{
			return icons;
		}
		
		void StageSelectScreen::reloadIcons(const SmashData&smashData)
		{
			for(size_t i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			ArrayList<StageInfo>& stages = smashData.getModuleData()->getStageLoader()->getStages();
			
			RectD bounds(0.3, 0.2, 0.9, 0.9);
			double bounds_w = bounds.right - bounds.left;
			double bounds_h = bounds.bottom - bounds.top;
			
			unsigned int cols = 6;
			unsigned int rows = 6;
			double icon_width = bounds_w / (double)cols;
			double icon_height = bounds_h / (double)rows;
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getStageLoader()->getAssetManager();
			for(size_t i=0; i<stages.size(); i++)
			{
				StageInfo& info = stages.get(i);
				StageIcon* icon = new StageIcon(info, 0, 0, loaderAssetManager);
				unsigned int col = (unsigned int)(i%cols);
				unsigned int row = (unsigned int)(i/cols);
				double icon_left = bounds.left+(((double)col)*icon_width);
				double icon_top = bounds.top+(((double)row)*icon_height);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_LEFT, icon_left, LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_TOP, icon_top, LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 1.0-(icon_left+icon_width), LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1.0-(icon_top+icon_height), LAYOUTVALUE_RATIO);
				icons.add(icon);
				addItem(icon);
			}
		}
		
		void StageSelectScreen::reloadPreview(const SmashData&smashData)
		{
			if(preview != nullptr)
			{
				preview->removeFromParentElement();
				delete preview;
				preview = nullptr;
			}
			
			preview = new StagePreview(smashData.getModuleData()->getStageLoader()->getAssetManager());
			preview->setLayoutRule(LAYOUTRULE_LEFT, 0.05, LAYOUTVALUE_RATIO);
			preview->setLayoutRule(LAYOUTRULE_TOP, 0.20, LAYOUTVALUE_RATIO);
			preview->setLayoutRule(LAYOUTRULE_WIDTH, 0.20, LAYOUTVALUE_RATIO);
			preview->setLayoutRule(LAYOUTRULE_BOTTOM, 0.10, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(preview);
		}
		
		void StageSelectScreen::onUpdate(const ApplicationData& appData)
		{
			BaseMenuScreen::onUpdate(appData);
		}
		
		void StageSelectScreen::onDraw(const ApplicationData& appData, Graphics graphics) const
		{
			BaseMenuScreen::onDraw(appData, graphics);
		}
		
		void StageSelectScreen::onItemHover(size_t index)
		{
			Actor* item = getItem(index);
			for(size_t i=0; i<icons.size(); i++)
			{
				StageSelect::StageIcon* icon = icons.get(i);
				if(item == icon)
				{
					onStageIconHover(icon);
					return;
				}
			}
		}
		
		void StageSelectScreen::onItemHoverFinish(size_t index)
		{
			Actor* item = getItem(index);
			for(size_t i=0; i<icons.size(); i++)
			{
				StageSelect::StageIcon* icon = icons.get(i);
				if(item == icon)
				{
					onStageIconHoverFinish(icon);
					return;
				}
			}
		}
		
		void StageSelectScreen::onStageIconHover(StageIcon*icon)
		{
			preview->setStageInfo(icon->getStageInfo());
		}
		
		void StageSelectScreen::onStageIconHoverFinish(StageIcon*icon)
		{
			preview->setStageInfo(nullptr);
		}
	}
}
