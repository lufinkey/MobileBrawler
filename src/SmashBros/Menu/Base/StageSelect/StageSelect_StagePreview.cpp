
#include "StageSelect_StagePreview.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			StagePreview::StagePreview(MenuData* menuData)
				: menuData(menuData),
				stageInfo(nullptr)
			{
				setDisplayMode(DISPLAY_FIT_CENTER);
			}
			
			StagePreview::~StagePreview()
			{
				//
			}
			
			void StagePreview::setStageInfo(StageInfo* stageInfo_arg)
			{
				stageInfo = stageInfo_arg;
				if(stageInfo == nullptr)
				{
					setImage(nullptr);
				}
				else
				{
					auto texture = menuData->getModuleManager()->getStagePreview(stageInfo->getIdentifier());
					setImage(texture);
				}
			}
			
			StageInfo* StagePreview::getStageInfo() const
			{
				return stageInfo;
			}
		}
	}
}
