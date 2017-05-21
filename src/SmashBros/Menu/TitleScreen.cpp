
#include "TitleScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();

			getBackgroundElement()->setImage(assetManager->loadTexture("titlescreen/background.png"));
			
			logo = new ImageElement(assetManager->loadTexture("titlescreen/logo.png"), ImageElement::DISPLAY_FIT_CENTER);
			logo->setLayoutRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_RIGHT,  0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_BOTTOM, 0, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(logo);
			
			auto mainMenu = new MainMenu(smashData);
			addScreen("MainMenu", mainMenu);
			transition = new FadeColorTransition(Color::WHITE, 0.6);
			
			tapRegion = new ButtonElement();
			tapRegion->setTapHandler([=]{
				goToScreen("MainMenu", transition, 2000);
			});
			tapRegion->setLayoutRule(LAYOUTRULE_LEFT, 0, LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(LAYOUTRULE_TOP, 0, LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(LAYOUTRULE_RIGHT, 0, LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(LAYOUTRULE_BOTTOM, 0, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(tapRegion);
			
			getBackButton()->setVisible(false);
			getHeaderbarElement()->setVisible(false);
		}
		
		TitleScreen::~TitleScreen()
		{
			delete transition;
			delete logo;
			delete tapRegion;
		}
	}
}
