
#include "CharacterSelect_PlayerChip.hpp"
#include "CharacterSelect_CharacterIcon.hpp"
#include "CharacterSelectScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			PlayerChip::PlayerChip(unsigned int pNum, CharacterSelectScreen*screen, double x, double y, AssetManager*assetManager) : SpriteActor(x,y)
			{
				playerNum = pNum;
				charSelectScreen = screen;
				addAnimation("default", new Animation(1, assetManager, (String)"characterselect/chip_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, "characterselect/chip_cpu.png"));
				changeAnimation("default", Animation::FORWARD);
				dragging = false;
				dragTouchID = 0;
				dragOffset.x = 0;
				dragOffset.y = 0;
			}
			
			PlayerChip::~PlayerChip()
			{
				//
			}
			
			void PlayerChip::onMousePress(const ActorMouseEvent& evt)
			{
				if(!dragging)
				{
					bool touch_alreadyBeingUsed = false;
					const ArrayList<PlayerChip*>& chips = charSelectScreen->getPlayerChips();
					for(unsigned int i=0; i<chips.size(); i++)
					{
						PlayerChip*chip = chips.get(i);
						if(chip != this)
						{
							if(chip->dragging && chip->dragTouchID == evt.getMouseIndex())
							{
								touch_alreadyBeingUsed = true;
							}
						}
					}
					if(!touch_alreadyBeingUsed)
					{
						grabChip(evt.getApplicationData(), evt.getMouseIndex());
					}
				}
			}
			
			void PlayerChip::update(ApplicationData appData)
			{
				//updating dragging
				bool stopDragging = false;
				if(dragging)
				{
					if(Multitouch::isAvailable())
					{
						if(Multitouch::isTouchActive(appData.getWindow(), dragTouchID))
						{
							Vector2d touchpos = appData.getTransform().getInverse().transform(Multitouch::getPosition(appData.getWindow(), dragTouchID));
							x = touchpos.x + dragOffset.x;
							y = touchpos.y + dragOffset.y;
						}
						else
						{
							stopDragging = true;
						}
					}
					else
					{
						if(Mouse::isButtonPressed(appData.getWindow(), dragTouchID, Mouse::BUTTON_LEFT))
						{
							Vector2d mousepos = appData.getTransform().getInverse().transform(Mouse::getPosition(appData.getWindow(), dragTouchID));
							x = mousepos.x + dragOffset.x;
							y = mousepos.y + dragOffset.y;
						}
						else
						{
							stopDragging = true;
						}
					}
				}
				SpriteActor::update(appData);
				
				//check if overlapping with any character icons;
				CharacterInfo* overlap_charInfo = nullptr;
				double overlap_area = 0;
				const ArrayList<CharacterIcon*>& icons = charSelectScreen->getCharacterIcons();
				RectangleD frame = getFrame();
				for(unsigned int i=0; i<icons.size(); i++)
				{
					CharacterIcon* icon = icons.get(i);
					RectangleD iconFrame = icon->getFrame();
					if(frame.intersects(iconFrame))
					{
						RectangleD overlap = frame.getIntersect(iconFrame);
						double area = overlap.getArea();
						if(area > overlap_area)
						{
							overlap_charInfo = icon->getCharacterInfo();
							overlap_area = area;
						}
					}
				}
				CharacterInfo* oldInfo = charSelectScreen->getRules()->getPlayerInfo(playerNum).getCharacterInfo();
				charSelectScreen->getRules()->getPlayerInfo(playerNum).setCharacterInfo(overlap_charInfo);
				if(oldInfo != overlap_charInfo)
				{
					//event: whenPlayerCharacterChanges
					charSelectScreen->whenPlayerCharacterChanges(playerNum, overlap_charInfo);
				}
				
				if(stopDragging)
				{
					releaseChip();
				}
			}
			
			void PlayerChip::grabChip(const ApplicationData&appData, unsigned int touchID)
			{
				dragging = true;
				dragTouchID = touchID;
				TransformD mouseTransform = appData.getTransform().getInverse();
				if(Multitouch::isAvailable())
				{
					dragOffset = Vector2d(x,y) - mouseTransform.transform(Multitouch::getPosition(appData.getWindow(), touchID));
				}
				else
				{
					dragOffset = Vector2d(x,y) - mouseTransform.transform(Mouse::getPosition(appData.getWindow(), touchID));
				}
				size_t index = charSelectScreen->chips.indexOf(this);
				charSelectScreen->chips.remove(index);
				charSelectScreen->chips.add(0,this);
				//event: whenPlayerChipGrabbed
				charSelectScreen->whenPlayerChipGrabbed(playerNum);
			}
			
			void PlayerChip::releaseChip()
			{
				if(dragging)
				{
					dragging = false;
					dragTouchID = 0;
					dragOffset.x = 0;
					dragOffset.y = 0;
					//event: whenPlayerChipReleased
					charSelectScreen->whenPlayerChipReleased(playerNum);
				}
			}
			
			bool PlayerChip::isDragging() const
			{
				return dragging;
			}
			
			unsigned int PlayerChip::getPlayerNum() const
			{
				return playerNum;
			}
		}
	}
}
