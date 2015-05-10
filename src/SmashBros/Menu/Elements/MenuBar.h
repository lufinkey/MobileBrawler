
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	namespace Menu
	{
		class MenuBar : public SpriteActor
		{
		private:
			TextActor* label_actor;
			Color label_color;
			
			void applyProperties(const Dictionary&properties);
			
		protected:
			AutoLayoutManager autoLayoutMgr;
			
			RectangleD getLabelFrame(const RectD&bounds) const;
			void applyPropertiesDict(RectD*bounds, const Dictionary&properties);
			void applyPropertiesDict(Color*color, const Dictionary&properties);
			
		public:
			MenuBar(const WideString&label, AssetManager*assetManager, const Dictionary&properties);
			MenuBar(double x, double y, const WideString&label, AssetManager*assetManager, const Dictionary&properties);
			virtual ~MenuBar();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			void setLabel(const WideString&);
			void setLabelBounds(const RectD&bounds);
			void setLabelAlignment(const TextActor::TextAlignment&);
			
			const WideString& getLabel() const;
			const RectD& getLabelBounds() const;
			const TextActor::TextAlignment& getLabelAlignment() const;
			
			virtual void updateSize() override;
		};
	}
}
