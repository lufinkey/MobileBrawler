
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
			class StageIcon : public SpriteActor
			{
			private:
				StageInfo* info;
				
			public:
				StageIcon(StageInfo&info, double x, double y, AssetManager*assetManager);
				virtual ~StageIcon();
				
				virtual void draw(ApplicationData appData, Graphics graphics) const override;
				
				StageInfo* getStageInfo() const;
			};
		}
	}
}
