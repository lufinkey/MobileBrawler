
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
			RectF label_bounds;
			
		protected:
			RectangleF getLabelFrame(const RectF&bounds) const;
			
		public:
			MenuBar(float x, float y, const String&label, AssetManager*assetManager);
			virtual ~MenuBar();
			
			virtual void update(ApplicationData appData) override;
			virtual void draw(ApplicationData appData, Graphics graphics) const override;
			
			void setLabel(const String&);
			void setLabelBounds(const RectF&bounds);
			void setLabelAlignment(const TextActor::TextAlignment&);

			const String& getLabel() const;
			const RectF& getLabelBounds() const;
			const TextActor::TextAlignment& getLabelAlignment() const;
		};
	}
}
