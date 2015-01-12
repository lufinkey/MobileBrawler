
#include "TitleScreen.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
		TitleScreen::TitleScreen(AssetManager*assetManager) : SmashBros::Menu::BaseMenuScreen(assetManager)
		{
			Vector2f screenCenter = getScreenCoords(0.5f, 0.5f);

			assetManager->loadTexture("images/menu/backgrounds/gradient_lightblue_whitestripe.png");
			TextureImage* backgroundImage = assetManager->getTexture("images/menu/backgrounds/gradient_lightblue_whitestripe.png");
			getBackgroundElement()->setImage(backgroundImage);
			
			assetManager->loadTexture("images/menu/titlescreen/logo.png");
			TextureImage* titleImage = assetManager->getTexture("images/menu/titlescreen/logo.png");
			Vector2f titleImageSize(0,0);
			if(titleImage != nullptr)
			{
				titleImageSize.x = (float)titleImage->getWidth();
				titleImageSize.y = (float)titleImage->getHeight();
			}
			RectangleF titleElementFrame(screenCenter.x-(titleImageSize.x/2), screenCenter.y-(titleImageSize.y/2), titleImageSize.x, titleImageSize.y);
			titleElement = new ImageElement(titleElementFrame, titleImage);
			getElement()->addChildElement(titleElement);
			
			mainMenu = new MainMenu(assetManager);
			transition = new FadeColorTransition(Color::WHITE, 0.5f);
			
			tapRegion = new WireframeActor();
		}
		
		TitleScreen::~TitleScreen()
		{
			delete mainMenu;
			delete transition;
			titleElement->removeFromParentElement();
			delete titleElement;
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
			
			RectangleF titleElementFrame = titleElement->getFrame();
			titleElementFrame.scaleToFit(bounds);
			Transform transform;
			transform.scale(0.7f, 0.7f, bounds.width/2, bounds.height/2);
			titleElementFrame = transform.transform(titleElementFrame);
			titleElement->setFrame(titleElementFrame);
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
					screenMgr->push(mainMenu, transition, 1000);
				}
			}
		}
	}
}
