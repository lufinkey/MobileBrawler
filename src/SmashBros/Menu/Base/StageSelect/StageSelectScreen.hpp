
#pragma once

#include "../BaseMenuScreen.hpp"
#include "../../Elements/ActorGrid.hpp"

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
			
			virtual void onSizeChange(const Vector2d& oldSize, const Vector2d& newSize) override;
			
			Rules* getRules() const;
			StageLoader* getStageLoader() const;
			StageSelect::StagePreview* getStagePreview() const;
			const ArrayList<StageSelect::StageIcon*>& getStageIcons() const;
			
		protected:
			void reloadIcons(const SmashData&smashData);
			void reloadPreview(const SmashData&smashData);
			
			virtual void onUpdate(const ApplicationData& appData) override;
			virtual void onDraw(const ApplicationData& appData, Graphics graphics) const override;
			
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
