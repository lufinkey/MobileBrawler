
#include "CharacterSelect_PlayerChip.h"
#include "CharacterSelect_CharacterIcon.h"
#include "CharacterSelectScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			PlayerChip::PlayerChip(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
			{
				playerNum = pNum;
				charSelectScreen = screen;
				addAnimation("default", new Animation(1, assetManager, (String)"characterselect/chip_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, "characterselect/chip_cpu.png"));
				changeAnimation("default", Animation::FORWARD);
				dragging = false;
				dragTouchID = 0;
			}
			
			PlayerChip::~PlayerChip()
			{
				//
			}
			
			void PlayerChip::onMousePress(Window*window, unsigned int touchID)
			{
				if(!dragging)
				{
					bool touch_alreadyBeingUsed = false;
					for(unsigned int i=0; i<charSelectScreen->chips.size(); i++)
					{
						PlayerChip*chip = charSelectScreen->chips.get(i);
						if(chip != this)
						{
							if(chip->dragging && chip->dragTouchID == touchID)
							{
								touch_alreadyBeingUsed = true;
							}
						}
					}
					if(!touch_alreadyBeingUsed)
					{
						dragging = true;
						dragTouchID = touchID;
						unsigned int index = charSelectScreen->chips.indexOf(this);
						charSelectScreen->chips.remove(index);
						charSelectScreen->chips.add(0,this);
					}
				}
			}
			
			void PlayerChip::update(ApplicationData appData)
			{
				//updating dragging
				if(dragging)
				{
					if(Multitouch::isEnabled())
					{
						if(Multitouch::isTouchActive(appData.getWindow(), dragTouchID))
						{
							Vector2f touchpos = appData.getTransform().getInverse().transform(Multitouch::getPosition(appData.getWindow(), dragTouchID));
							x = touchpos.x;
							y = touchpos.y;
						}
						else
						{
							dragging = false;
							dragTouchID = 0;
							//TODO add event for dragging being stopped
						}
					}
					else
					{
						if(Mouse::isButtonPressed(appData.getWindow(), dragTouchID, Mouse::BUTTON_LEFT))
						{
							Vector2f mousepos = appData.getTransform().getInverse().transform(Mouse::getPosition(appData.getWindow(), dragTouchID));
							x = mousepos.x;
							y = mousepos.y;
						}
						else
						{
							dragging = false;
							dragTouchID = 0;
							//TODO add event for dragging being stopped
						}
					}
				}
				SpriteActor::update(appData);
				
				//check if overlapping with any character icons;
				CharacterInfo* overlap_charInfo = nullptr;
				float overlap_area = 0;
				ArrayList<CharacterIcon*>& icons = charSelectScreen->icons;
				RectangleF frame = getFrame();
				for(unsigned int i=0; i<icons.size(); i++)
				{
					CharacterIcon* icon = icons.get(i);
					RectangleF iconFrame = icon->getFrame();
					if(frame.intersects(iconFrame))
					{
						RectangleF overlap = frame.getIntersect(iconFrame);
						float area = overlap.getArea();
						if(area > overlap_area)
						{
							overlap_charInfo = icon->getCharacterInfo();
							overlap_area = area;
						}
					}
				}
				CharacterInfo* oldInfo = charSelectScreen->rules->getPlayerInfo(playerNum).getCharacterInfo();
				charSelectScreen->rules->getPlayerInfo(playerNum).setCharacterInfo(overlap_charInfo);
				if(oldInfo != overlap_charInfo)
				{
					charSelectScreen->whenPlayerCharacterChanges(playerNum, overlap_charInfo);
				}
			}
		}
	}
}
