
#include "TitleScreen.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			Vector2f screenSize = smashData.getScreenCoords(1.0f, 1.0f);
			Vector2f screenCenter = smashData.getScreenCoords(0.5f, 0.5f);
			AssetManager* assetManager = smashData.getMenuData().getAssetManager();

			getBackgroundElement()->setImage(assetManager->getTexture("titlescreen/background.png"));
			
			TextureImage* logoImage = assetManager->getTexture("titlescreen/logo.png");
			Vector2f logoImageSize(0,0);
			if(logoImage != nullptr)
			{
				logoImageSize.x = (float)logoImage->getWidth();
				logoImageSize.y = (float)logoImage->getHeight();
			}
			RectangleF logoFrame(screenCenter.x-(logoImageSize.x/2), screenCenter.y-(logoImageSize.y/2), logoImageSize.x, logoImageSize.y);
			logoFrame.scaleToFit(RectangleF(0,0,screenSize.x,screenSize.y));
			logo = new ImageElement(logoFrame, logoImage);
			getElement()->addChildElement(logo);
			
			mainMenu = new MainMenu(smashData);
			transition = new FadeColorTransition(Color::WHITE, 0.6f);
			
			tapRegion = new WireframeActor(0,0,screenSize.x,screenSize.y);
			
			getBackButton()->setVisible(false);
			getHeaderbarElement()->setVisible(false);
		}
		
		TitleScreen::~TitleScreen()
		{
			delete mainMenu;
			delete transition;
			logo->removeFromParentElement();
			delete logo;
			delete tapRegion;
		}
		
		void TitleScreen::updateItems(ApplicationData appData)
		{
			BaseMenuScreen::updateItems(appData);
			tapRegion->update(appData);
			if(tapRegion->didMouseRelease())
			{
				ScreenManager* screenMgr = getScreenManager();
				if(screenMgr!=nullptr)
				{
					screenMgr->push(mainMenu, transition, 2000);
				}
			}
		}
		
		void TitleScreen::onItemSelect(unsigned int index)
		{
			//no behavior
		}
	}
}
