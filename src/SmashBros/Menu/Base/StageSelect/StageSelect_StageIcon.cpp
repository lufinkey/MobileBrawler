
#include "StageSelect_StageIcon.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			StageIcon::StageIcon(StageInfo&stageInfo, float x, float y, AssetManager*assetManager)
			{
				info = &stageInfo;
				String icon_path = stageInfo.getPath() + "/icon.png";
				addAnimation("default", new Animation(1, assetManager, icon_path));
				changeAnimation("default", Animation::FORWARD);
			}
			
			StageIcon::~StageIcon()
			{
				//
			}
			
			void StageIcon::draw(ApplicationData appData, Graphics graphics) const
			{
				SpriteActor::draw(appData, graphics);
				TextureImage* icon_frame = appData.getAssetManager()->getTexture("stageselect/icon_frame.png");
				graphics.drawImage(icon_frame, getFrame());
			}
		}
	}
}
