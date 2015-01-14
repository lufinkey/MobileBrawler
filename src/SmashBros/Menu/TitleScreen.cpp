
#include "TitleScreen.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(AssetManager*assetManager) : SmashBros::Menu::BaseMenuScreen(assetManager)
		{
			Vector2f screenCenter = getScreenCoords(0.5f, 0.5f);

			assetManager->loadTexture("assets/menu/backgrounds/gradient_lightblue_whitestripe.png");
			getBackgroundElement()->setImage(assetManager->getTexture("assets/menu/backgrounds/gradient_lightblue_whitestripe.png"));
			
			assetManager->loadTexture("assets/menu/titlescreen/logo.png");
			TextureImage* logoImage = assetManager->getTexture("assets/menu/titlescreen/logo.png");
			Vector2f logoImageSize(0,0);
			if(logoImage != nullptr)
			{
				logoImageSize.x = (float)logoImage->getWidth();
				logoImageSize.y = (float)logoImage->getHeight();
			}
			RectangleF logoFrame(screenCenter.x-(logoImageSize.x/2), screenCenter.y-(logoImageSize.y/2), logoImageSize.x, logoImageSize.y);
			logo = new ImageElement(logoFrame, logoImage);
			getElement()->addChildElement(logo);
			
			mainMenu = new MainMenu(assetManager);
			transition = new FadeColorTransition(Color::WHITE, 0.6f);
			
			tapRegion = new WireframeActor();
			
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
		
		void TitleScreen::onWillAppear(const Transition*transition)
		{
			BaseMenuScreen::onWillAppear(transition);
			
			RectangleF frame = getFrame();
			RectangleF bounds = RectangleF(0,0,frame.width,frame.height);
			
			tapRegion->x = 0;
			tapRegion->y = 0;
			tapRegion->setSize(bounds.width, bounds.height);
			
			RectangleF logoFrame = logo->getFrame();
			logoFrame.scaleToFit(bounds);
			logo->setFrame(logoFrame);
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
