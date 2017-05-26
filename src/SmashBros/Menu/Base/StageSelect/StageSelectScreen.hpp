
#pragma once

#include "../BaseMenuScreen.hpp"
#include <SmashBros/Game/Rules/Rules.hpp>

namespace SmashBros
{
	namespace Menu
	{
		namespace StageSelect
		{
			class StageIcon;
			class StagePreview;
		}
		
		class StageSelectScreen : public BaseMenuScreen
		{
		public:
			StageSelectScreen(MenuData* menuData, Rules* rules);
			virtual ~StageSelectScreen();
			
			Rules* getRules() const;
			StageSelect::StagePreview* getStagePreviewElement() const;
			const fgl::ArrayList<StageSelect::StageIcon*>& getStageIcons() const;
			
		protected:
			void reloadIcons();
			
			virtual void onUpdate(const fgl::ApplicationData& appData) override;
			
		private:
			Rules* rules;

			fgl::ArrayList<StageSelect::StageIcon*> icons;
			fgl::ScreenElement* iconsElement;
			StageSelect::StagePreview* previewElement;
		};
	}
}
