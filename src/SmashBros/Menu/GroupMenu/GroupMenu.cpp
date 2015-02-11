
#include "GroupMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupMenu::GroupMenu(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			smashButton = getItem(addItem(RectF(0.05f, 0.2f, 0.55f, 0.6f), new Animation(1, smashData.getMenuData()->getAssetManager(), "buttons/group/smash.png")));
			specialSmashButton = nullptr;//specialSmashButton = getItem(addItem(RectF(0.45f,0.25f,0.5f,0.5f), new Animation(smashData.getMenuData().getAssetManager(), 1, "buttons/group/specialsmash.png"));
			rulesButton = getItem(addItem(RectF(0.275f, 0.6f, 0.725f, 0.9f), new Animation(1, smashData.getMenuData()->getAssetManager(), "buttons/group/rules.png")));
			
			groupSmashData = new GroupSmashData();
			//TODO make the character select screen be loaded when the screen fades to black
			//(create an intermediate screen for while it's loading)
			smashMenu = new GroupSmashCharacterSelectMenu(smashData, *groupSmashData);
			rulesMenu = new GroupRulesMenu(smashData, *groupSmashData);
		}
		
		GroupMenu::~GroupMenu()
		{
			delete smashMenu;
			delete groupSmashData;
		}
		
		void GroupMenu::onItemSelect(unsigned int index)
		{
			BaseMenuScreen::onItemSelect(index);
			ScreenManager* screenMgr = getScreenManager();
			if(screenMgr != nullptr)
			{
				Actor* item = getItem(index);
				if(item == smashButton)
				{
					screenMgr->push(smashMenu);
				}
				else if(item == specialSmashButton)
				{
					//
				}
				else if(item == rulesButton)
				{
					screenMgr->push(rulesMenu);
				}
			}
		}
	}
}
