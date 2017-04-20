
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <SmashLib/SmashLib.hpp>

using namespace fgl;
using namespace SmashLib;

namespace SmashBros
{
	namespace Menu
	{
		class CharacterSelectScreen;
		
		namespace CharacterSelect
		{
			class PlayerChip : public SpriteActor
			{
			private:
				unsigned int playerNum;
				CharacterSelectScreen*charSelectScreen;
				
				bool dragging;
				unsigned int dragTouchID;
				Vector2d dragOffset;
				
			public:
				PlayerChip(unsigned int playerNum, CharacterSelectScreen*charSelectScreen, double x, double y, AssetManager*assetManager);
				virtual ~PlayerChip();
				
				virtual void onMousePress(const ActorMouseEvent& evt) override;
				virtual void update(ApplicationData appData) override;
				
				void updateDragging(ApplicationData appData, Graphics graphics);
				void grabChip(const ApplicationData&appData, unsigned int touchID);
				void releaseChip();
				
				bool isDragging() const;
				unsigned int getPlayerNum() const;
			};
		}
	}
}
