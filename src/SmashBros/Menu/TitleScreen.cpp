
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
			Vector2d logoImageSize(0,0);
			if(logoImage != nullptr)
			{
				logoImageSize.x = (double)logoImage->getWidth();
				logoImageSize.y = (double)logoImage->getHeight();
			}
			logo = new ImageElement(logoImage, ImageElement::DISPLAY_FIT);
			logo->setLayoutRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
			logo->setLayoutRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
			getElement()->addChildElement(logo);
			
			mainMenu = new MainMenu(smashData);
			transition = new FadeColorTransition(Color::WHITE, 0.6);
			
			RectangleD frame = getFrame();
			tapRegion = new WireframeActor(0, 0, frame.width, frame.height);
			
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
		
		void TitleScreen::onFrameChange(const RectangleD& oldFrame, const RectangleD& newFrame)
		{
			BaseMenuScreen::onFrameChange(oldFrame, newFrame);
			RectangleD frame = getFrame();
			tapRegion->x = 0;
			tapRegion->y = 0;
			tapRegion->setSize(frame.width, frame.height);
		}
		
		void TitleScreen::onItemSelect(size_t index)
		{
			//no behavior
		}
	}
}
