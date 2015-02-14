
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
			RectangleF frame = getFrame();
			autoIconLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
			autoPanelLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
			
			rules = ruleData;
			characterLoader = smashData.getModuleData()->getCharacterLoader();
			readyToFightBanner = new ReadyToFightBanner(this, 0, 0, smashData.getMenuData()->getAssetManager());
			getElement()->getAutoLayout().add(RectF(0, 0.5f, 1.0f, 0.7f), readyToFightBanner);
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{
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
		
		void CharacterSelectScreen::onFrameChange()
		{
			BaseMenuScreen::onFrameChange();
			RectangleF frame = getFrame();
			autoIconLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
			autoPanelLayout.setFrame(RectangleF(0,0,frame.width,frame.height));
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
			autoIconLayout.clear();
			
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
			
			float frameoffset_y = getElement()->getAutoLayout().get(getHeaderbarElement()).bottom*1.1f;
			
			RectF bounds(0.1f, frameoffset_y, 0.9f, 0.6f);
			float bounds_w = bounds.right - bounds.left;
			float bounds_h = bounds.bottom - bounds.top;
			
			float icon_width = bounds_w/((float)cols);
			float icon_height = bounds_h/((float)rows);
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getCharacterLoader()->getAssetManager();
			for(unsigned int i=0; i<characters.size(); i++)
			{
				CharacterInfo& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(info, 0, 0, loaderAssetManager);
				unsigned int col = i%cols;
				unsigned int row = i/cols;
				float icon_left = bounds.left+(((float)col)*icon_width);
				float icon_top = bounds.top+(((float)row)*icon_height);
				autoIconLayout.add(RectF(icon_left, icon_top, icon_left+icon_width, icon_top+icon_height), icon);
				icons.add(icon);
			}
		}
		
		void CharacterSelectScreen::reloadPlayerPanels(const SmashData&smashData)
		{
			autoPanelLayout.clear();
			
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
			
			RectF panelBounds(0.0f, 0.6f, 1.0f, 1.0f);
			
			float panelBounds_w = panelBounds.right - panelBounds.left;
			float panelBounds_h = panelBounds.bottom - panelBounds.top;

			float panel_width = panelBounds_w/(float)playerCount;
			float panel_height = panelBounds_h;
			Vector2f screenSize = smashData.getScreenCoords(1.0f,1.0f);
			Vector2f chipSize((panel_width*screenSize.x)/3, (panel_height*screenSize.y)/3);
			
			const Dictionary& panelProperties = smashData.getMenuData()->getCharacterSelectPanelProperties();
			
			for(unsigned int i = 0; i < playerCount; i++)
			{
				unsigned int playerNum = i+1;
				
				PlayerPanel* panel = new PlayerPanel(playerNum, this, 0, 0, panelProperties, smashData.getMenuData()->getAssetManager());
				float panel_left = panelBounds.left + (panel_width*((float)i));
				float panel_top = panelBounds.top;
				autoPanelLayout.add(RectF(panel_left, panel_top, panel_left+panel_width, panelBounds.bottom), panel);
				panels.add(panel);

				float chipX = (panel_left*screenSize.x)+(chipSize.x/2);
				float chipY = (panel_top+(panel_height/2))*screenSize.y;
				
				PlayerChip* chip = new PlayerChip(playerNum, this, chipX, chipY, smashData.getMenuData()->getAssetManager());
				chip->Actor::scaleToFit(chipSize);
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
