
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
			iconGrid = nullptr;
		}
		
		StageSelectScreen::~StageSelectScreen()
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
			}
			
			for(unsigned int i=0; i<previews.size(); i++)
			{
				delete previews.get(i);
			}
			icons.clear();
		}
		
		Rules* StageSelectScreen::getRules() const
		{
			return rules;
		}
		
		StageLoader* StageSelectScreen::getStageLoader() const
		{
			return stageLoader;
		}
		
		const ArrayList<StageSelect::StagePreview*>& StageSelectScreen::getStagePreviews() const
		{
			return previews;
		}
		
		const ArrayList<StageSelect::StageIcon*>& StageSelectScreen::getStageIcons() const
		{
			return icons;
		}
		
		void StageSelectScreen::reloadIcons(const SmashData&smashData)
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
				iconGrid = nullptr;
			}
			
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			ArrayList<StageInfo>& stages = smashData.getModuleData()->getStageLoader()->getStages();
			
			Vector2f topleft = smashData.getScreenCoords(0.3f, 0.2f);
			Vector2f bottomright = smashData.getScreenCoords(0.9f, 0.9f);
			RectangleF stageSelectRect(topleft.x, topleft.y, bottomright.x-topleft.x, bottomright.y-topleft.y);
			unsigned int cols = 6;
			unsigned int rows = 6;
			float icon_width = stageSelectRect.width / (float)cols;
			float icon_height = stageSelectRect.height / (float)rows;
			Vector2f icon_size(icon_width, icon_height);
			
			iconGrid = new ActorGrid(Vector2f(stageSelectRect.x+(icon_width/2), stageSelectRect.y+(icon_height/2)), cols, Vector2f(icon_width, icon_height));
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getStageLoader()->getAssetManager();
			for(unsigned int i=0; i<stages.size(); i++)
			{
				StageInfo& info = stages.get(i);
				StageIcon* icon = new StageIcon(info, 0, 0, loaderAssetManager);
				icon->Actor::scaleToFit(icon_size);
				icons.add(icon);
				iconGrid->add(icon);
				addItem(icon);
			}
		}
		
		void StageSelectScreen::reloadPreviews(const SmashData&smashData)
		{
			//
		}
		
		void StageSelectScreen::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
		}
		
		void StageSelectScreen::onDraw(ApplicationData appData, Graphics graphics) const
		{
			BaseMenuScreen::onDraw(appData, graphics);
		}
	}
}
