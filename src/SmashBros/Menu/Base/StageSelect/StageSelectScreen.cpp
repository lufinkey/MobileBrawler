
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
			
			RectangleD frame = getFrame();
			autoIconLayoutMgr.setFrame(RectangleD(0,0,frame.width,frame.height));
		}
		
		StageSelectScreen::~StageSelectScreen()
		{
			//items are deleted through the MenuScreen already, since they were added to it
		}
		
		void StageSelectScreen::onFrameChange()
		{
			BaseMenuScreen::onFrameChange();
			RectangleD frame = getFrame();
			autoIconLayoutMgr.setFrame(RectangleD(0,0,frame.width,frame.height));
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
			autoIconLayoutMgr.clear();
			
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
				autoIconLayoutMgr.add(RectD(icon_left, icon_top, icon_left+icon_width, icon_top+icon_height), icon);
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
			getElement()->addChildElement(RectD(0.05, 0.2, 0.25, 0.9), preview);
		}
		
		void StageSelectScreen::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
		}
		
		void StageSelectScreen::onDraw(ApplicationData appData, Graphics graphics) const
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
