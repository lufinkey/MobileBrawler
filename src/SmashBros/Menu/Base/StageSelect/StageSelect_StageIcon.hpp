
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "../../MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class StageSelectScreen;
		
		namespace StageSelect
		{
			class StageIcon : public fgl::ButtonElement
			{
				friend class ::SmashBros::Menu::StageSelectScreen;
			public:
				StageIcon(MenuData* menuData, StageInfo info);
				virtual ~StageIcon();
				
				const StageInfo& getStageInfo() const;

			private:
				StageInfo stageInfo;

				fgl::ImageElement* overlayElement;
			};
		}
	}
}
