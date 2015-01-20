
#include "CharacterSelectScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		CharacterSelectScreen::CharacterIcon::CharacterIcon(const CharacterInfo&characterInfo, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
		{
			info = &characterInfo;
			String icon_path = characterInfo.getPath() + "/icon.png";
			addAnimation("default", new Animation(assetManager, 1, icon_path));
			changeAnimation("default", Animation::FORWARD);
		}
		
		CharacterSelectScreen::CharacterIcon::~CharacterIcon()
		{
			//
		}
		
		bool CharacterSelectScreen::CharacterIcon::equals(const CharacterIcon&icon) const
		{
			if(info->getName().equals(icon.info->getName()) && info->getCreator().equals(icon.info->getCreator()))
			{
				return true;
			}
			return false;
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getName() const
		{
			return info->getName();
		}
		
		const String& CharacterSelectScreen::CharacterIcon::getCreator() const
		{
			return info->getCreator();
		}
		
		CharacterSelectScreen::PlayerChip::PlayerChip(float x, float y)
		{
			//
		}
		
		CharacterSelectScreen::PlayerChip::~PlayerChip()
		{
			//
		}
		
		CharacterSelectScreen::PlayerPanel::PlayerPanel(float x, float y)
		{
			//
		}
		
		CharacterSelectScreen::PlayerPanel::~PlayerPanel()
		{
			//
		}
		
		CharacterSelectScreen::CharacterSelectScreen(const SmashData&smashData) : SmashBros::Menu::BaseMenuScreen(smashData)
		{
			iconGrid = nullptr;
			reloadIcons(smashData);
		}
		
		CharacterSelectScreen::~CharacterSelectScreen()
		{

		}
		
		void CharacterSelectScreen::reloadIcons(const SmashData&smashData)
		{
			if(iconGrid != nullptr)
			{
				delete iconGrid;
				iconGrid = nullptr;
			}
			
			for(unsigned int i=0; i<icons.size(); i++)
			{
				delete icons.get(i);
			}
			icons.clear();
			
			const ArrayList<CharacterInfo>& characters = smashData.getCharacterLoader()->getCharacters();
			unsigned int total = characters.size();
			float approx_cols = Math::sqrt((3.0f*((float)total))/2.0f);
			float approx_rows = approx_cols*(2.0f/3.0f);
			unsigned int cols = (unsigned int)Math::round(approx_cols);
			unsigned int rows = (unsigned int)Math::round(approx_rows);
			if((cols*rows) < total)
			{
				cols = (unsigned int)Math::ceil(approx_cols);
				if((cols*rows) < total)
				{
					rows = (unsigned int)Math::ceil(approx_rows);
				}
			}
			
			Vector2f topLeft = smashData.getScreenCoords(0.1f, 0.16f);
			Vector2f bottomRight = smashData.getScreenCoords(0.9f, 0.6f);
			RectangleF charSelectRect = RectangleF(topLeft.x, topLeft.y, bottomRight.x-topLeft.x, bottomRight.y-topLeft.y);
			
			float icon_width = charSelectRect.width/((float)cols);
			float icon_height = charSelectRect.height/((float)rows);
			Vector2f icon_size(icon_width-1, icon_height);
			
			iconGrid = new ActorGrid(Vector2f(charSelectRect.x+(icon_width/2), charSelectRect.y+(icon_height/2)), cols, Vector2f(icon_width, icon_height));
			
			AssetManager* loaderAssetManager = smashData.getCharacterLoader()->getAssetManager();
			for(unsigned int i=0; i<characters.size(); i++)
			{
				const CharacterInfo& info = characters.get(i);
				CharacterIcon* icon = new CharacterIcon(info, 0, 0, loaderAssetManager);
				icon->Actor::scaleToFit(icon_size);
				icons.add(icon);
				iconGrid->add(icon);
			}
		}
		
		void CharacterSelectScreen::updateItems(ApplicationData appData)
		{
			BaseMenuScreen::updateItems(appData);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				icons.get(i)->update(appData);
			}
		}
		
		void CharacterSelectScreen::drawItems(ApplicationData appData, Graphics graphics) const
		{
			TextureImage* icon_frame = appData.getAssetManager()->getTexture("characterselect/icon_frame.png");
			BaseMenuScreen::drawItems(appData, graphics);
			for(unsigned int i=0; i<icons.size(); i++)
			{
				CharacterIcon* icon = icons.get(i);
				icon->draw(appData, graphics);
				RectangleF frame = icon->getFrame();
				graphics.drawImage(icon_frame, frame);
			}
		}
	}
}
