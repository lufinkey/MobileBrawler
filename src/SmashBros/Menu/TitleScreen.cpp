
#include "TitleScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();

			assetManager->loadTexture("titlescreen/background.png");
			assetManager->loadTexture("titlescreen/logo.png");

			getBackgroundElement()->setImage(assetManager->getTexture("titlescreen/background.png"));
			
			TextureImage* logoImage = assetManager->getTexture("titlescreen/logo.png");
			Vector2d logoImageSize(0,0);
			if(logoImage != nullptr)
			{
				logoImageSize.x = (double)logoImage->getWidth();
				logoImageSize.y = (double)logoImage->getHeight();
			}
			logo = new ImageElement(logoImage, ImageElement::DISPLAY_FIT_CENTER);
			logo->setLayoutRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_RIGHT,  0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_BOTTOM, 0, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(logo);
			
			auto mainMenu = new MainMenu(smashData);
			addScreen("MainMenu", mainMenu);
			transition = new FadeColorTransition(Color::WHITE, 0.6);
			
			Vector2d size = getSize();
			tapRegion = new WireframeActor(0, 0, size.x, size.y);
			
			getBackButton()->setVisible(false);
			getHeaderbarElement()->setVisible(false);
		}
		
		TitleScreen::~TitleScreen()
		{
			delete transition;
			logo->removeFromParentElement();
			delete logo;
			delete tapRegion;
		}
		
		void TitleScreen::onUpdate(const ApplicationData& appData)
		{
			BaseMenuScreen::onUpdate(appData);
			tapRegion->update(appData);
			if(tapRegion->didMouseRelease())
			{
				ScreenManager* screenMgr = getScreenManager();
				if(screenMgr!=nullptr)
				{
					goToScreen("MainMenu", transition, 2000);
				}
			}
		}
		
		void TitleScreen::onSizeChange(const Vector2d& oldSize, const Vector2d& newSize)
		{
			BaseMenuScreen::onSizeChange(oldSize, newSize);
			Vector2d size = getSize();
			tapRegion->x = 0;
			tapRegion->y = 0;
			tapRegion->setSize(size.x, size.y);
		}
		
		void TitleScreen::onItemSelect(size_t index)
		{
			//no behavior
		}
	}
}
