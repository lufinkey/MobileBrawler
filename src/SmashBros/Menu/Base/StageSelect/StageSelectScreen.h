
#pragma once

#include "../BaseMenuScreen.h"
#include "../../Elements/ActorGrid.h"

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
			StageSelectScreen(const SmashData&smashData, Rules*rules);
			virtual ~StageSelectScreen();
			
			Rules* getRules() const;
			StageLoader* getStageLoader() const;
			const ArrayList<StageSelect::StagePreview*>& getStagePreviews() const;
			const ArrayList<StageSelect::StageIcon*>& getStageIcons() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPreviews(const SmashData&smashData);
			
			virtual void onUpdate(ApplicationData appData) override;
			virtual void onDraw(ApplicationData appData, Graphics graphics) const override;
			
		private:
			Rules*rules;
			StageLoader* stageLoader;
			RectangleF iconGridFrame;
			ActorGrid*iconGrid;
			ImageElement*preview;
			ArrayList<StageSelect::StageIcon*> icons;
			ArrayList<StageSelect::StagePreview*> previews;
		};
	}
}
