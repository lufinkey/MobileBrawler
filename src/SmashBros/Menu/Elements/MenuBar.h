
#pragma once

#include <GameLibrary/GameLibrary.hpp>

using namespace fgl;

namespace SmashBros
{
	namespace Menu
	{
		class MenuBar : public SpriteActor
		{
		private:
			TextActor* label_actor;
			AutoLayoutManager label_autoLayoutMgr;
			Color label_color;
			
			void applyProperties(const Dictionary&properties);
			
		protected:
			AutoLayoutManager autoLayoutMgr;
			
			void applyPlacementDict(const Dictionary& dict, AutoLayoutManager* layoutMgr);
			void applyColorDict(const Dictionary& dict, Color* color);
			
		public:
			MenuBar(const String&label, AssetManager*assetManager, const Dictionary&properties);
			MenuBar(double x, double y, const String&label, AssetManager*assetManager, const Dictionary&properties);
			virtual ~MenuBar();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			void setLabel(const String&);
			void setLabelAlignment(const TextActor::TextAlignment&);
			
			const String& getLabel() const;
			AutoLayoutManager& getLabelAutoLayoutManager();
			const AutoLayoutManager& getLabelAutoLayoutManager() const;
			const TextActor::TextAlignment& getLabelAlignment() const;
			
			virtual void updateSize() override;
		};
	}
}
