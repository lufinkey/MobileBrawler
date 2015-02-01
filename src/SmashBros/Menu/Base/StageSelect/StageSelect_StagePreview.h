
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
			class StagePreview : public SpriteActor
			{
			private:
				StageInfo* info;
				
			public:
				StagePreview(StageInfo&info, float x, float y, AssetManager*assetManager);
				virtual ~StagePreview();
				
				virtual void draw(ApplicationData appData, Graphics graphics) const override;

			};
		}
	}
}
