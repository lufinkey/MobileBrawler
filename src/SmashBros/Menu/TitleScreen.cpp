
#include "TitleScreen.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();

			getBackgroundElement()->setImage(assetManager->getTexture("titlescreen/background.png"));
			
			TextureImage* logoImage = assetManager->getTexture("titlescreen/logo.png");
			Vector2f logoImageSize(0,0);
			if(logoImage != nullptr)
			{
				logoImageSize.x = (float)logoImage->getWidth();
				logoImageSize.y = (float)logoImage->getHeight();
			}
			logo = new ImageElement(logoImage, ImageElement::DISPLAY_FIT);
			getElement()->addChildElement(RectF(0,0,1.0f,1.0f), logo);
			
			mainMenu = new MainMenu(smashData);
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
		
		void TitleScreen::onUpdate(ApplicationData appData)
		{
			BaseMenuScreen::onUpdate(appData);
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
		
		void TitleScreen::onFrameChange()
		{
			BaseMenuScreen::onFrameChange();
			RectangleF frame = getFrame();
			tapRegion->x = 0;
			tapRegion->y = 0;
			tapRegion->setSize(frame.width, frame.height);
		}
		
		void TitleScreen::onItemSelect(unsigned int index)
		{
			//no behavior
		}
	}
}
