
#include "TitleScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(MenuData* menuData) : SmashBros::Menu::BaseMenuScreen(menuData)
		{
			auto assetManager = menuData->getAssetManager();

			getBackgroundElement()->setImage(assetManager->loadTexture("titlescreen/background.png"));
			
			logo = new fgl::ImageElement(assetManager->loadTexture("titlescreen/logo.png"), fgl::ImageElement::DISPLAY_FIT_CENTER);
			logo->setLayoutRule(fgl::LAYOUTRULE_LEFT,   0, fgl::LAYOUTVALUE_RATIO);
			logo->setLayoutRule(fgl::LAYOUTRULE_TOP,    0, fgl::LAYOUTVALUE_RATIO);
			logo->setLayoutRule(fgl::LAYOUTRULE_RIGHT,  0, fgl::LAYOUTVALUE_RATIO);
			logo->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0, fgl::LAYOUTVALUE_RATIO);
			getElement()->addChildElement(logo);
			
			auto mainMenu = new MainMenu(menuData);
			addScreen("MainMenu", mainMenu);
			transition = new fgl::FadeColorTransition(fgl::Color::WHITE, 0.6);
			
			tapRegion = new fgl::ButtonElement();
			tapRegion->setTapHandler([=]{
				goToScreen("MainMenu", transition, 2000);
			});
			tapRegion->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0, fgl::LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(fgl::LAYOUTRULE_TOP, 0, fgl::LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0, fgl::LAYOUTVALUE_RATIO);
			tapRegion->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0, fgl::LAYOUTVALUE_RATIO);
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
