
#include "StageSelect_StagePreview.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			StagePreview::StagePreview(AssetManager*assetMgr) : StagePreview(RectangleD(0, 0, 0, 0), assetMgr)
			{
				//
			}
			
			StagePreview::StagePreview(const RectangleD& frame, AssetManager*assetMgr) : ImageElement(frame)
			{
				assetManager = assetMgr;
				info = nullptr;
				setDisplayMode(DISPLAY_FIT_CENTER);
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
