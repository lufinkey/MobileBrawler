
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <SmashLib/SmashLib.hpp>

using namespace fgl;
using namespace SmashLib;

namespace SmashBros
{
	namespace Menu
	{
		class StageSelectScreen;
		
		namespace StageSelect
		{
			class StageIcon : public SpriteActor
			{
				friend class ::SmashBros::Menu::StageSelectScreen;
			private:
				StageInfo* info;
				AutoLayoutManager autoLayoutMgr;
				
			public:
				StageIcon(StageInfo&info, double x, double y, AssetManager*assetManager);
				virtual ~StageIcon();
				
				virtual void draw(ApplicationData appData, Graphics graphics) const override;
				
				StageInfo* getStageInfo() const;
			};
		}
	}
}
