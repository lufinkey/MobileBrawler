
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
			
			virtual void onFrameChange(const RectangleD& oldFrame, const RectangleD& newFrame) override;
			
			Rules* getRules() const;
			StageLoader* getStageLoader() const;
			StageSelect::StagePreview* getStagePreview() const;
			const ArrayList<StageSelect::StageIcon*>& getStageIcons() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPreview(const SmashData&smashData);
			
			virtual void onUpdate(ApplicationData appData) override;
			virtual void onDraw(ApplicationData appData, Graphics graphics) const override;
			
			virtual void onItemHover(size_t index) override;
			virtual void onItemHoverFinish(size_t index) override;
			
			virtual void onStageIconHover(StageSelect::StageIcon*icon);
			virtual void onStageIconHoverFinish(StageSelect::StageIcon*icon);
			
		private:
			Rules*rules;
			StageLoader* stageLoader;
			ArrayList<StageSelect::StageIcon*> icons;
			StageSelect::StagePreview* preview;
		};
	}
}
