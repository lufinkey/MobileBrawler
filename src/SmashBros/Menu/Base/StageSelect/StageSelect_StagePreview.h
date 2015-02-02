
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	using namespace BrawlerLibrary;
	
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
				StagePreview(const RectangleF&frame, AssetManager*assetManager);
				virtual ~StagePreview();
				
				void setStageInfo(StageInfo*);
				StageInfo* getStageInfo() const;
			};
		}
	}
}
