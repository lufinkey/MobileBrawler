
#include "CharacterSelect_PlayerPanel.hpp"
#include "CharacterSelectScreen.hpp"
#include "CharacterSelect_PlayerChip.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			PlayerPanel::PlayerPanel(CharacterSelectScreen* charSelectScreen, MenuData* menuData, size_t playerIndex)
				: PlayerPanel(charSelectScreen, menuData, playerIndex, getDefaultProperties(menuData->getAssetManager()))
			{
				//
			}

			PlayerPanel::PlayerPanel(CharacterSelectScreen* charSelectScreen, MenuData* menuData, size_t playerIndex, const fgl::Dictionary& properties)
				: charSelectScreen(charSelectScreen),
				menuData(menuData),
				playerIndex(playerIndex)
			{
				auto assetManager = menuData->getAssetManager();
				auto playerNum = playerIndex+1;

				humanBackground = assetManager->loadTexture((fgl::String)"characterselect/panel_background_p" + playerNum + ".png");
				cpuBackground = assetManager->loadTexture("characterselect/panel_background_cpu.png");
				offBackground = assetManager->loadTexture("characterselect/panel_background_na.png");

				humanOverlay = assetManager->loadTexture((fgl::String)"characterselect/panel_overlay_p" + playerNum + ".png");
				cpuOverlay = assetManager->loadTexture("characterselect/panel_overlay_cpu.png");
				offOverlay = assetManager->loadTexture("characterselect/panel_overlay_na.png");

				backgroundElement = new fgl::ImageElement(offBackground);
				backgroundElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				backgroundElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				backgroundElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				backgroundElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

				portraitElement = new fgl::ImageElement();
				portraitElement->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
				portraitElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				portraitElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				portraitElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				portraitElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

				overlayElement = new fgl::ImageElement(offOverlay);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
				overlayElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

				nameLabel = new fgl::TextElement();
				nameLabel->setFont(assetManager->loadFont("fonts/default.ttf"));
				nameLabel->setTextColor(fgl::Color::BLACK);
				nameLabel->setFontSize(36);
				nameLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
				nameLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
				nameLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.320, fgl::LAYOUTVALUE_RATIO);
				nameLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.870, fgl::LAYOUTVALUE_RATIO);
				nameLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.090, fgl::LAYOUTVALUE_RATIO);
				nameLabel->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.019, fgl::LAYOUTVALUE_RATIO);

				if(offBackground!=nullptr)
				{
					setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, (double)offBackground->getWidth()/(double)offBackground->getHeight(), fgl::LAYOUTVALUE_RATIO);
				}
				else
				{
					setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, 0.7, fgl::LAYOUTVALUE_RATIO);
				}
				
				addChildElement(backgroundElement);
				addChildElement(portraitElement);
				addChildElement(overlayElement);
				addChildElement(nameLabel);
				
				applyProperties(properties);

				setBorderWidth(1);
			}
			
			PlayerPanel::~PlayerPanel()
			{
				delete backgroundElement;
				delete portraitElement;
				delete overlayElement;
				delete nameLabel;
			}
			
			void PlayerPanel::applyProperties(const fgl::Dictionary& properties)
			{
				auto portrait = fgl::extract<fgl::Dictionary>(properties, "portrait", {});
				auto portrait_layoutRules = fgl::extract<fgl::Dictionary>(portrait, "layoutRules", {});
				if(portrait_layoutRules.size() > 0)
				{
					portraitElement->setLayoutRules(portrait_layoutRules);
				}
				auto overlay = fgl::extract<fgl::Dictionary>(properties, "overlay", {});
				auto overlay_layoutRules = fgl::extract<fgl::Dictionary>(overlay, "layoutRules", {});
				if(overlay_layoutRules.size() > 0)
				{
					overlayElement->setLayoutRules(overlay_layoutRules);
				}
				auto namebox = fgl::extract<fgl::Dictionary>(properties, "namebox", {});
				auto namebox_layoutRules = fgl::extract<fgl::Dictionary>(namebox, "layoutRules", {});
				if(namebox_layoutRules.size() > 0)
				{
					nameLabel->setLayoutRules(namebox_layoutRules);
				}
				auto namebox_color = fgl::extract<fgl::Dictionary>(namebox, "color", {});
				if(namebox_color.size() > 0)
				{
					nameLabel->setTextColor(fgl::Color(namebox_color));
				}
			}

			fgl::Dictionary PlayerPanel::getDefaultProperties(fgl::AssetManager* assetManager)
			{
				FILE* file = assetManager->openFile("characterselect/panel.plist", "rb");
				if(file!=nullptr)
				{
					fgl::Dictionary properties;
					fgl::Plist::loadFromFile(&properties, file);
					fgl::FileTools::closeFile(file);
					return properties;
				}
				return {};
			}
			
			void PlayerPanel::update(fgl::ApplicationData appData)
			{
				auto& playerInfo = charSelectScreen->getRules()->getPlayerInfo(playerIndex);
				switch(playerInfo.getPlayerMode())
				{
					case PlayerInfo::MODE_OFF:
					backgroundElement->setImage(offBackground);
					overlayElement->setImage(offOverlay);
					break;
					
					case PlayerInfo::MODE_HUMAN:
					backgroundElement->setImage(humanBackground);
					overlayElement->setImage(humanOverlay);
					break;
					
					case PlayerInfo::MODE_CPU:
					backgroundElement->setImage(cpuBackground);
					overlayElement->setImage(cpuOverlay);
					break;
				}
				
				auto& chips = charSelectScreen->getPlayerChips();
				for(auto& chip : chips)
				{
					if(chip->getPlayerIndex() == playerIndex)
					{
						if(chip->isDragging())
						{
							portraitElement->setAlpha(0.5);
						}
						else
						{
							portraitElement->setAlpha(1.0);
						}
						break;
					}
				}

				TouchElement::update(appData);
			}

			void PlayerPanel::onTouchUpInside(const TouchEvent& event)
			{
				auto& playerInfo = charSelectScreen->getRules()->getPlayerInfo(playerIndex);
				playerInfo.cyclePlayerMode();
			}
			
			size_t PlayerPanel::getPlayerIndex() const
			{
				return playerIndex;
			}
			
			void PlayerPanel::applyCharacterInfo(const CharacterInfo* characterInfo)
			{
				if(characterInfo == nullptr)
				{
					nameLabel->setText("");
					portraitElement->setImage(nullptr);
				}
				else
				{
					nameLabel->setText(characterInfo->getName());
					auto portrait = menuData->getModuleManager()->getCharacterPortrait(characterInfo->getIdentifier());
					portraitElement->setImage(portrait);
				}
			}
		}
	}
}
