
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "../../MenuData/MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class PlayerChip : public fgl::TouchElement
			{
			public:
				PlayerChip(CharacterSelectScreen*charSelectScreen, MenuData* menuData, size_t playerIndex);
				virtual ~PlayerChip();

				virtual void update(fgl::ApplicationData appData) override;
				
				bool isDragging() const;
				size_t getPlayerIndex() const;

			protected:
				virtual void onTouchDown(const TouchEvent& touchEvent) override;
				virtual bool onTouchMove(const TouchEvent& touchEvent) override;
				virtual void onTouchUpInside(const TouchEvent& touchEvent) override;
				virtual void onTouchUpOutside(const TouchEvent& touchEvent) override;
				virtual void onTouchCancel(const TouchEvent& touchEvent) override;

				void grabChip(const TouchEvent& touchEvent);
				void releaseChip();

			private:
				CharacterSelectScreen* charSelectScreen;
				size_t playerIndex;

				bool dragging;
				unsigned int dragTouchID;
				fgl::Vector2d dragOffset;

				fgl::TextureImage* playerChipTexture;
				fgl::TextureImage* cpuChipTexture;

				fgl::ImageElement* chipImageElement;
			};
		}
	}
}
