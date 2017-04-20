
#include "CharacterSelectScreen.hpp"

#include "CharacterSelect_CharacterIcon.hpp"
#include "CharacterSelect_PlayerChip.hpp"
#include "CharacterSelect_PlayerPanel.hpp"
#include "CharacterSelect_ReadyToFightBanner.hpp"

namespace SmashBros
{
	namespace Menu
	{
		using namespace CharacterSelect;
		
		CharacterSelectScreen::CharacterSelectScreen(const SmashData&smashData, Rules*ruleData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			Vector2d size = getSize();
			
			rules = ruleData;
			characterLoader = smashData.getModuleData()->getCharacterLoader();
			readyToFightBanner = new ReadyToFightBanner(this, 0, 0, smashData.getMenuData()->getAssetManager());
			readyToFightBanner->autoLayoutMgr.setRule(LAYOUTRULE_LEFT,   0,   LAYOUTVALUE_RATIO);
			readyToFightBanner->autoLayoutMgr.setRule(LAYOUTRULE_TOP,    0.5, LAYOUTVALUE_RATIO);
			readyToFightBanner->autoLayoutMgr.setRule(LAYOUTRULE_RIGHT,  0, LAYOUTVALUE_RATIO);
			readyToFightBanner->autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.3, LAYOUTVALUE_RATIO);
			readyToFightBanner->scaleToFit(readyToFightBanner->autoLayoutMgr.calculateFrame(readyToFightBanner->getFrame(), RectangleD(0,0,size.x,size.y)));
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
		
		void CharacterSelectScreen::onSizeChange(const Vector2d& oldSize, const Vector2d& newSize)
		{
			BaseMenuScreen::onSizeChange(oldSize, newSize);
			Vector2d size = getSize();
			RectangleD frame = RectangleD(0,0, size.x, size.y);
			readyToFightBanner->scaleToFit(readyToFightBanner->autoLayoutMgr.calculateFrame(readyToFightBanner->getFrame(), frame));
			for(size_t icons_size=icons.size(), i=0; i<icons_size; i++)
			{
				CharacterSelect::CharacterIcon* icon = icons.get(i);
				icon->scaleToFit(icon->autoLayoutMgr.calculateFrame(icon->getFrame(), frame));
			}
			for(size_t panels_size=panels.size(), i=0; i<panels_size; i++)
			{
				CharacterSelect::PlayerPanel* panel = panels.get(i);
				panel->scaleToFit(panel->autoLayoutMgr.calculateFrame(panel->getFrame(), frame));
			}
			if(oldSize.x==0 || oldSize.y==0)
			{
				RectD panelBounds(0.0, 0.6, 1.0, 1.0);
				double panelBounds_w = panelBounds.right - panelBounds.left;
				double panelBounds_h = panelBounds.bottom - panelBounds.top;
				unsigned int playerCount = getRules()->getPlayerCount();
				if(playerCount==0)
				{
					return;
				}
				double panel_width = panelBounds_w/(double)playerCount;
				double panel_height = panelBounds_h;
				Vector2d chipSize((panel_width*newSize.x)/3, (panel_height*newSize.y)/3);
				for(size_t chips_size=chips.size(), i=0; i<chips_size; i++)
				{
					CharacterSelect::PlayerChip* chip = chips.get(i);
					double panel_left = panelBounds.left + (panel_width*((double)i));
					double panel_top = panelBounds.top;
					chip->x = (panel_left*newSize.x)+(chipSize.x/2);
					chip->y = (panel_top+(panel_height/2))*newSize.y;
					chip->Actor::scaleToFit(chipSize);
				}
			}
			else
			{
				double screen_rat_x = newSize.x/oldSize.x;
				double screen_rat_y = newSize.y/oldSize.y;
				for(size_t chips_size=chips.size(), i=0; i<chips_size; i++)
				{
					CharacterSelect::PlayerChip* chip = chips.get(i);
					chip->x *= screen_rat_x;
					chip->y *= screen_rat_y;
				}
			}
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
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			ArrayList<CharacterInfo>& characters = smashData.getModuleData()->getCharacterLoader()->getCharacters();
			size_t total = characters.size();
			double approx_cols = Math::sqrt((3.0*((double)total))/2.0);
			double approx_rows = approx_cols*(2.0/3.0);
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
			
			double frameoffset_y = 0.134*1.1;
			
			LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==LAYOUTVALUE_RATIO)
			{
				frameoffset_y = headerBarBottomRule->value*1.1;
			}
			
			RectD bounds(0.1, frameoffset_y, 0.9, 0.6);
			double bounds_w = bounds.right - bounds.left;
			double bounds_h = bounds.bottom - bounds.top;
			
			double icon_width = bounds_w/((double)cols);
			double icon_height = bounds_h/((double)rows);
			
			Vector2d size = getSize();
			
			AssetManager* loaderAssetManager = smashData.getModuleData()->getCharacterLoader()->getAssetManager();
			for(unsigned int i=0; i<characters.size(); i++)
			{
				CharacterInfo& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(info, 0, 0, loaderAssetManager);
				unsigned int col = i%cols;
				unsigned int row = i/cols;
				double icon_left = bounds.left+(((double)col)*icon_width);
				double icon_top = bounds.top+(((double)row)*icon_height);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_LEFT, icon_left, LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_TOP, icon_top, LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 1.0-(icon_left+icon_width), LAYOUTVALUE_RATIO);
				icon->autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1.0-(icon_top+icon_height), LAYOUTVALUE_RATIO);
				icons.add(icon);
				icon->scaleToFit(icon->autoLayoutMgr.calculateFrame(icon->getFrame(), RectangleD(0,0,size.x,size.y)));
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
			
			RectD panelBounds(0.0, 0.6, 1.0, 1.0);
			
			double panelBounds_w = panelBounds.right - panelBounds.left;
			double panelBounds_h = panelBounds.bottom - panelBounds.top;

			double panel_width = panelBounds_w/(double)playerCount;
			double panel_height = panelBounds_h;
			Vector2d screenSize = smashData.getScreenCoords(1.0,1.0);
			Vector2d chipSize((panel_width*screenSize.x)/3, (panel_height*screenSize.y)/3);
			
			Vector2d size = getSize();
			
			const Dictionary& panelProperties = smashData.getMenuData()->getCharacterSelectPanelProperties();
			
			for(unsigned int i = 0; i < playerCount; i++)
			{
				unsigned int playerNum = i+1;
				
				PlayerPanel* panel = new PlayerPanel(playerNum, this, 0, 0, panelProperties, smashData.getMenuData()->getAssetManager());
				double panel_left = panelBounds.left + (panel_width*((double)i));
				double panel_top = panelBounds.top;
				panel->autoLayoutMgr.setRule(LAYOUTRULE_LEFT, panel_left, LAYOUTVALUE_RATIO);
				panel->autoLayoutMgr.setRule(LAYOUTRULE_TOP, panel_top, LAYOUTVALUE_RATIO);
				panel->autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 1.0-(panel_left+panel_width), LAYOUTVALUE_RATIO);
				panel->autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 1.0-(panelBounds.bottom), LAYOUTVALUE_RATIO);
				panels.add(panel);
				panel->scaleToFit(panel->autoLayoutMgr.calculateFrame(panel->getFrame(), RectangleD(0,0,size.x,size.y)));
				
				double chipX = (panel_left*screenSize.x)+(chipSize.x/2);
				double chipY = (panel_top+(panel_height/2))*screenSize.y;
				
				PlayerChip* chip = new PlayerChip(playerNum, this, chipX, chipY, smashData.getMenuData()->getAssetManager());
				chip->Actor::scaleToFit(chipSize);
				chips.add(chip);
			}
		}
		
		void CharacterSelectScreen::onUpdate(const ApplicationData& appData)
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
		
		void CharacterSelectScreen::onDraw(const ApplicationData& appData, Graphics graphics) const
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
