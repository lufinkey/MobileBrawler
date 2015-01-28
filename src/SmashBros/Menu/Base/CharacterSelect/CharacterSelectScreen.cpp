
#include "CharacterSelectScreen.h"

#include "CharacterSelect_CharacterIcon.h"
#include "CharacterSelect_PlayerChip.h"
#include "CharacterSelect_PlayerPanel.h"
#include "CharacterSelect_ReadyToFightBanner.h"

namespace SmashBros
{
	namespace Menu
	{
		using namespace CharacterSelect;
		
		CharacterSelectScreen::CharacterSelectScreen(const SmashData&smashData, Rules*ruleData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			rules = ruleData;
			characterLoader = smashData.getModuleData()->getCharacterLoader();
			iconGrid = nullptr;
			Vector2f readyToFightPos = smashData.getScreenCoords(0.5f, 0.6f);
			readyToFightBanner = new ReadyToFightBanner(this, readyToFightPos.x, readyToFightPos.y, smashData.getMenuData()->getAssetManager());
			Vector2f screenSize = smashData.getScreenCoords(1.0f,1.0f);
			RectangleF readytofight_constraint(0,readyToFightPos.y, screenSize.x, 1);
			RectangleF readytofight_frame = readyToFightBanner->getFrame();
			readytofight_frame.scaleToFill(readytofight_constraint);
			readyToFightBanner->Actor::scaleToFit(Vector2f(readytofight_frame.width, readytofight_frame.height));
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
			}
			for(unsigned int i=0; i<panels.size(); i++)
			{
				delete panels.get(i);
			}
			for(unsigned int i=0; i<chips.size(); i++)
			{
				delete chips.get(i);
			}
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			delete readyToFightBanner;
		}
		
		bool CharacterSelectScreen::isReadyToFight() const
		{
			unsigned int playerCount = rules->getPlayerCount();
			unsigned int activePlayers = 0;
			for(unsigned int i=0; i<playerCount; i++)
			{
				PlayerChip* chip = chips.get(i);
				if(chip->isDragging())
				{
					return false;
				}
				unsigned int playerNum = chip->getPlayerNum();
				PlayerInfo& playerInfo = rules->getPlayerInfo(playerNum);
				if(playerInfo.getPlayerMode() != PlayerInfo::MODE_OFF)
				{
					activePlayers++;
					if(playerInfo.getCharacterInfo() == nullptr)
					{
						return false;
					}
				}
			}
			if(activePlayers==0)
			{
				return false;
			}
			return true;
		}
		
		void CharacterSelectScreen::proceedToFight()
		{
			//
		}
		
		Rules* CharacterSelectScreen::getRules() const
		{
			return rules;
		}
		
		CharacterLoader* CharacterSelectScreen::getCharacterLoader() const
		{
			return characterLoader;
		}
		
		const ArrayList<CharacterSelect::PlayerChip*>& CharacterSelectScreen::getPlayerChips() const
		{
			return chips;
		}
		
		const ArrayList<CharacterSelect::CharacterIcon*>& CharacterSelectScreen::getCharacterIcons() const
		{
			return icons;
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
			
			ArrayList<CharacterInfo>& characters = smashData.getModuleData()->getCharacterLoader()->getCharacters();
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
			Vector2f icon_size(icon_width, icon_height);
			
			iconGrid = new ActorGrid(Vector2f(charSelectRect.x+(icon_width/2), charSelectRect.y+(icon_height/2)), cols, Vector2f(icon_width, icon_height));
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getCharacterLoader()->getAssetManager();
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
			
			const Dictionary& panelProperties = smashData.getMenuData()->getCharacterSelectPanelProperties();
			
			for(unsigned int i = 0; i < playerCount; i++)
			{
				unsigned int playerNum = i+1;
				PlayerPanel* panel = new PlayerPanel(playerNum, this, offsetX + (panelframe_width*(float)i), offsetY, panelProperties, smashData.getMenuData()->getAssetManager());
				panel->Actor::scaleToFit(Vector2f(panelframe_width, panelframe_height));
				panels.add(panel);
				PlayerChip* chip = new PlayerChip(playerNum, this, panel->x-(panel->getWidth()/2), panel->y, smashData.getMenuData()->getAssetManager());
				chip->Actor::scaleToFit(Vector2f(panelframe_width/3, panelframe_height/3));
				chips.add(chip);
			}
		}
		
		void CharacterSelectScreen::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
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
			if(isReadyToFight())
			{
				readyToFightBanner->setVisible(true);
			}
			else
			{
				readyToFightBanner->setVisible(false);
			}
			readyToFightBanner->update(appData);
		}
		
		void CharacterSelectScreen::onDraw(ApplicationData appData, Graphics graphics) const
		{
			BaseMenuScreen::onDraw(appData, graphics);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				CharacterIcon* icon = icons.get(i);
				icon->draw(appData, graphics);
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
			readyToFightBanner->draw(appData, graphics);
		}
		
		void CharacterSelectScreen::whenPlayerChipGrabbed(unsigned int playerNum)
		{
			PlayerInfo& info = rules->getPlayerInfo(playerNum);
			info.turnPlayerModeOn();
		}
		
		void CharacterSelectScreen::whenPlayerChipReleased(unsigned int playerNum)
		{
			/*PlayerInfo& info = rules->getPlayerInfo(playerNum);
			CharacterInfo* characterInfo = info.getCharacterInfo();
			if(characterInfo == nullptr)
			{
				info.turnPlayerModeOff();
			}*/
		}
		
		void CharacterSelectScreen::whenPlayerCharacterChanges(unsigned int playerNum, CharacterInfo*characterInfo)
		{
			for(unsigned int i=0; i<panels.size(); i++)
			{
				PlayerPanel*panel = panels.get(i);
				if(playerNum == panel->getPlayerNum())
				{
					panel->applyCharacterInfo(characterInfo);
					return;
				}
			}
		}
	}
}
