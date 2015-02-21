
#include "CharacterSelect_ReadyToFightBanner.h"
#include "CharacterSelectScreen.h"
#include "CharacterSelect_PlayerChip.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			ReadyToFightBanner::ReadyToFightBanner(CharacterSelectScreen*screen, double x, double y, AssetManager*assetManager) : SpriteActor(x, y)
			{
				charSelectScreen = screen;
				selected = false;
				
				addAnimation("default", new Animation(1, assetManager, "characterselect/readytofight_banner.png"));
				changeAnimation("default", Animation::FORWARD);
				setVisible(false);
			}
			
			void ReadyToFightBanner::update(ApplicationData appData)
			{
				SpriteActor::update(appData);
				
				const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
				for(unsigned int i=0; i<chips.size(); i++)
				{
					PlayerChip* chip = chips.get(i);
					if(chip->isDragging())
					{
						setVisible(false);
					}
				}
				
				if(!isVisible())
				{
					selected = false;
				}
				
				if(isMouseOver())
				{
					if(selected)
					{
						setColor(Color::BLUE);
					}
					else
					{
						setColor(Color::LIGHTBLUE);
					}
				}
				else
				{
					setColor(Color::WHITE);
				}
			}
			
			void ReadyToFightBanner::onMousePress(ApplicationData appData, unsigned int touchID)
			{
				if(isVisible())
				{
					selected = true;
				}
			}
			
			void ReadyToFightBanner::onMouseRelease(ApplicationData appData, unsigned int touchID)
			{
				if(selected)
				{
					selected = false;
					charSelectScreen->proceedToFight();
				}
			}
		}
	}
}
