
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "../../MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			class StagePreview : public fgl::ImageElement
			{
			public:
				explicit StagePreview(MenuData* menuData);
				virtual ~StagePreview();
				
				void setStageInfo(StageInfo* stageInfo);
				StageInfo* getStageInfo() const;

			private:
				MenuData* menuData;
				StageInfo* stageInfo;
			};
		}
	}
}
