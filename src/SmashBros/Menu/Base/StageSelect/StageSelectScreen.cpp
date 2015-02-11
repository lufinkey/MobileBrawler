
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
			
			RectangleF frame = getFrame();
			autoIconLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
		}
		
		StageSelectScreen::~StageSelectScreen()
		{
			//items are deleted through the MenuScreen already, since they were added to it
		}
		
		void StageSelectScreen::onFrameChange()
		{
			BaseMenuScreen::onFrameChange();
			RectangleF frame = getFrame();
			autoIconLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
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
			autoIconLayout.clear();
			
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			ArrayList<StageInfo>& stages = smashData.getModuleData()->getStageLoader()->getStages();
			
			RectF bounds(0.3f, 0.2f, 0.9f, 0.9f);
			float bounds_w = bounds.right - bounds.left;
			float bounds_h = bounds.bottom - bounds.top;
			
			unsigned int cols = 6;
			unsigned int rows = 6;
			float icon_width = bounds_w / (float)cols;
			float icon_height = bounds_h / (float)rows;
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getStageLoader()->getAssetManager();
			for(unsigned int i=0; i<stages.size(); i++)
			{
				StageInfo& info = stages.get(i);
				StageIcon* icon = new StageIcon(info, 0, 0, loaderAssetManager);
				unsigned int col = i%cols;
				unsigned int row = i/cols;
				float icon_left = bounds.left+(((float)col)*icon_width);
				float icon_top = bounds.top+(((float)row)*icon_height);
				autoIconLayout.add(RectF(icon_left, icon_top, icon_left+icon_width, icon_top+icon_height), icon);
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
			
			Vector2f topleft = smashData.getScreenCoords(0.05f, 0.2f);
			Vector2f bottomright = smashData.getScreenCoords(0.25f, 0.9f);
			preview = new StagePreview(smashData.getModuleData()->getStageLoader()->getAssetManager());
			getElement()->addChildElement(RectF(0.05f, 0.2f, 0.25f, 0.9f), preview);
		}
		
		void StageSelectScreen::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
		}
		
		void StageSelectScreen::onDraw(ApplicationData appData, Graphics graphics) const
		{
			BaseMenuScreen::onDraw(appData, graphics);
		}
		
		void StageSelectScreen::onItemHover(unsigned int index)
		{
			Actor* item = getItem(index);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				StageSelect::StageIcon* icon = icons.get(i);
				if(item == icon)
				{
					onStageIconHover(icon);
					return;
				}
			}
		}
		
		void StageSelectScreen::onItemHoverFinish(unsigned int index)
		{
			Actor* item = getItem(index);
			for(unsigned int i=0; i<icons.size(); i++)
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
