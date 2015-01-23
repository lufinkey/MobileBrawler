
#include "CharacterSelectScreen.h"

namespace SmashBros
{
	namespace Menu
	{
//CharacterIcon
		CharacterSelectScreen::CharacterIcon::CharacterIcon(CharacterInfo&characterInfo, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
		{
			info = &characterInfo;
			String icon_path = characterInfo.getPath() + "/icon.png";
			addAnimation("default", new Animation(assetManager, 1, icon_path));
			changeAnimation("default", Animation::FORWARD);
		}
		
		CharacterSelectScreen::CharacterIcon::~CharacterIcon()
		{
			//
		}
		
		bool CharacterSelectScreen::CharacterIcon::equals(const CharacterIcon&icon) const
		{
			if(info->getName().equals(icon.info->getName()) && info->getCreator().equals(icon.info->getCreator()))
			{
				return true;
			}
			return false;
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getName() const
		{
			return info->getName();
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getCreator() const
		{
			return info->getCreator();
		}
		
		CharacterInfo* CharacterSelectScreen::CharacterIcon::getCharacterInfo() const
		{
			return info;
		}
		
//PlayerPanel
		CharacterSelectScreen::PlayerPanel::PlayerPanel(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, AssetManager*assetManager) : SpriteActor(x, y)
		{
			playerNum = pNum;
			characterName = new TextActor(x, y+(getHeight()/2), "", assetManager->getFont("fonts/LemonMilk.ttf"), Color::BLACK, 36, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			characterName->Actor::scaleToFit(Vector2f((getWidth()*(3.0f/8.0f)), (getHeight()/10)));
			charSelectScreen = screen;
			addAnimation("default", new Animation(assetManager, 1, (String)"characterselect/panel_p" + playerNum + ".png"));
			addAnimation("cpu", new Animation(assetManager, 1, "characterselect/panel_cpu.png"));
			addAnimation("na", new Animation(assetManager, 1, "characterselect/panel_na.png"));
			addAnimation("blank", new Animation(assetManager, 1, "characterselect/panel_blank.png"));
			changeAnimation("na", Animation::FORWARD);
		}
		
		CharacterSelectScreen::PlayerPanel::~PlayerPanel()
		{
			//
		}
		
		void CharacterSelectScreen::PlayerPanel::update(ApplicationData appData)
		{
			SpriteActor::update(appData);
			CharacterInfo*charInfo = charSelectScreen->rules->getPlayerInfo(playerNum).getCharacterInfo();
			if(charInfo == nullptr)
			{
				if(!characterName->getText().equals(""))
				{
					characterName->setText("");
				}
			}
			else
			{
				String charName = charInfo->getName();
				if(!characterName->getText().equals(charName))
				{
					characterName->setText(charName);
				}
			}
			characterName->Actor::scaleToFit(Vector2f((getWidth()*(3.0f/8.0f)), (getHeight()/8)));
			characterName->x = x + (getWidth()/10);
			characterName->y = y + (getHeight()/2) - (characterName->getHeight()*(3.0f/4.0f));
			characterName->update(appData);
		}
		
		void CharacterSelectScreen::PlayerPanel::draw(ApplicationData appData, Graphics graphics) const
		{
			SpriteActor::draw(appData, graphics);
			characterName->Actor::scaleToFit(Vector2f((getWidth()*(3.0f/8.0f)), (getHeight()/8)));
			characterName->x = x + (getWidth()/10);
			characterName->y = y + (getHeight()/2) - (characterName->getHeight()*(3.0f/4.0f));
			characterName->draw(appData, graphics);
		}
		
//PlayerChip
		CharacterSelectScreen::PlayerChip::PlayerChip(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
		{
			playerNum = pNum;
			charSelectScreen = screen;
			addAnimation("default", new Animation(assetManager, 1, (String)"characterselect/chip_p" + playerNum + ".png"));
			addAnimation("cpu", new Animation(assetManager, 1, "characterselect/chip_cpu.png"));
			changeAnimation("default", Animation::FORWARD);
			dragging = false;
			dragTouchID = 0;
		}
		
		CharacterSelectScreen::PlayerChip::~PlayerChip()
		{
			//
		}
		
		void CharacterSelectScreen::PlayerChip::onMousePress(Window*window, unsigned int touchID)
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
		
		void CharacterSelectScreen::PlayerChip::update(ApplicationData appData)
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
			charSelectScreen->rules->getPlayerInfo(playerNum).setCharacterInfo(overlap_charInfo);
		}
		
//CharacterSelectScreen
		CharacterSelectScreen::CharacterSelectScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			rules = smashData.getRules();
			iconGrid = nullptr;
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
			}
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			for(unsigned int i=0; i<panels.size(); i++)
			{
				delete panels.get(i);
			}
		}
		
		void CharacterSelectScreen::reloadIcons(const SmashData&smashData)
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
			
			ArrayList<CharacterInfo>& characters = smashData.getCharacterLoader()->getCharacters();
			unsigned int total = characters.size();
			float approx_cols = Math::sqrt((3.0f*((float)total))/2.0f);
			float approx_rows = approx_cols*(2.0f/3.0f);
			unsigned int cols = (unsigned int)Math::round(approx_cols);
			unsigned int rows = (unsigned int)Math::round(approx_rows);
			if((cols*rows) < total)
			{
				cols = (unsigned int)Math::ceil(approx_cols);
				if((cols*rows) < total)
				{
					rows = (unsigned int)Math::ceil(approx_rows);
				}
			}
			
			ImageElement* headerbar = getHeaderbarElement();
			RectangleF headerbarFrame = headerbar->getFrame();
			Vector2f screenSize = smashData.getScreenCoords(Vector2f(1.0f,1.0f));
			float frameoffset_y = headerbarFrame.height / screenSize.y;
			
			Vector2f topLeft = smashData.getScreenCoords(0.1f, frameoffset_y);
			Vector2f bottomRight = smashData.getScreenCoords(0.9f, 0.6f);
			RectangleF charSelectRect(topLeft.x, topLeft.y, bottomRight.x-topLeft.x, bottomRight.y-topLeft.y);
			iconGridFrame = charSelectRect;
			
			float icon_width = charSelectRect.width/((float)cols);
			float icon_height = charSelectRect.height/((float)rows);
			Vector2f icon_size(icon_width-1, icon_height);
			
			iconGrid = new ActorGrid(Vector2f(charSelectRect.x+(icon_width/2), charSelectRect.y+(icon_height/2)), cols, Vector2f(icon_width, icon_height));
			
			AssetManager* loaderAssetManager = smashData.getCharacterLoader()->getAssetManager();
			for(unsigned int i=0; i<characters.size(); i++)
			{
				CharacterInfo& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(info, 0, 0, loaderAssetManager);
				icon->Actor::scaleToFit(icon_size);
				icons.add(icon);
				iconGrid->add(icon);
			}
		}
		
		void CharacterSelectScreen::reloadPlayerPanels(const SmashData&smashData)
		{
			for(unsigned int i=0; i<panels.size(); i++)
			{
				delete panels.get(i);
			}
			panels.clear();
			for(unsigned int i = 0; i < chips.size(); i++)
			{
				delete chips.get(i);
			}
			chips.clear();
			
			unsigned int playerCount = rules->getPlayerCount();
			if(playerCount==0)
			{
				return;
			}
			
			Vector2f topLeft = smashData.getScreenCoords(0.0f, 0.6f);
			Vector2f bottomRight = smashData.getScreenCoords(1.0f, 1.0f);
			RectangleF frame(topLeft.x, topLeft.y, bottomRight.x-topLeft.x, bottomRight.y-topLeft.y);
			
			float panelframe_width = frame.width/(float)playerCount;
			float panelframe_height = frame.height*(5.0f/6.0f);
			float offsetX = frame.x + (panelframe_width/2);
			float offsetY = frame.y + (frame.height/2);
			
			for(unsigned int i = 0; i < playerCount; i++)
			{
				unsigned int playerNum = i+1;
				PlayerPanel* panel = new PlayerPanel(playerNum, this, offsetX + (panelframe_width*(float)i), offsetY, smashData.getMenuData().getAssetManager());
				panel->Actor::scaleToFit(Vector2f(panelframe_width, panelframe_height));
				panels.add(panel);
				PlayerChip* chip = new PlayerChip(playerNum, this, panel->x-(panel->getWidth()/2), panel->y, smashData.getMenuData().getAssetManager());
				chip->Actor::scaleToFit(Vector2f(panelframe_width/3, panelframe_height/3));
				chips.add(chip);
			}
		}
		
		void CharacterSelectScreen::updateItems(ApplicationData appData)
		{
			BaseMenuScreen::updateItems(appData);
			ArrayList<CharacterIcon*> icons_list = icons;
			for(unsigned int i=0; i<icons_list.size(); i++)
			{
				icons_list.get(i)->update(appData);
			}
			icons_list.clear();
			ArrayList<PlayerChip*> chips_list = chips;
			for(unsigned int i=0; i<chips_list.size(); i++)
			{
				chips_list.get(i)->update(appData);
			}
			chips_list.clear();
			ArrayList<PlayerPanel*> panels_list = panels;
			for(unsigned int i=0; i<panels_list.size(); i++)
			{
				panels_list.get(i)->update(appData);
			}
			panels_list.clear();
		}
		
		void CharacterSelectScreen::drawItems(ApplicationData appData, Graphics graphics) const
		{
			TextureImage* icon_frame = appData.getAssetManager()->getTexture("characterselect/icon_frame.png");
			BaseMenuScreen::drawItems(appData, graphics);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				CharacterIcon* icon = icons.get(i);
				icon->draw(appData, graphics);
				RectangleF frame = icon->getFrame();
				graphics.drawImage(icon_frame, frame);
			}
			for(unsigned int i=0; i<panels.size(); i++)
			{
				PlayerPanel* panel = panels.get(i);
				panel->draw(appData, graphics);
			}
			ArrayList<PlayerChip*> chips_list;
			for(unsigned int i=0; i<chips.size(); i++) //reverse the chips list
			{
				chips_list.add(0, chips.get(i));
			}
			for(unsigned int i=0; i<chips_list.size(); i++)
			{
				chips_list.get(i)->draw(appData, graphics);
			}
		}
	}
}
