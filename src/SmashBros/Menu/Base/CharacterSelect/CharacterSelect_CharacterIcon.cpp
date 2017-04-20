
#include "CharacterSelect_CharacterIcon.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			CharacterIcon::CharacterIcon(CharacterInfo&characterInfo, double x, double y, AssetManager*assetManager) : SpriteActor(x,y)
			{
				info = &characterInfo;
				String icon_path = characterInfo.getPath() + "/icon.png";
				addAnimation("default", new Animation(1, assetManager, icon_path));
				changeAnimation("default", Animation::FORWARD);
			}
			
			CharacterIcon::~CharacterIcon()
			{
				//
			}
			
			void CharacterIcon::draw(ApplicationData appData, Graphics graphics) const
			{
				SpriteActor::draw(appData, graphics);
				TextureImage* icon_frame = appData.getAssetManager()->getTexture("characterselect/icon_frame.png");
				graphics.drawImage(icon_frame, getFrame());
			}
			
			bool CharacterIcon::equals(const CharacterIcon&icon) const
			{
				if(info->getName().equals(icon.info->getName()) && info->getCreator().equals(icon.info->getCreator()))
				{
					return true;
				}
				return false;
			}
			
			const String& CharacterIcon::getName() const
			{
				return info->getName();
			}
			
			const String& CharacterIcon::getCreator() const
			{
				return info->getCreator();
			}
			
			CharacterInfo* CharacterIcon::getCharacterInfo() const
			{
				return info;
			}
		}
	}
}
