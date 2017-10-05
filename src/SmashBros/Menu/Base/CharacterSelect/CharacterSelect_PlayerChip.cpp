
#include "CharacterSelect_PlayerChip.hpp"
#include "CharacterSelect_CharacterIcon.hpp"
#include "CharacterSelectScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			PlayerChip::PlayerChip(CharacterSelectScreen* charSelectScreen, MenuData* menuData, size_t playerIndex)
				: charSelectScreen(charSelectScreen),
				playerIndex(playerIndex),
				dragging(false),
				dragTouchID(0)
			{
				auto assetManager = menuData->getAssetManager();
				auto playerNum = playerIndex+1;

				playerChipTexture = assetManager->loadTexture((fgl::String)"characterselect/chip_p" + playerNum + ".png");
				cpuChipTexture = assetManager->loadTexture("characterselect/chip_cpu.png");

				chipImageElement = new fgl::ImageElement(playerChipTexture);
				chipImageElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				chipImageElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				chipImageElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				chipImageElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
				addChildElement(chipImageElement);
			}
			
			PlayerChip::~PlayerChip()
			{
				delete chipImageElement;
			}
			
			void PlayerChip::onTouchDown(const TouchEvent& event)
			{
				if(!dragging)
				{
					//make sure this touch ID isn't already grabbing another chip
					bool touch_alreadyBeingUsed = false;
					auto& chips = charSelectScreen->getPlayerChips();
					for(auto& chip : chips)
					{
						if(chip != this)
						{
							if(chip->dragging && chip->dragTouchID == event.getTouchID())
							{
								touch_alreadyBeingUsed = true;
								break;
							}
						}
					}
					if(!touch_alreadyBeingUsed)
					{
						grabChip(event);
					}
				}
			}

			bool PlayerChip::onTouchMove(const TouchEvent& event)
			{
				if(dragging && dragTouchID==event.getTouchID())
				{
					auto realPosition = event.getPosition();
					setCenter(realPosition + dragOffset);
					return true;
				}
				return false;
			}

			void PlayerChip::onTouchUpInside(const TouchEvent& event)
			{
				if(dragging && dragTouchID==event.getTouchID())
				{
					releaseChip();
				}
			}

			void PlayerChip::onTouchUpOutside(const TouchEvent& event)
			{
				if(dragging && dragTouchID==event.getTouchID())
				{
					releaseChip();
				}
			}

			void PlayerChip::onTouchCancel(const TouchEvent& event)
			{
				if(dragging && dragTouchID==event.getTouchID())
				{
					releaseChip();
				}
			}
			
			void PlayerChip::update(fgl::ApplicationData appData)
			{
				TouchElement::update(appData);

				//check if overlapping with any character icons;
				fgl::String characterID;
				double overlap_area = 0;
				auto& icons = charSelectScreen->getCharacterIcons();
				auto frame = getFrame();
				for(auto& icon : icons)
				{
					auto iconFrame = icon->getChipFrame();
					if(frame.intersects(iconFrame))
					{
						fgl::RectangleD overlap = frame.getIntersect(iconFrame);
						double area = overlap.getArea();
						if(area > overlap_area)
						{
							characterID = icon->getCharacterInfo().getIdentifier();
							overlap_area = area;
						}
					}
				}
				auto oldCharacterID = charSelectScreen->getRules()->getPlayerInfo(playerIndex).getCharacterIdentifier();
				charSelectScreen->getRules()->getPlayerInfo(playerIndex).setCharacterIdentifier(characterID);
				if(oldCharacterID != characterID)
				{
					//event: handlePlayerCharacterChanged
					charSelectScreen->handlePlayerCharacterChanged(playerIndex, characterID);
				}
			}
			
			void PlayerChip::grabChip(const TouchEvent& touchEvent)
			{
				dragging = true;
				dragTouchID = touchEvent.getTouchID();
				auto center = getCenter();
				auto realPosition = touchEvent.getPosition();
				dragOffset = center - realPosition;
				size_t index = charSelectScreen->chips.indexOf(this);
				if(index!=-1)
				{
					charSelectScreen->chips.remove(index);
					charSelectScreen->chips.add(0, this);
					//event: handlePlayerChipGrabbed
					charSelectScreen->handlePlayerChipGrabbed(playerIndex);
				}
			}
			
			void PlayerChip::releaseChip()
			{
				if(dragging)
				{
					dragging = false;
					dragTouchID = 0;
					dragOffset.x = 0;
					dragOffset.y = 0;
					//event: handlePlayerChipReleased
					charSelectScreen->handlePlayerChipReleased(playerIndex);
				}
			}
			
			bool PlayerChip::isDragging() const
			{
				return dragging;
			}
			
			size_t PlayerChip::getPlayerIndex() const
			{
				return playerIndex;
			}
		}
	}
}
