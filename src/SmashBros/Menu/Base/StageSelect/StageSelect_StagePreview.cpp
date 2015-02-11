
#include "StageSelect_StagePreview.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			StagePreview::StagePreview(AssetManager*assetMgr) : StagePreview(RectangleF(0, 0, 0, 0), assetMgr)
			{
				//
			}
			
			StagePreview::StagePreview(const RectangleF& frame, AssetManager*assetMgr) : ImageElement(frame)
			{
				assetManager = assetMgr;
				info = nullptr;
				setDisplayMode(DISPLAY_FIT);
			}
			
			StagePreview::~StagePreview()
			{
				//
			}
			
			void StagePreview::setStageInfo(StageInfo*stageInfo)
			{
				info = stageInfo;
				if(info == nullptr)
				{
					setImage(nullptr);
				}
				else
				{
					TextureImage* previewImage = assetManager->getTexture(info->getPath() + "/preview.png");
					setImage(previewImage);
				}
			}
			
			StageInfo* StagePreview::getStageInfo() const
			{
				return info;
			}
		}
	}
}
