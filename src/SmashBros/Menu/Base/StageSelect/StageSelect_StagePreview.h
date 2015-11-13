
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

using namespace GameLibrary;
using namespace BrawlerLibrary;

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			class StagePreview : public ImageElement
			{
			private:
				StageInfo* info;
				AssetManager* assetManager;
				
			public:
				explicit StagePreview(AssetManager*assetManager);
				StagePreview(const RectangleD&frame, AssetManager*assetManager);
				virtual ~StagePreview();
				
				void setStageInfo(StageInfo*);
				StageInfo* getStageInfo() const;
			};
		}
	}
}
