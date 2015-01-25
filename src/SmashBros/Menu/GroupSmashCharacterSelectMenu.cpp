
#include "GroupSmashCharacterSelectMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		GroupSmashCharacterSelectMenu::GroupSmashCharacterSelectMenu(const SmashData&smashData) : CharacterSelectScreen(smashData)
		{
			setHeaderbarMode(HEADERBAR_SMALL);
			reloadIcons(smashData);
			reloadPlayerPanels(smashData);
			/*Vector2f rulesBar_topleft = smashData.getScreenCoords(0.36f, 0);
			Vector2f rulesBar_bottomright = smashData.getScreenCoords(1.0f, 0.162f);
			RectangleF rulesBar_frame = RectangleF(rulesBar_topleft.x, rulesBar_topleft.y, rulesBar_bottomright.x-rulesBar_topleft.x, getHeaderbarElement()->getFrame().height);
			rulesBar = new SpriteActor(rulesBar_frame.x+(rulesBar_frame.width/2), rulesBar_frame.y+(rulesBar_frame.height/2));
			rulesBar->addAnimation("default", new Animation(1, smashData.getMenuData().getAssetManager(), "characterselect/rules_bar.png"));
			rulesBar->Actor::scaleToFit(Vector2f(rulesBar_frame.width, rulesBar_frame.height));
			
			Vector2f rulesBar_arrowsPoint(rulesBar->x-(rulesBar->getWidth()/2)+(rulesBar->getWidth()/10), rulesBar->y);
			float rulesBar_arrowSpaceX = rulesBar->getWidth()/24;
			//rulesBar_leftArrow = new ArrowButton(rulesBar_arrowsPoint.x-rulesBar_arrowSpaceX, rulesBar_arrowsPoint.y, &rulesBarValue)*/
		}
		
		GroupSmashCharacterSelectMenu::~GroupSmashCharacterSelectMenu()
		{
			//delete rulesBar;
		}
		
		void GroupSmashCharacterSelectMenu::updateItems(ApplicationData appData)
		{
			CharacterSelectScreen::updateItems(appData);
			//rulesBar->update(appData);
		}
		
		void GroupSmashCharacterSelectMenu::drawItems(ApplicationData appData, Graphics graphics) const
		{
			CharacterSelectScreen::drawItems(appData, graphics);
			//rulesBar->draw(appData, graphics);
		}
	}
}
