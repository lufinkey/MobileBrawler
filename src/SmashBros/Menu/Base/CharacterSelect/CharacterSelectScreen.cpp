
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
		
		CharacterSelectScreen::CharacterSelectScreen(MenuData* menuData, Rules* rules)
			: SmashBros::Menu::BaseMenuScreen(menuData),
			rules(rules)
		{
			auto assetManager = menuData->getAssetManager();
			auto element = getElement();

			iconsElement = new fgl::ScreenElement();
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			iconsElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

			panelsElement = new fgl::ScreenElement();
			panelsElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			panelsElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			panelsElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			panelsElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

			chipsElement = new fgl::ScreenElement();
			chipsElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			chipsElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			chipsElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			chipsElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
			
			readyToFightBanner = new ReadyToFightBanner(this, assetManager);
			readyToFightBanner->setVisible(false);
			readyToFightBanner->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.56, fgl::LAYOUTVALUE_RATIO);

			element->addChildElement(iconsElement);
			element->addChildElement(panelsElement);
			element->addChildElement(chipsElement);
			element->addChildElement(readyToFightBanner);
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{
			for(auto& panel : panels)
			{
				delete panel;
			}
			for(auto& chip : chips)
			{
				delete chip;
			}
			for(auto& icon : icons)
			{
				delete icon;
			}
			delete iconsElement;
			delete panelsElement;
			delete chipsElement;
			delete readyToFightBanner;
		}

		void CharacterSelectScreen::onSizeChange(const fgl::Vector2d& oldSize, const fgl::Vector2d& newSize)
		{
			BaseMenuScreen::onSizeChange(oldSize, newSize);
			for(size_t playerIndex=0; playerIndex < rules->getPlayerCount(); playerIndex++)
			{
				auto& identifier = rules->getPlayerInfo(playerIndex).getCharacterIdentifier();
				if(identifier.length()==0)
				{
					resetPlayerChip(playerIndex);
				}
				else
				{
					auto icon = getCharacterIcon(identifier);
					auto chip = getPlayerChip(playerIndex);
					chip->setCenter(icon->getCenter());
				}
			}
		}
		
		bool CharacterSelectScreen::isReadyToFight() const
		{
			size_t playerCount = rules->getPlayerCount();
			size_t activePlayers = 0;
			for(size_t i=0; i<playerCount; i++)
			{
				auto chip = chips[i];
				if(chip->isDragging())
				{
					return false;
				}
				size_t playerIndex = chip->getPlayerIndex();
				PlayerInfo& playerInfo = rules->getPlayerInfo(playerIndex);
				if(playerInfo.getPlayerMode() != PlayerInfo::MODE_OFF)
				{
					activePlayers++;
					auto characterIdentifier = playerInfo.getCharacterIdentifier();
					if(characterIdentifier.length()==0)
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
			//TODO proceed to fight
		}
		
		Rules* CharacterSelectScreen::getRules() const
		{
			return rules;
		}
		
		const fgl::ArrayList<CharacterSelect::PlayerChip*>& CharacterSelectScreen::getPlayerChips() const
		{
			return chips;
		}

		CharacterSelect::PlayerChip* CharacterSelectScreen::getPlayerChip(size_t playerIndex) const
		{
			if(playerIndex < chips.size())
			{
				return chips[playerIndex];
			}
			return nullptr;
		}
		
		const fgl::ArrayList<CharacterSelect::CharacterIcon*>& CharacterSelectScreen::getCharacterIcons() const
		{
			return icons;
		}

		CharacterSelect::CharacterIcon* CharacterSelectScreen::getCharacterIcon(const fgl::String& identifier) const
		{
			for(auto& icon : icons)
			{
				if(icon->getCharacterInfo().getIdentifier()==identifier)
				{
					return icon;
				}
			}
			return nullptr;
		}
		
		void CharacterSelectScreen::reloadCharacters()
		{
			for(auto& icon : icons)
			{
				icon->removeFromParentElement();
				delete icon;
			}
			icons.clear();

			auto menuData = getMenuData();
			auto characterLoader = menuData->getModuleManager()->getCharacterLoader();
			
			auto& characters = characterLoader->getCharacters();
			size_t characters_size = characters.size();
			double approx_cols = fgl::Math::sqrt((3.0*((double)characters_size))/2.0);
			double approx_rows = approx_cols*(2.0/3.0);
			size_t cols = (size_t)fgl::Math::round(approx_cols);
			size_t rows = (size_t)fgl::Math::round(approx_rows);
			if((cols*rows) < characters_size)
			{
				cols = (unsigned int)fgl::Math::ceil(approx_cols);
				if((cols*rows) < characters_size)
				{
					rows = (unsigned int)fgl::Math::ceil(approx_rows);
				}
			}
			
			double frameoffset_y = 0.134*1.1;
			
			fgl::LayoutRule* headerBarBottomRule = getHeaderbarElement()->getAutoLayoutManager().getRule(fgl::LAYOUTRULE_BOTTOM);
			if(headerBarBottomRule!=nullptr && headerBarBottomRule->valueType==fgl::LAYOUTVALUE_RATIO)
			{
				frameoffset_y = headerBarBottomRule->value*1.1;
			}
			
			fgl::RectD bounds(0.1, frameoffset_y, 0.9, 0.6);
			double bounds_w = bounds.right - bounds.left;
			double bounds_h = bounds.bottom - bounds.top;
			
			double icon_width = bounds_w/((double)cols);
			double icon_height = bounds_h/((double)rows);
			
			for(size_t i=0; i<characters.size(); i++)
			{
				auto& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(menuData, info);
				size_t col = i%cols;
				size_t row = i/cols;
				double icon_left = bounds.left+(((double)col)*icon_width);
				double icon_top = bounds.top+(((double)row)*icon_height);
				icon->setLayoutRule(fgl::LAYOUTRULE_LEFT, icon_left, fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_TOP, icon_top, fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 1.0-(icon_left+icon_width), fgl::LAYOUTVALUE_RATIO);
				icon->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 1.0-(icon_top+icon_height), fgl::LAYOUTVALUE_RATIO);
				iconsElement->addChildElement(icon);
				icons.add(icon);
			}
		}
		
		void CharacterSelectScreen::reloadPlayers()
		{
			for(auto& panel : panels)
			{
				panel->removeFromParentElement();
				delete panel;
			}
			panels.clear();
			for(auto& chip : chips)
			{
				chip->removeFromParentElement();
				delete chip;
			}
			chips.clear();
			
			size_t playerCount = rules->getPlayerCount();
			if(playerCount==0)
			{
				return;
			}

			auto menuData = getMenuData();
			auto assetManager = menuData->getAssetManager();
			auto window = assetManager->getWindow();
			auto screenSize = window->getDrawSize();
			
			fgl::RectD panelBounds(0.0, 0.6, 1.0, 1.0);
			
			double panelBounds_w = panelBounds.right - panelBounds.left;
			double panelBounds_h = panelBounds.bottom - panelBounds.top;

			double panel_width = panelBounds_w/(double)playerCount;
			double panel_height = panelBounds_h;
			
			for(size_t playerIndex=0; playerIndex<playerCount; playerIndex++)
			{
				PlayerPanel* panel = new PlayerPanel(this, menuData, playerIndex);
				double panel_left = panelBounds.left + (panel_width*(double)playerIndex);
				double panel_center_x = panel_left + (panel_width/2);
				double panel_top = panelBounds.top;
				panel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, panel_center_x, fgl::LAYOUTVALUE_RATIO);
				panel->setLayoutRule(fgl::LAYOUTRULE_TOP, panel_top, fgl::LAYOUTVALUE_RATIO);
				panel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, panel_height, fgl::LAYOUTVALUE_RATIO);
				panelsElement->addChildElement(panel);
				panels.add(panel);
				
				fgl::Vector2d chipCenter;
				chipCenter.x = (panel_left*(double)screenSize.x)+20;
				chipCenter.y = (panel_top+(panel_height/2))*screenSize.y;
				
				PlayerChip* chip = new PlayerChip(this, menuData, playerIndex);
				chip->setCenter(chipCenter);
				chip->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 0.08, fgl::LAYOUTVALUE_RATIO);
				chip->setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, 1.0, fgl::LAYOUTVALUE_RATIO);
				chipsElement->addChildElement(chip);
				chips.add(chip);
			}
		}

		void CharacterSelectScreen::resetPlayerChip(size_t playerIndex)
		{
			auto chip = getPlayerChip(playerIndex);
			auto screenSize = getSize();

			double panel_width = 1.0/(double)rules->getPlayerCount();
			double panel_height = 0.4;
			double panel_top = 0.6;
			double panel_left = panel_width*(double)playerIndex;

			fgl::Vector2d chipCenter;
			chipCenter.x = (panel_left*(double)screenSize.x)+20;
			chipCenter.y = (panel_top+(panel_height/2))*screenSize.y;

			chip->setCenter(chipCenter);
		}
		
		void CharacterSelectScreen::onUpdate(const fgl::ApplicationData& appData)
		{
			BaseMenuScreen::onUpdate(appData);
			if(isReadyToFight())
			{
				readyToFightBanner->setVisible(true);
			}
			else
			{
				readyToFightBanner->setVisible(false);
			}
		}
		
		void CharacterSelectScreen::handlePlayerChipGrabbed(size_t playerIndex)
		{
			auto& info = rules->getPlayerInfo(playerIndex);
			info.turnPlayerModeOn();
		}
		
		void CharacterSelectScreen::handlePlayerChipReleased(size_t playerNum)
		{
			/*auto& info = rules->getPlayerInfo(playerIndex);
			auto characterID = info.getCharacterIdentifier();
			if(characterID.length() == 0)
			{
				info.turnPlayerModeOff();
			}*/
		}
		
		void CharacterSelectScreen::handlePlayerCharacterChanged(size_t playerIndex, const fgl::String& characterIdentifier)
		{
			for(auto& panel : panels)
			{
				if(playerIndex == panel->getPlayerIndex())
				{
					if(characterIdentifier.length()!=0)
					{
						auto& characterInfo = getMenuData()->getModuleManager()->getCharacterLoader()->getCharacterInfo(characterIdentifier);
						panel->applyCharacterInfo(&characterInfo);
					}
					else
					{
						panel->applyCharacterInfo(nullptr);
					}
					return;
				}
			}
		}
	}
}
